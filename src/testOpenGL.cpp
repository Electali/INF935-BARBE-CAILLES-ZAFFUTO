#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <iostream>

#include "window.hpp"
#include "shader.hpp"
#include "triangle.hpp"
#include "vector3.hpp"

using namespace std;

int main(int argc, char **argv)
{
    Window ctx;

    Shader shader;

    Triangle triangle;

    Vector3 particleCoords(0, 0, 0);

    triangle.model.setPosition(Vector3(1, 1, 0));
    glUseProgram(shader.program);
    shader.setUniform("model", triangle.model);

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            cout << triangle.model.data[i].data[j];
        }
        cout << endl;
    }

    while (!glfwWindowShouldClose(ctx.window))
    {
        particleCoords.x += 0.0000001;
        particleCoords.y -= 0.000001;
        
        glfwSwapBuffers(ctx.window);
        glfwPollEvents();

        if (glfwGetKey(ctx.window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(ctx.window, true);
        }
    
        if (glfwGetKey(ctx.window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            triangle.model.translate(Vector3(0, 0.1, 0));
            glUseProgram(shader.program);
            shader.setUniform("model", triangle.model);
        }

        if (glfwGetKey(ctx.window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            triangle.model.translate(Vector3(0, -0.1, 0));
            glUseProgram(shader.program);
            shader.setUniform("model", triangle.model);
        }

        triangle.draw(shader, particleCoords);
    }

    return 0;
}