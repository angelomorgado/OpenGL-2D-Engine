# Compiler and flags
CXX := g++
CXXFLAGS := -g -std=c++17 -IInclude -IDependencies/Include -IDependencies/Include/imgui -IDependencies/Include/freetype2
LDFLAGS := -LLib -lglfw3dll -lfreetype

# Source and build directories
SRC_DIR := Src
DEPS_SRC_DIR := Dependencies/Src
BUILD_DIR := build
SCENES_SRC_DIR := Src/Scenes

# Find all .cpp source files
SRCS := $(wildcard $(SRC_DIR)/*.cpp) \
        $(wildcard $(SCENES_SRC_DIR)/*.cpp) \
        $(wildcard $(DEPS_SRC_DIR)/*.c*) \
        $(wildcard $(DEPS_SRC_DIR)/imgui/*)

# Convert source files to object files
OBJS := $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(notdir $(SRCS)))
OBJS := $(patsubst %.c, $(BUILD_DIR)/%.o, $(OBJS))

# Output executable
OUTPUT := Main.exe

# Default target
all: $(OUTPUT)

# Create the output executable by linking object files
$(OUTPUT): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Compile each source file into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SCENES_SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(DEPS_SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(DEPS_SRC_DIR)/imgui/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean the build directory
clean:
	rm -rf $(BUILD_DIR)/*.o $(OUTPUT)

.PHONY: clean
