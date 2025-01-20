#include <iostream>
#include <string>
#include <thread>
#include <future>
#include <sstream>
#include <fstream>
#include <vector>

#include "logger.h"

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

class ConsoleApp {
public:
    ConsoleApp(const std::string& logFile, LogLevel defaultLevel) : logger_(logFile, defaultLevel), logFileName_(logFile) {}

    bool isLogFileValid() {
        std::ofstream testFile(logFileName_, std::ios::app);
        if (!testFile.is_open()) {
            std::cerr << "Error: Cannot open log file for writing: " << logFileName_ << std::endl;
            return false;
        }
        testFile.close();
        return true;
    }


    void run() {
        if(!isLogFileValid())
            return;

        printHelp();
        std::string input;
        while (true) {
            std::cout << "> ";
            std::getline(std::cin, input);
            if (input == "exit")
                break;
            processInput(input);
        }
        std::cout << "Exiting application..." << std::endl;
    }

private:
    void printHelp() {
        std::cout << "Usage:" << std::endl;
        std::cout << "  <message>              Log message with default level." << std::endl;
        std::cout << "  DEBUG <message>        Log message with DEBUG level." << std::endl;
        std::cout << "  INFO <message>         Log message with INFO level." << std::endl;
        std::cout << "  ERROR <message>        Log message with ERROR level." << std::endl;
        std::cout << "  1 <message>            Log message with DEBUG level." << std::endl;
        std::cout << "  2 <message>            Log message with INFO level." << std::endl;
        std::cout << "  3 <message>            Log message with ERROR level." << std::endl;
        std::cout << "  set <level>            Set default log level (DEBUG, INFO, ERROR)." << std::endl;
        std::cout << "  exit                   Exit application." << std::endl;
        std::cout << std::endl;
    }

    void processInput(const std::string& input) {
        std::istringstream iss(input);
        std::string command;
        iss >> command;

        if (command == "set") {
            std::string levelStr;
            iss >> levelStr;
            setLevel(levelStr);
        } else if (command == "DEBUG" || command == "1") {
            logMessage(iss, LogLevel::DEBUG);
        } else if (command == "INFO" || command == "2") {
            logMessage(iss, LogLevel::INFO);
        } else if (command == "ERROR" || command == "3") {
            logMessage(iss, LogLevel::ERROR);
        } else {
            logMessage(input); // Log as message with default level if not recognized
        }
    }

    void logMessage(const std::string& message) {
        std::thread logThread([&, message] { logger_.log(message); });
        logThread.detach();
    }

    void logMessage(std::istringstream& iss, LogLevel level) {
        std::string message;
        std::getline(iss >> std::ws, message); // Read the rest of the line as the message
        std::thread logThread([&, message, level] { logger_.log(message, level); });
        logThread.detach();
    }

    void setLevel(const std::string& levelStr) {
        LogLevel level;
        if (levelStr == "DEBUG") {
            level = LogLevel::DEBUG;
        } else if (levelStr == "INFO") {
            level = LogLevel::INFO;
        } else if (levelStr == "ERROR") {
            level = LogLevel::ERROR;
        } else {
            std::cerr << "Invalid log level: " << levelStr << std::endl;
            return;
        }
        logger_.setLevel(level);
        std::cout << "Default log level set to: " << level << std::endl;
    }

private:
    Logger logger_;
    std::string logFileName_;
};

LogLevel parseLogLevel(const std::string& levelString) {
    if (levelString == "DEBUG") return LogLevel::DEBUG;
    if (levelString == "INFO") return LogLevel::INFO;
    if (levelString == "ERROR") return LogLevel::ERROR;
    return LogLevel::INFO; // Default to INFO if not recognized
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: app <log_file> <default_log_level>" << std::endl;
        return 1;
    }

    std::string logFile = argv[1];
    LogLevel defaultLevel = parseLogLevel(argv[2]);

    ConsoleApp app(logFile, defaultLevel);
    app.run();

    return 0;
}