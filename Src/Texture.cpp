#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <Texture.hpp>

#include <iostream>
#include <glad/glad.h>

void Texture::load(const char* path) {
    this->path = path;

    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    // Set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set the texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Load image, create texture and generate mipmaps
    // stbi_set_flip_vertically_on_load(true);
    data = stbi_load(path, &width, &height, &nrChannels, 0);
    GLenum format;
    if (nrChannels == 1) {
        format = GL_RED;
        transparent = false;
    }
    else if (nrChannels == 3) {
        format = GL_RGB;
        transparent = false;
    }
    else if (nrChannels == 4) {
        format = GL_RGBA;
        transparent = true;
    }
    else
        format = GL_RGB; // Default to GL_RGB if the number of channels is unexpected
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_set_flip_vertically_on_load(true);
    stbi_image_free(data);
}

void Texture::bind(int textureUnit) {
    glActiveTexture(GL_TEXTURE0 + textureUnit); 
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::clean() {
    glDeleteTextures(1, &ID);
}

unsigned int Texture::getID() {
    return ID;
}

bool Texture::isTransparent() {
    return transparent;
}