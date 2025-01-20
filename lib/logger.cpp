#include "logger.h"

#include <fstream>
#include <iostream>
#include <ctime>
#include <iomanip>

Logger::Logger(const std::string& filename, LogLevel defaultLevel)
  : filename(filename), defaultLevel(defaultLevel) {}

void Logger::log(const std::string& message, LogLevel level) {
  std::lock_guard<std::mutex> lock(mutex);
  if (level < defaultLevel)
    return;
  std::ofstream file(filename, std::ios::app);
  if (file.is_open()) {
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm;
    localtime_r(&now_c, &now_tm);
    file << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S") << " | ";

    switch (level) {
      case LogLevel::DEBUG:
        file << "DEBUG";
        break;
      case LogLevel::INFO:
        file << "INFO";
        break;
      case LogLevel::ERROR:
        file << "ERROR";
        break;
    }
    file << " | " << message << std::endl;
    file.close();
  } else {
    std::cerr << "Error opening log file: " << filename << std::endl;
  }
}

void Logger::setLevel(LogLevel level) {
  defaultLevel = level;
}
LogLevel Logger::getDefaultLevel() const
{
  return defaultLevel;
}
