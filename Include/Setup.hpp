/*
Initialization.hpp
    - Deals with the setup of the window, OpenGL, etc.
*/

#ifndef SETUP_HPP
#define SETUP_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Setup{
    public:
        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
        static void glfw_setup();
        static GLFWwindow* window_setup(const char* title = "Window", int width = 800, int height = 600, bool fullscreen = false, bool resizable = true);
        static void glad_setup();
        static void printInfo();
        static GLFWwindow* complete_setup(const char* title = "Window", int width = 800, int height = 600, bool fullscreen = false, bool resizable = true);
};

#endif