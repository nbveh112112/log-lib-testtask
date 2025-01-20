## Project Structure

The project is organized as follows:

- `lib/`: Contains the source code for the dynamic library.
    - `logger.h`: Header file for the `Logger` class.
    - `logger.cpp`: Implementation of the `Logger` class.
- `app/`: Contains the source code for the console application.
    - `main.cpp`: The main source file for the application.
- `Makefile`: Used for building the library and application.
- `README.md`: This file, providing project documentation.

## Features

- **Dynamic Library:** The logger is implemented as a dynamic library (`liblogger.so`).
- **Log Levels:** Supports three log levels: `DEBUG`, `INFO`, and `ERROR`.
- **Customizable Log File:** The log file path and default level are configurable via command-line arguments.
- **Thread-Safe Logging:** Messages are logged in a thread-safe manner using a mutex.
- **Formatted Output:** Log messages include the timestamp, log level, and the message itself.
- **Interactive Console Application:** The application provides a command-line interface for logging messages with specific levels and setting the default level.
- **Input Validation:** Checks log file validity before starting.
- **Object-Oriented Design:** The application uses a `ConsoleApp` class to manage its functionality.
- **Easy to Use:** Simple syntax for logging messages and setting the default log level.

## Build Instructions

To build the project, you need `g++` and `make` installed on your system.

1.  Clone the repository:
    ```bash
    git clone <your-repository-url>
    cd <your-repository-name>
    ```
2.  Run `make` in the root directory:
    ```bash
    make
    ```
    This will compile the library (`liblogger.so`) and the application (`app`) and place the files in the `build` folder.

## Run Instructions

To run the application:

1.  Execute the following command:
    ```bash
    ./build/app <log_file> <default_log_level>
    ```
    Where:
    - `<log_file>` is the path to the log file (e.g., `log.txt`).
    - `<default_log_level>` is the initial log level (`DEBUG`, `INFO`, or `ERROR`).

2.  Once the application starts, you can use the following commands:
    ```
    Usage:
      <message>              Log message with default level.
      DEBUG <message>        Log message with DEBUG level.
      INFO <message>         Log message with INFO level.
      ERROR <message>        Log message with ERROR level.
      1 <message>            Log message with DEBUG level.
      2 <message>            Log message with INFO level.
      3 <message>            Log message with ERROR level.
      set <level>            Set default log level (DEBUG, INFO, ERROR).
    ```

**Examples**

```bash
> Hello, world!   # Logs the message with default level
> DEBUG This is a debug message  # Logs the message with DEBUG level
> 1 This is a debug message too # Logs the message with DEBUG level
> set ERROR   # Sets the default log level to ERROR
> INFO This is info message     # Logs the message with INFO level
> 2 This is info message too    # Logs the message with INFO level
> ERROR This is error message   # Logs the message with ERROR level
> 3 This is error message too    # Logs the message with ERROR level