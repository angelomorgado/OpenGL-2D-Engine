#ifndef COLLISIONSSCENE_HPP
#define COLLISIONSSCENE_HPP

#include <Scene.hpp>
#include <Texture.hpp>
#include <Shapes.hpp>
#include <Object.hpp>
#include <Framebuffer.hpp>
#include <glm/glm.hpp>
#include <string>
#include <TextRendering.hpp>
#include "miniaudio.h"

class CollisionsScene : public Scene {

public:
    CollisionsScene();
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
    Shape shape1, shape2, screenShape;
    Shader standardShader, textureShader, textShader, screenShader;
    Texture texture1;
    Texture texture2;
    Framebuffer screenEffect;
    Font font1;
    float offset;
    Object square, circle, screenObj;
    float speed;
    glm::vec2 direction;
    ma_engine audioEngine;
    bool flag;

    void processInput();
    void borderCollision(Object& obj);
};

#endif