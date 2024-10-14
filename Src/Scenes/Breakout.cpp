#include <Scenes/Breakout.hpp>
#include <SceneManager.hpp>

#include <iostream>
#include <Callbacks.hpp>
#include <Setup.hpp>
#include <Shader.hpp>
#include <Collisions.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <INIReader.h>

// ==================================================== Setup ====================================================
Breakout::Breakout() {
    INIReader reader("Config.ini");
    title = "Collisions Scene";
    screenWidth = reader.GetInteger("Window", "width", 800);
    screenHeight = reader.GetInteger("Window", "height", 600);
    fullscreen = reader.GetBoolean("Window", "fullscreen", false);
    resizable = reader.GetBoolean("Window", "resizable", true);
    
    window = Setup::complete_setup(title.c_str(), screenWidth, screenHeight, fullscreen, resizable);

    // Lock Mouse
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, Callbacks::mouse_callback);
}

void Breakout::load() {
    // Shapes
    squareShape.createSquare();
    circleShape.createCircle();

    // Load shaders
    textureShader.load("standardTexture");
    textShader.load("text");

    // Load textures
    boxTexture.load("Media/Textures/container.jpg");
    ballTexture.load("Media/Textures/awesomeface.png");

    // Load objects
    ball.load(circleShape, glm::vec2(0.0f, -0.8f), 0.0f, glm::vec2(0.3f));
    box.load(squareShape, glm::vec2(0.3f, 0.0f), 0.0f, glm::vec2(0.3f));
    paddle.load(squareShape, glm::vec2(0.0,-0.9), 0.0f, glm::vec2(0.3f, 0.05f));

    // Set the speed and direction
    ballSpeed = 0.002f;
    ballDirection = glm::vec2(0.0f, 1.0f);

    font1.loadFont("Media/Fonts/Roboto-Regular.ttf", 48, textShader, screenWidth, screenHeight);

    // Audio
    if (ma_engine_init(nullptr, &audioEngine) != MA_SUCCESS) {
        std::cout << "Failed to initialize audio engine\n";
    }
}

// ==================================================== Main Loop ====================================================
void Breakout::update() {    
    // input
    processInput();

    borderCollision(ball);
    ball.move(ballDirection * ballSpeed);

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Breakout::render() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render objects (The order matters)
    ball.render(textureShader, ballTexture);
    box.render(textureShader, boxTexture);
    paddle.render(textureShader, paddleTexture);

    // Render text
    font1.renderText("Collisions Scene", glm::vec2(10.0f, 10.0f), 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
}

// ==================================================== Collision Detection ====================================================

// Check if the object is colliding with the borders of the window
void Breakout::borderCollision(Object& obj) {
    switch (Collisions::checkWindowCollision(obj)) {
        // Top, Bottom
        case 2:
        case 3:
            ballDirection.y = -ballDirection.y;
            break;

        // Left, Right
        case 4:
        case 5:
            ballDirection.x = -ballDirection.x;
            break;

        // Corners
        case 6:
        case 7:
        case 8:
            ballDirection.x = -ballDirection.x;
            ballDirection.y = -ballDirection.y;
            break;

        default:
            break;
    }
}
// =======================================================================================================

int Breakout::clean() {
    ball.clean();
    box.clean();
    paddle.clean();
    ballTexture.clean();
    boxTexture.clean();
    paddleTexture.clean();
    textureShader.clean();
    textShader.clean();
    font1.clean();
    ma_engine_uninit(&audioEngine);

    glfwTerminate();
    return 0;
}

void Breakout::processInput()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        paddle.move(glm::vec2(-0.01f, 0.0f));
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        paddle.move(glm::vec2(0.01f, 0.0f));
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        std::cout << "Space pressed" << std::endl;
    }
}

GLFWwindow* Breakout::getWindow() {
    return window;
}

// Register this scene to the scene manager
namespace {
    bool isRegistered = []() {
        SceneManager::getInstance().registerScene("Breakout", []() -> std::shared_ptr<Scene> {
            return std::make_shared<Breakout>();
        });
        return true;
    }();
}
