#include <Scenes/StandardTextureScene.hpp>
#include <SceneManager.hpp>

// ==================================================== Setup ====================================================
StandardTextureScene::StandardTextureScene() {
    INIReader reader("Config.ini");
    title = reader.Get("Window", "title", "Window");
    screen_width = reader.GetInteger("Window", "width", 800);
    screen_height = reader.GetInteger("Window", "height", 600);
    fullscreen = reader.GetBoolean("Window", "fullscreen", false);
    resizable = reader.GetBoolean("Window", "resizable", true);
    
    window = Setup::complete_setup(title.c_str(), screen_width, screen_height, fullscreen, resizable);

    // Lock Mouse
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, Callbacks::mouse_callback);
}

void StandardTextureScene::load() {
    // Shapes
    squareShape.createSquare();

    // Load shaders
    standardShader.load("Shaders/standardTexture.vert", "Shaders/standardTexture.frag");

    // Load textures
    texture1.load("Media/Textures/container.jpg", &standardShader, "texture1");
    texture2.load("Media/Textures/awesomeface.png", &standardShader, "texture2");

    // Load objects
    square.load(squareShape, standardShader, {texture1, texture2}, glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, glm::vec3(0.5f));
}

// ==================================================== Main Loop ====================================================
void StandardTextureScene::update() {    
    // input
    processInput();

    // Move the square with sine
    offset = sin(glfwGetTime()) / 2.0f;
    square.setPosition(glm::vec3(offset, offset, 0.0f));
    square.setRotation(glfwGetTime() * -3.0f);

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void StandardTextureScene::render() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    square.render();
}

// =======================================================================================================

int StandardTextureScene::clean() {
    square.clean();

    glfwTerminate();
    return 0;
}

void StandardTextureScene::processInput()
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

GLFWwindow* StandardTextureScene::getWindow() {
    return window;
}

// Register this scene to the scene manager
namespace {
    bool isRegistered = []() {
        SceneManager::getInstance().registerScene("StandardTextureScene", []() -> std::shared_ptr<Scene> {
            return std::make_shared<StandardTextureScene>();
        });
        return true;
    }();
}
