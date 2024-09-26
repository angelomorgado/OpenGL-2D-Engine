#ifndef STANDARDTEXURESCENE_HPP
#define STANDARDTEXURESCENE_HPP

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

class StandardTextureScene : public Scene {
public:
    StandardTextureScene();
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
    Shape squareShape;
    Shader standardShader;
    Texture texture1;
    Texture texture2;
    float offset;
    Object square;

    void processInput();
};

#endif