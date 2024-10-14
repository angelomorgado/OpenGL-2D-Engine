#include <Scenes/CircleInsideSquareScene.hpp>
#include <SceneManager.hpp>

#include <Collisions.hpp>
#include <Callbacks.hpp>
#include <INIReader.h>

// ==================================================== Setup ====================================================
CircleInsideSquareScene::CircleInsideSquareScene() {
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

void CircleInsideSquareScene::load() {
    // Shapes
    shape1.createSquare();
    shape2.createCircle();

    // Load shaders
    textureShader.load("Shaders/standardTexture.vert", "Shaders/standardTexture.frag");
    standardShader.load("standardTexture");

    // Load textures
    texture1.load("Media/Textures/container.jpg");
    texture2.load("Media/Textures/awesomeface.png");

    // Load objects
    circle.load(shape2, glm::vec2(0.0f, 0.05f), 0.0f, glm::vec2(0.1f));
    square.load(shape1, glm::vec2(0.0f, 0.0f), 0.0f, glm::vec2(0.5f));

    // Set the speed and direction
    speed = 0.002f;
    direction = glm::vec2(1.0f, 1.0f);
}

// ==================================================== Main Loop ====================================================
void CircleInsideSquareScene::update() {    
    // input
    processInput();

    isInside(circle, square);
    circle.move(direction * speed);

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void CircleInsideSquareScene::render() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // The order in wich the objects are rendered is important
    square.render(textureShader, texture1);
    circle.render(textureShader, texture2);
}

// ==================================================== Collision Detection ====================================================
// Keep obj1 inside obj2
void CircleInsideSquareScene::isInside(Object& obj1, Object& obj2) {
    glm::vec2 obj1Size     = obj1.getSize();
    glm::vec2 obj1Position = obj1.getPosition();
    
    glm::vec2 obj2Size     = obj2.getSize();
    glm::vec2 obj2Position = obj2.getPosition();

    glm::vec2 obj1HalfSize = obj1Size / 2.0f;
    glm::vec2 obj2HalfSize = obj2Size / 2.0f;

    switch (Collisions::detectBoundaryOverlap(obj1, obj2)) {
        // Top
        case 2:
            obj1Position.y = obj2Position.y + obj2HalfSize.y - obj1HalfSize.y - 0.01f;  // Push obj1 back inside
            direction.y = -direction.y;
            break;
        // Bottom
        case 3:
            obj1Position.y = obj2Position.y - obj2HalfSize.y + obj1HalfSize.y + 0.01f;  // Push obj1 back inside
            direction.y = -direction.y;
            break;

        // Left
        case 4:
            obj1Position.x = obj2Position.x + obj2HalfSize.x - obj1HalfSize.x - 0.01f;  // Push obj1 back inside
            direction.x = -direction.x;
            break;
        // Right
        case 5:
            obj1Position.x = obj2Position.x - obj2HalfSize.x + obj1HalfSize.x + 0.01f;  // Push obj1 back inside
            direction.x = -direction.x;
            break;
        case 6:
        case 7:
        case 8:
            direction.x = -direction.x;
            direction.y = -direction.y;
            break;
        default:
            break;
    }

    // Update obj1's position after handling the collisions
    obj1.setPosition(obj1Position);
}

// =======================================================================================================
int CircleInsideSquareScene::clean() {
    square.clean();
    circle.clean();
    texture1.clean();
    texture2.clean();
    standardShader.clean();
    textureShader.clean();

    glfwTerminate();
    return 0;
}

void CircleInsideSquareScene::processInput()
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        square.move(glm::vec2(0.0f, speed/2.0f));
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        square.move(glm::vec2(0.0f, -speed/2.0f));
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        square.move(glm::vec2(-speed/2.0f, 0.0f));
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        square.move(glm::vec2(speed/2.0f, 0.0f));
}

GLFWwindow* CircleInsideSquareScene::getWindow() {
    return window;
}

// Register this scene to the scene manager
namespace {
    bool isRegistered = []() {
        SceneManager::getInstance().registerScene("CircleInsideSquareScene", []() -> std::shared_ptr<Scene> {
            return std::make_shared<CircleInsideSquareScene>();
        });
        return true;
    }();
}
