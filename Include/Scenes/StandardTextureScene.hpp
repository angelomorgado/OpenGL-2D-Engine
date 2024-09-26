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
    unsigned int VBO, VAO, EBO;
    Shape square;
    Shader standardShader;
    Texture texture1;
    Texture texture2;
    float offset;

    void processInput();
};

#endif