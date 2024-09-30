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
    circle.load(shape2, textureShader, {texture2}, glm::vec2(0.0f, 0.0f), 0.0f, glm::vec2(0.1f));
    square.load(shape1, textureShader, {texture1, texture2}, glm::vec2(0.0f, 0.0f), 0.0f, glm::vec2(0.5f));

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
    square.setPosition(glm::vec2(0.0, offset));

    if (circle.isColliding(square)) {
        square.setColor(glm::vec3(1.0f, 0.0f, 0.0f));
        circle.setColor(glm::vec3(1.0f, 0.0f, 0.0f));
    } else {
        square.setColor(glm::vec3(1.0f));
        circle.setColor(glm::vec3(1.0f));
    }

    // borderCollision(circle);
    isInside(circle, square);
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
bool CollisionsScene::checkCircleCollision(Object& obj1, Object& obj2) {
    // Get center point of circle
    glm::vec2 circle_center = obj1.getPosition();

    // Calculate AABB info (center, half-extents)
    glm::vec2 aabb_half_extents = obj2.getScale() / 2.0f;
    glm::vec2 aabb_center = obj2.getPosition() + aabb_half_extents;

    // Get difference vector between both centers
    glm::vec2 difference = circle_center - aabb_center;
    glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);

    // Add clamped value to AABB_center and we get the value of box closest to circle
    glm::vec2 closest = aabb_center + clamped;

    // Retrieve vector between center circle and closest point AABB and check if length <= radius
    difference = closest - circle_center;

    return glm::length(difference) < obj1.getShape().radius;
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

// Checks if obj1 is inside obj2
void CollisionsScene::isInside(Object& obj1, Object& obj2) {
    glm::vec2 obj1Size     = obj1.getSize();
    glm::vec2 obj1Position = obj1.getPosition();
    
    glm::vec2 obj2Size     = obj2.getSize();
    glm::vec2 obj2Position = obj2.getPosition();

    // Calculate half sizes for easier boundary checking
    glm::vec2 obj1HalfSize = obj1Size / 2.0f;
    glm::vec2 obj2HalfSize = obj2Size / 2.0f;

    // Check for Y-axis boundaries
    // Top
    if (obj1Position.y + obj1HalfSize.y > obj2Position.y + obj2HalfSize.y) {
        obj1Position.y = obj2Position.y + obj2HalfSize.y - obj1HalfSize.y - 0.01f;  // Push obj1 back inside
        direction.y = -direction.y;
        std::cout << "Hit Top Boundary" << std::endl;
    }
    // Bottom
    if (obj1Position.y - obj1HalfSize.y < obj2Position.y - obj2HalfSize.y) {
        obj1Position.y = obj2Position.y - obj2HalfSize.y + obj1HalfSize.y + 0.01f;  // Push obj1 back inside
        direction.y = -direction.y;
        std::cout << "Hit Bottom Boundary" << std::endl;
    }

    // Check for X-axis boundaries
    // Right
    if (obj1Position.x + obj1HalfSize.x > obj2Position.x + obj2HalfSize.x) {
        obj1Position.x = obj2Position.x + obj2HalfSize.x - obj1HalfSize.x - 0.01f;  // Push obj1 back inside
        direction.x = -direction.x;
        std::cout << "Hit Right Boundary" << std::endl;
    }
    // Left
    if (obj1Position.x - obj1HalfSize.x < obj2Position.x - obj2HalfSize.x) {
        obj1Position.x = obj2Position.x - obj2HalfSize.x + obj1HalfSize.x + 0.01f;  // Push obj1 back inside
        direction.x = -direction.x;
        std::cout << "Hit Left Boundary" << std::endl;
    }

    // Update obj1's position after handling the collisions
    obj1.setPosition(obj1Position);
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

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        square.move(glm::vec2(0.0f, speed));
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        square.move(glm::vec2(0.0f, -speed));
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        square.move(glm::vec2(-speed, 0.0f));
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        square.move(glm::vec2(speed, 0.0f));
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
