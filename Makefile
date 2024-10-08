# Compiler
CXX = g++
CXXFLAGS = -g -std=c++17 -IInclude -IDependencies/Include -IDependencies/Include/imgui

# Linker flags
LDFLAGS = -LDependencies/Lib -lglfw -lGL -ldl -lpthread -lX11 -lXrandr -lXi -lXxf86vm -lXcursor -lXinerama -lXext -lXrender -lGLU -lfreetype

# Source files
SRC = $(wildcard Src/*.cpp Src/Scenes/*.cpp Dependencies/Src/*.c* Dependencies/Src/imgui/*.cpp)

# Output executable
OUT = Main

# Default target
all: $(OUT)

# Build the executable
$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(LDFLAGS) -o $(OUT)

# Clean target to remove compiled files
clean:
	rm -f $(OUT)
