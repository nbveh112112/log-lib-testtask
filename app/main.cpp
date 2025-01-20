#include <iostream>
#include <string>
#include <thread>
#include <future>
#include <sstream>

#include "logger.h" // Предполагается, что logger.h находится в папке include
std::ostream& operator<<(std::ostream& os, const LogLevel& level) {
    switch (level) {
        case LogLevel::DEBUG:
            os << "DEBUG";
            break;
        case LogLevel::INFO:
            os << "INFO";
            break;
        case LogLevel::ERROR:
            os << "ERROR";
            break;
        default:
          os << "UNKNOWN";
          break;
    }
    return os;
}

LogLevel parseLogLevel(const std::string& levelString) {
    if (levelString == "DEBUG") return LogLevel::DEBUG;
    if (levelString == "INFO") return LogLevel::INFO;
    if (levelString == "ERROR") return LogLevel::ERROR;
    return LogLevel::INFO; // Default to INFO if not recognized
}

int main(int argc, char* argv[]) {
  if (argc < 3) {
    std::cerr << "Usage: app <log_file> <default_log_level> \n";
    return 1;
  }

  std::string logFile = argv[1];
  LogLevel defaultLevel = parseLogLevel(argv[2]);


  Logger logger(logFile, defaultLevel);
  std::cout << "Current level " << logger.getDefaultLevel() << '\n';
    
    
  while (true) {
        std::string message;
        std::cout << "Enter message: ";
        std::getline(std::cin, message);


        std::string levelInput;
        std::cout << "Enter log level (DEBUG, INFO, ERROR, or empty for default): ";
        std::getline(std::cin, levelInput);
        LogLevel level = defaultLevel;
        if (!levelInput.empty())
            level = parseLogLevel(levelInput);


        std::thread logThread([&logger, message, level] {
            logger.log(message, level);
        });
        logThread.detach();
    
        std::string setLevelInput;
        std::cout << "Set level (DEBUG, INFO, ERROR, or empty for skip): ";
        std::getline(std::cin, setLevelInput);
        if(!setLevelInput.empty())
        {
            logger.setLevel(parseLogLevel(setLevelInput));
             std::cout << "Current level " << logger.getDefaultLevel() << '\n';
        }
  }


  return 0;
}
