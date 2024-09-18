#include <Callbacks.hpp>

void Callbacks::processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// Whenever the window size changed (by OS or user resize) this callback function executes
void Callbacks::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// This callback function handles the mouse input
void Callbacks::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    std::cout << "Mouse position: " << xpos << ", " << ypos << std::endl;
}


