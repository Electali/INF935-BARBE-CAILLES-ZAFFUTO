#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <iostream>

#include "shader.hpp"
#include "Matrix44.hpp"

class Triangle
{
public:
    static inline float point[] = {
        -0.05f, -0.05f, 0.0f,
        0.05f, -0.05f, 0.0f,
        0.0f, 0.05f, 0.0f};

    unsigned int VBO;

    unsigned int VAO;

    Matrix44 model;

    Triangle()
    {
    }

    void draw(Shader &shader, Vector3 &particleCoords)
    {
        // Initialisation des données de jeu

        point[0] += particleCoords.x;
        point[1] += particleCoords.x;
        point[2] += particleCoords.x;
        point[3] += particleCoords.y;
        point[4] += particleCoords.y;
        point[5] += particleCoords.y;
        point[6] += particleCoords.z;
        point[7] += particleCoords.z;
        point[8] += particleCoords.z;

        glGenBuffers(1, &VBO);

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        glUseProgram(shader.program);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    void updatePos(float x, float y, float z)
    {
    }
};