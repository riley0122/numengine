#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "embedded_shaders.hpp"
#include "shaders.hpp"

#include "spritedata.hpp"

#include "rect.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 320;
const unsigned int SCR_HEIGHT = 240;

void init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

void translateColours(EADK::Color colour, float& r, float& g, float& b) {
    uint16_t value = (uint16_t)colour;
    
    uint16_t red = (value >> 11) & 0x1F;
    uint16_t green = (value >> 5) & 0x3F;
    uint16_t blue = value & 0x1F;

    r = red / 31.0f;
    g = green / 63.0f;
    b = blue / 31.0f;
}

int main(int argc, char *argv[]) {
    init();

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "sprite preview", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create glfw window" << std::endl;
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialise GLAD!" << std::endl;
    }

    unsigned int shaderProgram = createShaderProgram(vertex_shader_shader, fragment_shader_shader);

    std::vector<numengine::sprite_image_data_block> image_data = final_sprite.get_image_data();
    std::vector<rect> rects = std::vector<rect>();
    for (sprite_image_data_block s : image_data) {
        float r, g, b;
        translateColours(s.colour, r, g, b);

        float width = static_cast<float>(s.width) / SCR_WIDTH;
        float height = static_cast<float>(s.height) / SCR_HEIGHT;

        float relativeX = (s.relative_x > 0) ? (2.0f * s.relative_x / SCR_WIDTH - 1.0f) : 0.0f;
        float relativeY = (s.relative_y > 0) ? (1.0f - 2.0f * s.relative_y / SCR_HEIGHT) : 0.0f;

        rect R = rect(width, height, relativeX, relativeY, glm::vec4(r, g, b, 1.0f));
        R.generate_buffers();
        rects.push_back(R);
    }

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (auto& R : rects) {
            R.draw(shaderProgram);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();

        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cerr << "OpenGL error: " << error << std::endl;
        }
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
