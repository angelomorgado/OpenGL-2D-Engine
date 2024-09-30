#include <Scenes/CollisionsScene.hpp>
#include <SceneManager.hpp>

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

    // Load textures
    texture1.load("Media/Textures/container.jpg", "texture1");
    texture2.load("Media/Textures/awesomeface.png", "texture2");

    // Load objects
    circle.load(shape2, textureShader, {texture2}, glm::vec2(0.0f, 0.0f), 0.0f, glm::vec2(0.3f));
    square.load(shape1, textureShader, {texture1, texture2}, glm::vec2(0.0f, 0.0f), 0.0f, glm::vec2(0.3f));
}

// ==================================================== Main Loop ====================================================
void CollisionsScene::update() {    
    // input
    processInput();

    // Move the square with sine
    // offset = sin(glfwGetTime()) / 2.0f;
    // square.setPosition(glm::vec3(offset, offset, 0.0f));
    // square.setRotation(glfwGetTime() * -3.0f);

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
}


// ==================================================== Collision Detection ====================================================
bool CollisionsScene::checkAABBCollision(Object& obj1, Object& obj2) {
    glm::vec2 obj1Position = obj1.getPosition();
    glm::vec2 obj1Size = obj1.getScale();
    glm::vec2 obj2Position = obj2.getPosition();
    glm::vec2 obj2Size = obj2.getScale();

    // collision x-axis?
    bool collisionX = obj1Position.x + obj1Size.x >= obj2Position.x &&
        obj2Position.x + obj2Size.x >= obj1Position.x;
    // collision y-axis?
    bool collisionY = obj1Position.y + obj1Size.y >= obj2Position.y &&
        obj2Position.y + obj2Size.y >= obj1Position.y;
    // collision only if on both axes
    return collisionX && collisionY;
}  

bool CollisionsScene::checkCircleCollision(Object& obj1, Object& obj2) {
    // Get the distance between the two objects
    glm::vec2 distance = obj1.getPosition() - obj2.getPosition();
    float length = glm::length(distance);

    // Get the sum of the two objects' scales
    float scaleSum = obj1.getScale().x + obj2.getScale().x;

    // If the distance is less than the sum of the scales, then the objects are colliding
    return length < scaleSum;
}

// =======================================================================================================

int CollisionsScene::clean() {
    square.clean();
    circle.clean();
    texture1.clean();
    texture2.clean();
    standardShader.clean();
    textureShader.clean();

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
