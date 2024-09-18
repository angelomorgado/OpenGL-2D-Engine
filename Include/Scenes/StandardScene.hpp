#ifndef STANDARDSCENE_HPP
#define STANDARDSCENE_HPP

#include <array>
#include <string>
#include <iostream>

#include <Scene.hpp>
#include <Callbacks.hpp>
#include <Setup.hpp>
#include <INIReader.h>
#include <Shader.hpp>

class StandardScene : public Scene {
public:
    StandardScene();
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
    bool cursor_locked;
    
    std::array<float, 18> vertices;
    std::array<int, 3> indices;
    unsigned int VBO, VAO, EBO;
    Shader standardShader;
};

#endif // STANDARDSCENE_HPP