#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <Shader.hpp>

class Framebuffer {
public:
    void loadFramebuffer(unsigned int width, unsigned int height);
    void bind();
    void unbind();
    void applyFilter(Shader &shader);

private:
    // Framebuffer data
    unsigned int fbo;
    unsigned int rbo;
    unsigned int textureColorBuffer;
};

#endif