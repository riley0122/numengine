#include "rect.hpp"

rect::rect(float width, float height, float center_x, float center_y, glm::vec4 colour) {
    this->center_x = center_x;
    this->center_y = center_y;

    this->colour = colour;

    float halfHeight = height / 2;
    float halfWidth = width / 2;

    // 4 x,y pairs
    float vertecies[8] = {
        // Top left
        0.0f, 0.0f,
        // Top right
        width, 0.0f,
        // Bottom right
        width, -height,
        // Bottom left
        0.0f, -height
    };

    for (unsigned int i = 0; i < 8; i++)
        this->vertecies[i] = vertecies[i];    
}

float* rect::getvertecies() {
    static float vertecies[8];

    for (int i = 0; i < 8; i += 2)
    {
        vertecies[i] = this->vertecies[i] + this->center_x;
        vertecies[i + 1] = this->vertecies[i + 1] + this->center_y;
    }

    return vertecies;
}

void rect::generate_buffers() {
    shape_data data;

    float* vertecies = this->getvertecies();

    glGenVertexArrays(1, &data.VAO);
    glGenBuffers(1, &data.VBO);
    glGenBuffers(1, &data.EBO);

    glBindVertexArray(data.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, data.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, this->getvertecies(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rect_indices), rect_indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    this->data = data;
};

void rect::draw(GLuint shaderProgram) {
    glUseProgram(shaderProgram);

    GLint colourLocation = glGetUniformLocation(shaderProgram, "colour");

    float colourArray[4] ={
        this->colour.r,
        this->colour.g,
        this->colour.b,
        this->colour.a,
    };

    glUniform4fv(colourLocation, 1, colourArray);

    glBindVertexArray(data.VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
};