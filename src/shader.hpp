#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <iostream>

#include "matrix44.hpp"

using namespace std;

class Shader
{
public:
    unsigned int program;

    Shader()
    {
        const char *vertexShaderSource = "#version 330 core\n"
                                         "layout (location = 0) in vec3 aPos;\n"
                                         "uniform mat4 model;\n"
                                         "void main()\n"
                                         "{\n"
                                         "   gl_Position = model*vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                         "}\0";

        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
        glCompileShader(vertexShader);

        const char *fragmentShaderSource = "#version 330 core\n"
                                           "out vec4 FragColor;\n"
                                           "void main()\n"
                                           "{\n"
                                           "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                           "}\0";

        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
        glCompileShader(fragmentShader);

        program = glCreateProgram();
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);

        glUseProgram(program);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    void setUniform(const string& name, const Matrix44& mat) {
            glUseProgram(program);
            glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, mat);
        }
};