cmake_minimum_required(VERSION 3.10)

project(OpenGLProject VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/Include
    ${CMAKE_SOURCE_DIR}/Dependencies/Include
    ${CMAKE_SOURCE_DIR}/Dependencies/Include/imgui
    ${CMAKE_SOURCE_DIR}/Dependencies/Include/freetype2
)

# Find all source files
file(GLOB_RECURSE SOURCES 
    "${CMAKE_SOURCE_DIR}/Src/*.cpp"
    "${CMAKE_SOURCE_DIR}/Src/Scenes/*.cpp"
    "${CMAKE_SOURCE_DIR}/Dependencies/Src/*.c*"
    "${CMAKE_SOURCE_DIR}/Dependencies/Src/imgui/*"
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Add library directories
link_directories(${CMAKE_SOURCE_DIR}/Lib)

# Find libraries
find_library(GLFW_LIBRARY glfw3dll PATHS ${CMAKE_SOURCE_DIR}/Lib)
find_library(FREETYPE_LIBRARY freetype PATHS ${CMAKE_SOURCE_DIR}/Lib)

# Link libraries
target_link_libraries(${PROJECT_NAME} 
    ${GLFW_LIBRARY}
    ${FREETYPE_LIBRARY}
)

# Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)

# Rename output to Main.exe
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "Main")

# Print some debug information
message(STATUS "GLFW_LIBRARY: ${GLFW_LIBRARY}")
message(STATUS "FREETYPE_LIBRARY: ${FREETYPE_LIBRARY}")