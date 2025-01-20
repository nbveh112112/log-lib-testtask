#pragma once

#include <string>
#include <chrono>
#include <mutex>

enum class LogLevel {
  DEBUG,
  INFO,
  ERROR
};

struct LogMessage {
  std::string message;
  LogLevel level;
  std::chrono::system_clock::time_point timestamp;
};

class Logger {
public:
  Logger(const std::string& filename, LogLevel defaultLevel);

  void log(const std::string& message, LogLevel level = LogLevel::INFO);
  void setLevel(LogLevel level);
  LogLevel getDefaultLevel() const;

private:
  std::string filename;
  LogLevel defaultLevel;
  std::mutex mutex;
};
