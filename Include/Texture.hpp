#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <stb_image.h>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream>
#include <string>

class Texture {
public:
    void load(const char* path, std::string uniformName = "texture1");
    void bind(int textureUnit = 0);
    void unbind();
    void clean();
    unsigned int getID();
    const char* getUniformName();
private:
    unsigned int ID, textureUnit;
    const char* path;
    const char* uniformName;
    int width, height, nrChannels;
    unsigned char* data;
};

#endif