#include <Shapes.hpp>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

void Shape::createSquare() {
    vertices = {
        // Positions          // Colors        // Texture Coords
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f, // Top Left
        0.5f,  0.5f, 0.0f,    1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // Top Right
        0.5f, -0.5f, 0.0f,    1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // Bottom Right
        -0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f  // Bottom Left
    };

    indices = {
        0, 1, 3, // First Triangle
        1, 2, 3  // Second Triangle
    };

    numberOfVertices = 6;  
    size = glm::vec2(1.0f);
}


void Shape::createTriangle() {
    vertices = {
        // Positions          // Colors        // Texture Coords
        0.0f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.5f, 1.0f, // Top
        0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // Bottom Right
        -0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 1.0f,   0.0f, 0.0f  // Bottom Left
    };

    indices = {
        0, 1, 2
    };

    numberOfVertices = 3; 
    size = glm::vec2(1.0f);
}

void Shape::createCircle(int segments) {
    vertices = { 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.5f, 0.5f }; // Center vertex

    for (unsigned int i = 0; i <= segments; ++i) {
        float angle = 2.0f * M_PI * i / segments;
        float x = 0.5f * cos(angle);
        float y = 0.5f * sin(angle);

        vertices.insert(vertices.end(), {
            x, y, 0.0f,   1.0f, 1.0f, 1.0f,   (x + 0.5f), (y + 0.5f)
        });

        if (i > 0) {
            indices.insert(indices.end(), { 0, i, i + 1 });
        }
    }

    numberOfVertices = segments * 3 + 1;
    size   = glm::vec2(1.0f);
    radius = 0.5f;
}
