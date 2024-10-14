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
INIReader reader("Config/Breakout.ini");

/*
TODO:
- Make more types of levels (e.g., footbal, futuristic, default)
- Implement random levels
- Make lose/win conditions
- Make it harder with time
- HUD
- Music
- Different Block types
- Powerups
*/

Breakout::Breakout() {
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
    screenShape.createScreen();

    // Load shaders
    boxShader.load("standard");
    textureShader.load("standardTexture");
    textShader.load("text");
    screenShader.load("noColorTexture");
    screenShader.use();
    screenShader.setVec3("customColor", glm::vec3(0.1, 1.0, 0.1));

    // Load textures
    boxTexture.load("Media/Textures/container.jpg");
    ballTexture.load("Media/Textures/football.png");
    paddleTexture.load("Media/Textures/paddle-goal.png");
    screenTexture.load("Media/Textures/football-field.jpg");
    screenTexture.setWrappingParameters(GL_REPEAT, GL_CLAMP_TO_BORDER);

    // Load objects
    ball.load(circleShape, glm::vec2(0.0f, -0.8f), 0.0f, glm::vec2(0.05f));
    float boxMult = reader.GetReal("Game", "boxSizeMultiplier", 1.0);
    box.load(squareShape, glm::vec2(0.3f, 0.0f), 0.0f, glm::vec2(0.1f, 0.05) * boxMult);
    paddle.load(squareShape, glm::vec2(0.0,-0.9), 0.0f, glm::vec2(0.3f, 0.05f));
    screen.load(screenShape);

    // Set the speed and direction
    ballSpeed = reader.GetReal("Game", "ballSpeed", 2.0) / 100;
    ballDirection = glm::vec2(1.0f, 1.0f);
    paddleSpeed = reader.GetReal("Game", "paddleSpeed", 3.0) / 100;

    font1.loadFont("Media/Fonts/Roboto-Regular.ttf", 48, textShader, screenWidth, screenHeight);

    // Audio
    if (ma_engine_init(nullptr, &audioEngine) != MA_SUCCESS) {
        std::cout << "Failed to initialize audio engine\n";
    }

    // Box field
    bool field[4][9] = {{1, 1, 1, 1, 1, 1, 1, 1, 1},
                        {1, 1, 1, 1, 1, 1, 1, 1, 1},
                        {1, 1, 1, 1, 1, 1, 1, 1, 1},
                        {1, 1, 1, 1, 1, 1, 1, 1, 1}};

    // Manually copy values using loops
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 9; j++) {
            boxesField[i][j] = field[i][j];
        }
    }

    setupBoxPositions();
}

// ==================================================== Main Loop ====================================================
void Breakout::update() {    
    // input
    processInput();

    borderCollision(ball);
    checkBoxBallCollision();
    checkPaddleBallCollision();
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
    screen.render(screenShader, screenTexture);
    ball.render(textureShader, ballTexture);
    drawBoxField();
    paddle.render(textureShader, paddleTexture);

    // Render text
    // font1.renderText("Collisions Scene", glm::vec2(10.0f, 10.0f), 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
}

void Breakout::drawBoxField() { 
    glm::vec3 boxColor = glm::vec3(0.0, 1.0, 0.0);
    boxShader.use();
    for (int i=0; i<4; i++) {
        // 9 columns
        for (int j=0; j<9; j++) {
            if (boxesField[i][j]) {
                box.setPosition(boxesPosition[i][j]);
                boxShader.setVec3("customColor", boxColor);
                box.render(boxShader);
            }
        }
        boxColor.x += 0.1;
        boxColor.z += 0.1;
    }
    textureShader.setVec3("customColor", glm::vec3(1.0));
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

void Breakout::checkPaddleBallCollision() {
    unsigned int collision = Collisions::checkCircleCollisionComplex(ball, paddle);
    if (collision) {
        ma_engine_play_sound(&audioEngine, "Media/Sounds/bleep1.wav", NULL);
        
        if (collision == 1) {
            ballDirection.y = -ballDirection.y;
        }
        else if (collision == 2) {
            ballDirection.x = -ballDirection.x;
        } else {
            ballDirection.y = -ballDirection.y;
            ballDirection.x = -ballDirection.x;
        }
    }
}

void Breakout::checkBoxBallCollision() {
    for (int i=0; i<4; i++) {
        // 9 columns
        for (int j=0; j<9; j++) {
            box.setPosition(boxesPosition[i][j]);
            if (boxesField[i][j]) {
                unsigned int collision = Collisions::checkCircleCollisionComplex(ball, box);

                if (collision == 1) {
                    ballDirection.y = -ballDirection.y;
                    ma_engine_play_sound(&audioEngine, "Media/Sounds/bleep2.mp3", NULL);
                    boxesField[i][j] = false;
                    return;
                } else if (collision == 2) {
                    ballDirection.x = -ballDirection.x;
                    ma_engine_play_sound(&audioEngine, "Media/Sounds/bleep2.mp3", NULL);
                    boxesField[i][j] = false;
                    return;
                } else if (collision == 3){
                    ballDirection.y = -ballDirection.y;
                    ballDirection.x = -ballDirection.x;
                    ma_engine_play_sound(&audioEngine, "Media/Sounds/bleep2.mp3", NULL);
                    boxesField[i][j] = false;
                    return;
                }
            }
        }
    }
}

// ======================================= Aux ===========================================================

void Breakout::setupBoxPositions() {
    float paddingX = reader.GetReal("Game", "boxPaddingX", 0.01);
    float paddingY = reader.GetReal("Game", "boxPaddingY", 0.01);
    float offsetY  = reader.GetReal("Game", "offsetY", 0.1);

    glm::vec2 pos = glm::vec2(-1.0 + paddingX + (box.getSize().x / 2) + 0.05, 1.0 - paddingY - offsetY - (box.getSize().y / 2));

    // 4 rows
    for (int i=0; i<4; i++) {
        // 9 columns
        for (int j=0; j<9; j++) {
            boxesPosition[i][j] = pos;
            pos.x += (box.getSize().x + paddingX);
        }
        pos.x = -1.0 + paddingX + (box.getSize().x / 2) + 0.05;
        pos.y -= (box.getSize().y + paddingY);
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
    
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && paddle.getPosition().x - paddle.getSize().x /2 > -1.0) {
        paddle.move(glm::vec2(-0.01f, 0.0f));
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && paddle.getPosition().x + paddle.getSize().x /2 < 1.0) {
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
