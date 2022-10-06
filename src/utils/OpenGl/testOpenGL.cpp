#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <iostream>

#include "window.hpp"
#include "shader.hpp"
#include "transform.hpp"
#include "point.hpp"

using namespace std;

int main()
{
    Window window;
    window.setWireFrame(false);
    window.setBackFaceCulling(false);

    Shader shader1;
    glPointSize(25); // C'est juste pour mieux voir le point
    Point mesh1;
    Transform trans1;

    while (window.isOpen())
    {
        // Traitement des evenements
        window.pollEvents();

        if (window.isKeyDown(ESCAPE))
            window.closeWindow();

        if (window.isKeyDown(ARROW_DOWN))
            trans1.moveY(-0.1);
        else if (window.isKeyDown(ARROW_UP))
            trans1.moveY(0.1);

        if (window.isKeyDown(ARROW_LEFT))
            trans1.moveX(-0.1);
        else if (window.isKeyDown(ARROW_RIGHT))
            trans1.moveX(0.1);

        // Affichage
        window.clear();
        shader1.setUniform("color", vec4(1, 0.5, 0, 1));
        window.draw(mesh1, shader1, trans1);
        window.display();
    }

    return 0;
}