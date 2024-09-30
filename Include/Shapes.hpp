/*
    Shapes.hpp:

        - It contains the vectors for the standard objects in the engine, such as squares, circles, and triangles
*/
#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <cmath>

class Shape {
public:
    void createSquare();
    void createTriangle();
    void createCircle(int segments = 36);
    
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    int numberOfVertices;
    float radius;
    glm::vec2 size;
};

#endif
