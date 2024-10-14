#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

class Texture {
public:
    void load(const char* path);
    void bind(int textureUnit = 0);
    void unbind();
    void clean();
    unsigned int getID();
    const char* getUniformName();
    bool isTransparent();
    void setWrappingParameters(GLenum wrapS, GLenum wrapT);
private:
    unsigned int ID, textureUnit;
    const char* path;
    const char* uniformName;
    int width, height, nrChannels;
    unsigned char* data;
    bool transparent;
};

#endif