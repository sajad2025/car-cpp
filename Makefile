CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
INCLUDES = -Isrc
SRC_DIR = src
BUILD_DIR = build
TARGET = $(BUILD_DIR)/car_sim

# Source files
SRCS = $(SRC_DIR)/main.cpp \
       $(SRC_DIR)/vehicle_model.cpp \
       $(SRC_DIR)/control.cpp \
       $(SRC_DIR)/utils.cpp

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
OBJS := $(OBJS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Create build directory
$(shell mkdir -p $(BUILD_DIR))

# Main target
all: $(TARGET)

# Link
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

# Compile .cpp files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<

# Compile .c files (for vahicle_model.c)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean 