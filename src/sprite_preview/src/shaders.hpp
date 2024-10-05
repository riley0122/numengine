#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

unsigned int compileShader(unsigned int type, const char* source);
unsigned int createShaderProgram(const char* vertexSource, const char* fragmentSource);
