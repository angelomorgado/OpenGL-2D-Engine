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

class StandardTextureScene : public Scene {
public:
    StandardTextureScene();
    void load() override;
    void update() override;
    void render() override;
    int clean() override;
    GLFWwindow* getWindow() override;
private:
    GLFWwindow* window;
    int screen_width;
    int screen_height;
    std::string title;
    bool fullscreen;
    bool resizable;
    
    std::array<float, 32> vertices;
    std::array<int, 6> indices;
    std::array<float, 6> texCoords;
    unsigned int VBO, VAO, EBO;
    Shader standardShader;
    Texture texture1;
    float offset;

    void processInput();
};

#endif