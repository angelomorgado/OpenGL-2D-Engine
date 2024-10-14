#include <Object.hpp>
#include <iostream>

void Object::load(Shape shape, glm::vec2 position, float rotation, glm::vec2 scale) {
    this->shape = shape;
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;

    // Load object to the GPU
    // Generate and bind Vertex Array Object (VAO)
    glGenVertexArrays(1, &VAO);  // Generate VAO
    glBindVertexArray(VAO);      // Bind VAO
    // Generate and bind Vertex Buffer Object (VBO)
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Copy our vertices array into the buffer for OpenGL to use
    glBufferData(GL_ARRAY_BUFFER, shape.vertices.size() * sizeof(float), shape.vertices.data(), GL_STATIC_DRAW);
    // Generate and bind Element Buffer Object (EBO)
    if (shape.indices.size() > 0) {
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    }
    // Copy our vertices array into the buffer for OpenGL to use
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape.indices.size() * sizeof(unsigned int), shape.indices.data(), GL_STATIC_DRAW); 
    // Set the vertex attributes pointers 
    setVertexAttributes();
    // Unbind VAO and VBO for safety
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    updateTransform();
}

void Object::render(Shader shader, Texture texture) {
    if(shader.getID()) {
        shader.use();
        shader.setMat4("transform", transform);
        if (texture.getID()) {
            texture.bind(0);
            shader.setInt("texture1", 0);
        }
    }

    glBindVertexArray(VAO);

    if (shape.indices.size() == 0) {
        glDrawArrays(shape.drawFormat, 0, shape.numberOfVertices);
    }
    else {
        glDrawElements(shape.drawFormat, shape.numberOfVertices, GL_UNSIGNED_INT, 0);
    }

    glBindVertexArray(0);
}

void Object::clean() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Object::updateTransform() {
    transform = glm::mat4(1.0f);
    // Translate (convert vec2 to vec3 by adding z = 0)
    transform = glm::translate(transform, glm::vec3(position, 0.0f));
    // Rotate around z-axis (2D rotation)
    transform = glm::rotate(transform, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    // Scale (convert vec2 to vec3 by adding z = 1)
    transform = glm::scale(transform, glm::vec3(scale, 1.0f));
}

// Getters and Setters
glm::vec2 Object::getPosition() {
    return position;
}

float Object::getRotation() {
    return rotation;
}

glm::vec2 Object::getScale() {
    return scale;
}

glm::vec2 Object::getSize() {
    return scale * shape.size;
}

glm::mat4 Object::getTransform() {
    return transform;
}

Shape Object::getShape() {
    return shape;
}

void Object::setPosition(glm::vec2 position) {
    this->position = position;
    updateTransform();
}

void Object::move(glm::vec2 position) {
    this->position += position;
    updateTransform();
}

void Object::setRotation(float rotation) {
    this->rotation = rotation;
    updateTransform();
}

void Object::setScale(glm::vec2 scale) {
    this->scale = scale;
    updateTransform();
}

void Object::setTransform(glm::mat4 transform) {
    this->transform = transform;
}

void Object::setColor(glm::vec3 color) {
    for (unsigned int i = 0; i < shape.vertices.size(); i += 8) {
        shape.vertices[i + 3] = color.r;
        shape.vertices[i + 4] = color.g;
        shape.vertices[i + 5] = color.b;
    }
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, shape.vertices.size() * sizeof(float), shape.vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// --------

void Object::setVertexAttributes() {
    for (const auto& attr : shape.vertexAttributes) {
        glVertexAttribPointer(attr.index, attr.size, attr.type, attr.normalized, attr.stride, attr.pointer);
        glEnableVertexAttribArray(attr.index);  // Enable the attribute
    }
}