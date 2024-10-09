#ifndef COLLISIONSSCENE_HPP
#define COLLISIONSSCENE_HPP

#include <Scene.hpp>
#include <Texture.hpp>
#include <Shapes.hpp>
#include <Object.hpp>
#include <glm/glm.hpp>
#include <string>
#include <TextRendering.hpp>

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
    int screen_width;
    int screen_height;
    std::string title;
    bool fullscreen;
    bool resizable;
    
    // Object Attributes
    Shape shape1, shape2;
    Shader standardShader, textureShader, textShader;
    Texture texture1;
    Texture texture2;
    Font font1;
    float offset;
    Object square, circle;
    float speed;
    glm::vec2 direction;

    void processInput();
    void borderCollision(Object& obj);
};

#endif