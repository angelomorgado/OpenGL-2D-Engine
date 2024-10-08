#include <Object.hpp>

void Object::load(Shape shape, Shader shader, std::vector<Texture> textures, glm::vec2 position, float rotation, glm::vec2 scale) {
    this->shape = shape;
    this->textures = textures;
    this->shader = shader;
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
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // Copy our vertices array into the buffer for OpenGL to use
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape.indices.size() * sizeof(unsigned int), shape.indices.data(), GL_STATIC_DRAW); 
    // Set the vertex attributes pointers
    //      Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); // offset, stride, pointer, divisor, integer, normalized
    glEnableVertexAttribArray(0);  
    //      Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);  
    //      Texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6* sizeof(float)));
    glEnableVertexAttribArray(2);  
    // Unbind VAO and VBO for safety
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    updateTransform();

    // Set the texture units
    shader.use();
    for (unsigned int i = 0; i < textures.size(); i++) {
        shader.setInt(textures[i].getUniformName(), i);
    }
}

void Object::render() {
    shader.use();
    shader.setMat4("transform", transform);
    for (unsigned int i = 0; i < textures.size(); i++) {
        textures[i].bind(i);
    }
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, shape.numberOfVertices, GL_UNSIGNED_INT, 0);
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