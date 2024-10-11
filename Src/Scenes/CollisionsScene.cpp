#include <Scenes/CollisionsScene.hpp>
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
CollisionsScene::CollisionsScene() {
    INIReader reader("Config.ini");
    title = "Collisions Scene";
    screen_width = reader.GetInteger("Window", "width", 800);
    screen_height = reader.GetInteger("Window", "height", 600);
    fullscreen = reader.GetBoolean("Window", "fullscreen", false);
    resizable = reader.GetBoolean("Window", "resizable", true);
    
    window = Setup::complete_setup(title.c_str(), screen_width, screen_height, fullscreen, resizable);

    // Lock Mouse
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, Callbacks::mouse_callback);
}

void CollisionsScene::load() {
    // Shapes
    shape1.createSquare();
    shape2.createCircle();

    // Load shaders
    textureShader.load("Shaders/standardTexture.vert", "Shaders/standardTexture.frag");
    standardShader.load("standardTexture");
    textShader.load("text");

    // Load textures
    texture1.load("Media/Textures/container.jpg", "texture1");
    texture2.load("Media/Textures/awesomeface.png", "texture2");

    // Load objects
    circle.load(shape2, textureShader, {texture2}, glm::vec2(-0.3f, 0.0f), 0.0f, glm::vec2(0.3f));
    square.load(shape1, textureShader, {texture1, texture2}, glm::vec2(0.3f, 0.0f), 0.0f, glm::vec2(0.3f));

    // Set the speed and direction
    speed = 0.002f;
    direction = glm::vec2(1.0f, 1.0f);
    flag = false;

    font1.loadFont("Media/Fonts/Roboto-Regular.ttf", 48, textShader, screen_width, screen_height);

    // Audio
    if (ma_engine_init(nullptr, &audioEngine) != MA_SUCCESS) {
        std::cout << "Failed to initialize audio engine\n";
    }
}

// ==================================================== Main Loop ====================================================
void CollisionsScene::update() {    
    // input
    processInput();

    // Move the square with sine
    offset = sin(glfwGetTime()) / 3.0f;
    square.setPosition(glm::vec2(offset));

    if (Collisions::checkCircleCollision(circle, square)) {
        square.setColor(glm::vec3(1.0f, 0.0f, 1.0f));
        circle.setColor(glm::vec3(1.0f, 0.0f, 1.0f));
        if(!flag) {
            ma_engine_play_sound(&audioEngine, "Media/Sounds/bleep.mp3", NULL);
            flag = true;
        }
    } else {
        square.setColor(glm::vec3(1.0f));
        circle.setColor(glm::vec3(1.0f));
        flag = false;
    }

    borderCollision(circle);
    circle.move(direction * speed);

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void CollisionsScene::render() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // The order in wich the objects are rendered is important
    square.render();
    circle.render();
    font1.renderText("Collisions Scene", glm::vec2(10.0f, 10.0f), 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
}


// ==================================================== Collision Detection ====================================================

// Check if the object is colliding with the borders of the window
void CollisionsScene::borderCollision(Object& obj) {
    switch (Collisions::checkWindowCollision(obj)) {
        // Top, Bottom
        case 2:
        case 3:
            direction.y = -direction.y;
            break;

        // Left, Right
        case 4:
        case 5:
            direction.x = -direction.x;
            break;

        // Corners
        case 6:
        case 7:
        case 8:
            direction.x = -direction.x;
            direction.y = -direction.y;
            break;

        default:
            break;
    }
}
// =======================================================================================================

int CollisionsScene::clean() {
    square.clean();
    circle.clean();
    texture1.clean();
    texture2.clean();
    standardShader.clean();
    textureShader.clean();
    textShader.clean();
    font1.clean();
    ma_engine_uninit(&audioEngine);

    glfwTerminate();
    return 0;
}

void CollisionsScene::processInput()
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

GLFWwindow* CollisionsScene::getWindow() {
    return window;
}

// Register this scene to the scene manager
namespace {
    bool isRegistered = []() {
        SceneManager::getInstance().registerScene("CollisionsScene", []() -> std::shared_ptr<Scene> {
            return std::make_shared<CollisionsScene>();
        });
        return true;
    }();
}
