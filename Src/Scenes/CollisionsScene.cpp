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
    circle.load(shape2, textureShader, {texture2}, glm::vec2(-0.3f, 0.0f), 0.0f, glm::vec2(0.3f));
    square.load(shape1, textureShader, {texture1, texture2}, glm::vec2(0.3f, 0.0f), 0.0f, glm::vec2(0.3f));

    // Set the speed and direction
    speed = 0.002f;
    direction = glm::vec2(1.0f, 1.0f);
}

// ==================================================== Main Loop ====================================================
void CollisionsScene::update() {    
    // input
    processInput();

    // Move the square with sine
    offset = sin(glfwGetTime()) / 3.0f;
    square.setPosition(glm::vec2(offset));
    circle.setPosition(glm::vec2(-offset));

    if (checkCircleCollision(circle, square)) {
        square.setColor(glm::vec3(1.0f, 0.0f, 0.0f));
        circle.setColor(glm::vec3(1.0f, 0.0f, 0.0f));
    } else {
        square.setColor(glm::vec3(1.0f));
        circle.setColor(glm::vec3(1.0f));
    }

    // borderCollision(circle);
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
}


// ==================================================== Collision Detection ====================================================
bool CollisionsScene::checkCircleCollision(Object& circle, Object& square) {
    // Get center point of circle
    glm::vec2 circle_center = circle.getPosition();

    // Calculate AABB info (center, half-extents)
    glm::vec2 aabb_half_extents = square.getSize() / 2.0f;
    glm::vec2 aabb_center = square.getPosition();

    // Get difference vector between both centers
    glm::vec2 difference = circle_center - aabb_center;
    glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);

    // Add clamped value to AABB_center and we get the value of box closest to circle
    glm::vec2 closest = aabb_center + clamped;

    // Retrieve vector between center circle and closest point AABB and check if length <= radius
    difference = closest - circle_center;

    return glm::length(difference) < circle.getSize().x / 2.0f;
}

// Check if the object is colliding with the borders of the window
void CollisionsScene::borderCollision(Object& obj) {
    glm::vec2 objSize     = obj.getSize();
    glm::vec2 objPosition = obj.getPosition();

    // Y axis
    // Top
    if(objPosition.y + objSize.y/2.0f >= 1.0f) {
        direction.y = -direction.y;
        std::cout << "Top" << std::endl;
    // Bottom
    } else if(objPosition.y - objSize.y/2.0f <= -1.0f) {
        direction.y = -direction.y;
        std::cout << "Bottom" << std::endl;
    
    // X axis
    // Left
    } if(objPosition.x - objSize.x/2.0f <= -1.0f) {
        direction.x = -direction.x;
        std::cout << "Left" << std::endl;
    // Right
    } else if(objPosition.x + objSize.x/2.0f >= 1.0f) {
        direction.x = -direction.x;
        std::cout << "Right" << std::endl;
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
