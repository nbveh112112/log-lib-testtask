#ifndef APP_WORKER_H
#define APP_WORKER_H


#include <string>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "logger.h"

struct LogRequest;

class Worker {
public:
    Worker(Logger& logger);
    ~Worker();
    void stop();
    void addRequest(const LogRequest& request);

private:
    void workerThreadFunction();

    Logger& logger_;
    std::queue<LogRequest> logQueue_;
    std::mutex mutex_;
    std::condition_variable condition_;
    std::thread workerThread_;
    bool running_;
};

#endif //APP_WORKER_H
