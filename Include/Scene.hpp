#ifndef SCENE_HPP
#define SCENE_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <vector>

class Scene {
public:
    virtual ~Scene() = default;
    virtual void load() = 0;   // Load the scene assets
    virtual void update() = 0; // Update scene state
    virtual void render() = 0; // Render the scene
    virtual int clean() = 0; // Clean the scene
    virtual GLFWwindow* getWindow() = 0; // Get the window
};

#endif // SCENE_HPP