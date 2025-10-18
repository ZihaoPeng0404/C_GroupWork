# Compiler and flags
CC = gcc
CFLAGS = -Wall -Werror -ansi -Iinclude

# Source and build directories
SRC_DIR = src
BUILD_DIR = build

# List all source files and corresponding object files
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))

# Output binary
TARGET = $(BUILD_DIR)/crystal_defense

# Default rule (release build)
all: $(BUILD_DIR) $(TARGET)

# Link object files into final executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

# Compile each .c file into .o inside build/
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Create build directory if it doesn’t exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Debug build (adds -g and defines DEBUG)
debug: CFLAGS += -g -DDEBUG
debug: clean all
	@echo "Debug build created."


# Clean build directory
clean:
	rm -rf $(BUILD_DIR)

# Run the game
run: all
	./$(TARGET)

.PHONY: all clean debug run
