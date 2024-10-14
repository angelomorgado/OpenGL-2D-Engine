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
    bool boxesField[4][9];
    glm::vec2 boxesPosition[4][9];
    
    // Object Attributes
    Shape squareShape, circleShape;
    Shader textureShader, textShader;
    Texture ballTexture, boxTexture, paddleTexture;
    Font font1;
    Object box, ball, paddle;
    float ballSpeed, paddleSpeed;
    glm::vec2 ballDirection;
    ma_engine audioEngine;
    bool flag;

    void processInput();
    void setupBoxPositions();
    void borderCollision(Object& obj);
    void drawBoxField();
    void checkPaddleBallCollision();
    void checkBoxBallCollision();
};

#endif