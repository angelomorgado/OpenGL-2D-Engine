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

# Find source files
file(GLOB_RECURSE SCENE_SOURCES "${CMAKE_SOURCE_DIR}/Src/Scenes/*.cpp")
file(GLOB_RECURSE OTHER_SOURCES 
    "${CMAKE_SOURCE_DIR}/Src/*.cpp"
    "${CMAKE_SOURCE_DIR}/Dependencies/Src/*.c*"
    "${CMAKE_SOURCE_DIR}/Dependencies/Src/imgui/*"
)
list(REMOVE_ITEM OTHER_SOURCES ${SCENE_SOURCES})

# Create object libraries
add_library(SceneObjects OBJECT ${SCENE_SOURCES})
add_library(OtherObjects OBJECT ${OTHER_SOURCES})

# Create executable
add_executable(${PROJECT_NAME} $<TARGET_OBJECTS:SceneObjects> $<TARGET_OBJECTS:OtherObjects>)

# Add library directories
link_directories(${CMAKE_SOURCE_DIR}/Dependencies/Lib)

# Find libraries
find_library(GLFW_LIBRARY glfw3dll PATHS ${CMAKE_SOURCE_DIR}/Dependencies/Lib)
find_library(FREETYPE_LIBRARY freetype PATHS ${CMAKE_SOURCE_DIR}/Dependencies/Lib)

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

# Copy all DLLs from dependencies/bin to output directory
file(GLOB_RECURSE DLLS "${CMAKE_SOURCE_DIR}/Dependencies/Bin/*.dll")
file(COPY ${DLLS} DESTINATION ${CMAKE_SOURCE_DIR})

# Print some debug information
message(STATUS "GLFW_LIBRARY: ${GLFW_LIBRARY}")
message(STATUS "FREETYPE_LIBRARY: ${FREETYPE_LIBRARY}")