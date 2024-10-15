#ifndef BREAKOUT_HPP
#define BREAKOUT_HPP

#include <Scene.hpp>
#include <Texture.hpp>
#include <Shapes.hpp>
#include <Object.hpp>
#include <glm/glm.hpp>
#include <string>
#include <TextRendering.hpp>
#include "miniaudio.h"

class Breakout : public Scene {

public:
    Breakout();
    void load() override;
    void update() override;
    void render() override;
    int clean() override;
    GLFWwindow* getWindow() override;
private:
    // Window attributes
    GLFWwindow* window;
    int screenWidth;
    int screenHeight;
    std::string title;
    bool fullscreen;
    bool resizable;
    
    // Object Attributes
    Shape squareShape, circleShape, screenShape;
    Shader boxShader, textureShader, textShader, screenShader;
    Texture ballTexture, boxTexture, paddleTexture, screenTexture;
    Font font1;
    Object box, ball, paddle, screen;
    float ballSpeed, ballSpeedIncrease, paddleSpeed;
    glm::vec2 ballDirection;
    ma_engine audioEngine;
    bool levelStartedFlag, levelFailed;
    unsigned int level = 1;
    unsigned int numOfBlocks;
    unsigned int boxesField[4][9];
    glm::vec2 boxesPosition[4][9];
    std::string levelTheme;

    void processInput();
    void setupBoxPositions();
    void borderCollision(Object& obj);
    void drawBoxField();
    void checkPaddleBallCollision();
    void checkBoxBallCollision();
    void loadLevel();
    int isLevelFinished();
    void renderText();
    void loadBlocksFromJSON(const std::string& levelName);
    void loadRandomBlocksFromJSON();
    void cleanObjects();
};

#endif