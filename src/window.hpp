#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <iostream>

using namespace std;

class Window
{
public:
    GLFWwindow *window;

    Window()
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(800, 600, "Bonjour", nullptr, nullptr);

        if (window == nullptr)
        {
            cout << "Erreur initialisation fenêtre" << endl;
            glfwTerminate();
            exit(1);
        }

        glfwMakeContextCurrent(window);
        glewInit();
    }

    ~Window()
    {
        glfwTerminate();
    }
};