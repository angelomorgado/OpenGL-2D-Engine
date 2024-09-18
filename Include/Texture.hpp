#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <stb_image.h>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream>

class Texture {
public:
    void load(const char* path);
    void bind();
    void unbind();
    void clean();
    unsigned int getID();
private:
    unsigned int ID;
    const char* path;
    int width, height, nrChannels;
    unsigned char* data;
};

#endif