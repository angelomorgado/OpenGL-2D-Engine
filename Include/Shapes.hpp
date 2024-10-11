/*
    Shapes.hpp:

        - It contains the vectors for the standard objects in the engine, such as squares, circles, and triangles
*/
#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>

class Shape {
public:
    struct VertexAttribute {
        GLuint index;           // The index of the attribute (e.g., 0 for position, 1 for color)
        GLint size;             // Number of components (e.g., 3 for vec3)
        GLenum type;            // Data type (e.g., GL_FLOAT)
        GLboolean normalized;   // Whether to normalize the data
        GLsizei stride;         // The stride (distance between consecutive vertex attributes)
        const void* pointer;    // The offset in the buffer
    };

    void createSquare();
    void createScreen();
    void createTriangle();
    void createCircle(int segments = 36);
    
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    std::vector<VertexAttribute> vertexAttributes;
    int numberOfVertices;
    float radius;
    glm::vec2 size;

};

#endif
