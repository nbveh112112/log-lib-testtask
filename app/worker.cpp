#include "worker.h"

struct LogRequest {
    std::string message;
    LogLevel level;
};

Worker::Worker(Logger& logger) : logger_(logger), running_(true) {
    workerThread_ = std::thread(&Worker::workerThreadFunction, this);
}

Worker::~Worker() {
    stop();
    workerThread_.join();
}

void Worker::stop() {
    {
        std::unique_lock<std::mutex> lock(mutex_);
        running_ = false;
    }
    condition_.notify_one();
}

void Worker::addRequest(const LogRequest& request) {
    {
        std::unique_lock<std::mutex> lock(mutex_);
        logQueue_.push(request);
    }
    condition_.notify_one();
}


void Worker::workerThreadFunction() {
    while (running_) {
        LogRequest request;
        {
            std::unique_lock<std::mutex> lock(mutex_);
            condition_.wait(lock, [this] { return !logQueue_.empty() || !running_; });
            if(!running_ && logQueue_.empty())
                break;

            request = logQueue_.front();
            logQueue_.pop();
        }
        logger_.log(request.message, request.level);
    }
}