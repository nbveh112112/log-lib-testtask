CXX = g++
CXXFLAGS = -std=c++17 -Wall -fPIC

# Директории
LIB_DIR = lib
APP_DIR = app
BUILD_DIR = build

# Имена файлов
LIB_NAME = liblogger.so
APP_NAME = app

# Цели
all: $(BUILD_DIR)/$(LIB_NAME) $(BUILD_DIR)/$(APP_NAME)

$(BUILD_DIR)/$(LIB_NAME): $(LIB_DIR)/logger.h $(LIB_DIR)/logger.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -shared -o $(BUILD_DIR)/$(LIB_NAME) $(LIB_DIR)/logger.cpp

$(BUILD_DIR)/$(APP_NAME): $(APP_DIR)/main.cpp $(BUILD_DIR)/$(LIB_NAME)
	$(CXX) $(CXXFLAGS) -I$(LIB_DIR) -o $(BUILD_DIR)/$(APP_NAME) $(APP_DIR)/main.cpp -L$(BUILD_DIR) -Wl,-rpath,$(BUILD_DIR) -llogger -lpthread

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean