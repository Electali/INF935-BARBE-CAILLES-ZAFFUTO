#ifndef POINT_HPP
#define POINT_HPP

#include "shader.hpp"
#include "transform.hpp"
#include "abstractMesh.hpp"

class Point: public AbstractMesh
{
public:
    Point()
    {
        glGenBuffers(1, &VBO);

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
    }

public:
    void draw(const Shader &shader, Transform& transform) override
    {
        shader.setUniform("model", transform.getModel());
        glBindVertexArray(VAO);
        glDrawArrays(GL_POINTS, 0, 1);
    }

private:
    static inline float point[] = {
        0.0f, 0.0f, 0.0f
    };

    unsigned int VBO;
    unsigned int VAO;
};

#endif // POINT_HPP