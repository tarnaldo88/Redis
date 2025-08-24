# Compiler
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
DEPFLAGS = -MMD -MP
CPPFLAGS = -I. -IClient

# Platform detection (Windows via MSYS2/MinGW vs Linux)
ifeq ($(OS),Windows_NT)
  EXE_EXT := .exe
  PLATFORM_LIBS := -lws2_32
  PLATFORM := windows
else
  EXE_EXT :=
  PLATFORM_LIBS :=
  PLATFORM := linux
endif

# Directories
SRC_DIR = Client
BUILD_DIR = build/$(PLATFORM)
BIN_DIR = bin/$(PLATFORM)

# Find all .cpp files in project (exclude root CLI.cpp to avoid duplicate with Client/CLI.cpp)
SRCS := $(filter-out CLI.cpp,$(wildcard *.cpp)) $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Output binary
TARGET = $(BIN_DIR)/my_redis_cli$(EXE_EXT)

# Default rule
all: $(TARGET)

# Create build and bin directories if they don’t exist
$(BUILD_DIR) $(BIN_DIR):
	mkdir -p $@

# Compile each .cpp file into .o files (mirror subdirectories under build/)
$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) $(CPPFLAGS) -c $< -o $@

# Link the object files to create the executable
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(PLATFORM_LIBS)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Remove all build artifacts for all platforms
distclean:
	rm -rf build bin

# Rebuild from scratch
rebuild: clean all

# Run the compiled binary
run: all
	./$(TARGET)

# Include auto-generated dependency files
-include $(OBJS:.o=.d)