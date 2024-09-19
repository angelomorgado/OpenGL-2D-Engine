#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <stb_image.h>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream>
#include <string>

#include <Shader.hpp>

class Texture {
public:
    void load(const char* path, Shader* shader = nullptr, std::string uniformName = "texture1");
    void bind();
    void unbind();
    void clean();
    unsigned int getID();
private:
    unsigned int ID, textureUnit;
    const char* path;
    int width, height, nrChannels;
    unsigned char* data;

    static unsigned int textureCount;  // Static variable to track texture count
};

#endif