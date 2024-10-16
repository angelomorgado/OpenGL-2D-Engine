/*
    Object.hpp:

        - Makes it easier initializing shaders and communication between the shader files and the main program
*/
#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <Shapes.hpp>
#include <Texture.hpp>
#include <Shader.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class Object {
    public:
        void load(Shape shape, glm::vec2 position = glm::vec2(0.0f), float rotation = 0.0f, glm::vec2 scale = glm::vec2(1.0f));
        void render(Shader shader = Shader(), Texture texture = Texture());
        void clean();
        void move(glm::vec2 position);

        // Getters
        glm::vec2 getPosition();
        float getRotation();
        glm::vec2 getScale();
        glm::mat4 getTransform();
        Shape getShape();
        glm::vec2 getSize();

        // Setters
        void setPosition(glm::vec2 position);
        void setRotation(float rotation);
        void setScale(glm::vec2 scale);
        void setTransform(glm::mat4 transform);
        void setColor(glm::vec3 color);
    private:
        // Private attributes
        Shape shape;
        glm::vec2 position;
        float rotation;
        glm::vec2 scale;
        glm::mat4 transform;

        unsigned int VBO, VAO, EBO;

        void updateTransform();
        void setVertexAttributes();
};

#endif