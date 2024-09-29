#include <Object.hpp>

void Object::load(Shape shape, Shader shader, std::vector<Texture> textures, glm::vec3 position, float rotation, glm::vec3 scale) {
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
    transform = glm::translate(transform, position);
    transform = glm::rotate(transform, glm::radians(rotation), glm::vec3(0.0, 0.0, 1.0));
    transform = glm::scale(transform, scale);
}

// Getters and Setters
glm::vec3 Object::getPosition() {
    return position;
}

float Object::getRotation() {
    return rotation;
}

glm::vec3 Object::getScale() {
    return scale;
}

glm::mat4 Object::getTransform() {
    return transform;
}

void Object::setPosition(glm::vec3 position) {
    this->position = position;
    updateTransform();
}

void Object::setRotation(float rotation) {
    this->rotation = rotation;
    updateTransform();
}

void Object::setScale(glm::vec3 scale) {
    this->scale = scale;
    updateTransform();
}

void Object::setTransform(glm::mat4 transform) {
    this->transform = transform;
}