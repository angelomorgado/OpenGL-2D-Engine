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
#include <glm/gtc/type_ptr.hpp>
#include <vector>

class Object {
    public:
        void load(Shape shape, Shader shader, std::vector<Texture> textures = {}, glm::vec3 position = glm::vec3(0.0f), float rotation = 0.0f, glm::vec3 scale = glm::vec3(0.0f));
        void render();
        void clean();

        // Getters
        glm::vec3 getPosition();
        float getRotation();
        glm::vec3 getScale();
        glm::mat4 getTransform();

        // Setters
        void setPosition(glm::vec3 position);
        void setRotation(float rotation);
        void setScale(glm::vec3 scale);
        void setTransform(glm::mat4 transform);
    private:
        // Private attributes
        Shape shape;
        std::vector<Texture> textures;
        Shader shader;
        glm::vec3 position;
        float rotation;
        glm::vec3 scale;
        glm::mat4 transform;

        unsigned int VBO, VAO, EBO;

        void updateTransform();
};

#endif