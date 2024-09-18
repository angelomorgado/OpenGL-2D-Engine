// In this page we define the various callbacks functions, if we need to use the same callbacks in multiple scenes we can define them here and call them from the scene. This way we can avoid code duplication and keep the code clean and organized, such as keybindings, mouse input, etc.
#include <Callbacks.hpp>

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
    // std::cout << "Mouse position: " << xpos << ", " << ypos << std::endl;
}


