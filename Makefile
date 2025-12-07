# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
LDFLAGS =

# Directories
SRC_DIR = src
INC_DIR = include
TEST_DIR = tests
OBJ_DIR = obj
BIN_DIR = bin

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
MAIN_OBJ = $(OBJ_DIR)/main.o
TARGET = $(BIN_DIR)/aging_demo.exe

# Test files
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJECTS = $(TEST_SOURCES:$(TEST_DIR)/%.cpp=$(OBJ_DIR)/test_%.o)
TEST_TARGET = $(BIN_DIR)/test_runner.exe

# Default target
.PHONY: all
all: $(TARGET)

# Build main executable
$(TARGET): $(OBJECTS) $(MAIN_OBJ) | $(BIN_DIR)
	$(CXX) $^ -o $@ $(LDFLAGS)
	@echo "Build complete: $(TARGET)"

# Compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile main file
$(MAIN_OBJ): main.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile test files
$(OBJ_DIR)/test_%.o: $(TEST_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create directories
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Build tests (if any)
.PHONY: test
test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(OBJECTS) $(TEST_OBJECTS) | $(BIN_DIR)
	$(CXX) $^ -o $@ $(LDFLAGS)
	@echo "Test build complete: $(TEST_TARGET)"

# Run the program
.PHONY: run
run: $(TARGET)
	./$(TARGET)

# Clean build artifacts
.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "Clean complete"

# Rebuild everything
.PHONY: rebuild
rebuild: clean all

# Display help
.PHONY: help
help:
	@echo "Available targets:"
	@echo "  make          - Build the project"
	@echo "  make all      - Build the project (default)"
	@echo "  make run      - Build and run the program"
	@echo "  make test     - Build and run tests"
	@echo "  make clean    - Remove build artifacts"
	@echo "  make rebuild  - Clean and rebuild"
	@echo "  make help     - Display this help message"

# Debug target with additional flags
.PHONY: debug
debug: CXXFLAGS += -g -DDEBUG
debug: clean all
	@echo "Debug build complete"

# Release target with optimization
.PHONY: release
release: CXXFLAGS += -O3 -DNDEBUG
release: clean all
	@echo "Release build complete"

# Dependencies
-include $(OBJECTS:.o=.d)
-include $(MAIN_OBJ:.o=.d)
