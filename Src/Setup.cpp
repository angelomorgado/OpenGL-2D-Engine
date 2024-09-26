#include <Setup.hpp>

void Setup::glfw_setup() {
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif
}

GLFWwindow* Setup::window_setup(const char* title, int width, int height, bool fullscreen, bool resizable) {
    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, Callbacks::framebuffer_size_callback);

	if (fullscreen) {
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
        
        // Set the viewport to match the fullscreen resolution
        glViewport(0, 0, mode->width, mode->height);
	}

	if (resizable) {
		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	}

    return window;
}

void Setup::glad_setup() {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(-1);
	}
}

// prints all the relevant info
void Setup::printInfo() {
	std::cout << "=======================================================================\n";
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "=======================================================================\n";
}

// It automatically sets up everything and returns the window
GLFWwindow* Setup::complete_setup(const char* title, int width, int height, bool fullscreen, bool resizable)
{
    glfw_setup();
    GLFWwindow* window = window_setup(title, width, height, fullscreen, resizable);
    glad_setup();
	printInfo();

    // Z buffer (depth buffer)
	// glEnable(GL_DEPTH_TEST);

	return window;
}