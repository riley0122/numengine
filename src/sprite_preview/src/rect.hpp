#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>

const unsigned int rect_indices[] = {
    0, 1, 2,
    2, 3, 0
};

struct shape_data {
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
};

class rect {
private:
    float center_x;
    float center_y;

    float vertecies[8];
    shape_data data;

    glm::vec4 colour;
public:
    rect(float width, float height, float center_x, float center_y, glm::vec4 colour);
    float* getvertecies();
    void generate_buffers();
    void draw(GLuint shaderProgram);
};
