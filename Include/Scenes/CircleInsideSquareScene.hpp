#ifndef CIRCLEINSIDESQUARESCENE_HPP
#define CIRCLEINSIDESQUARESCENE_HPP

#include <array>
#include <string>
#include <iostream>

#include <Scene.hpp>
#include <Callbacks.hpp>
#include <Setup.hpp>
#include <INIReader.h>
#include <Shader.hpp>
#include <Texture.hpp>
#include <Shapes.hpp>
#include <Object.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class CircleInsideSquareScene : public Scene {
public:
    CircleInsideSquareScene();
    void load() override;
    void update() override;
    void render() override;
    int clean() override;
    GLFWwindow* getWindow() override;
private:
    // Window attributes
    GLFWwindow* window;
    int screen_width;
    int screen_height;
    std::string title;
    bool fullscreen;
    bool resizable;
    
    // Object Attributes
    Shape shape1, shape2;
    Shader standardShader, textureShader;
    Texture texture1;
    Texture texture2;
    float offset;
    Object square, circle;
    float speed;
    glm::vec2 direction;

    void processInput();
    bool checkAABBCollision(Object& obj1, Object& obj2);
    bool checkCircleCollision(Object& circle, Object& square);
    void borderCollision(Object& obj);
    void isInside(Object& obj1, Object& obj2);
};

#endif