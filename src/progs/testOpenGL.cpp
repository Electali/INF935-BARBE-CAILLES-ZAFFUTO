#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <iostream>

#include "../utils/OpenGl/window.hpp"
#include "../utils/OpenGl/shader.hpp"
#include "../utils/OpenGl/transform.hpp"
#include "../utils/OpenGl/point.hpp"


using namespace std;

int main()
{
    Window window;
    window.setWireFrame(false);
    window.setBackFaceCulling(false);

    Shader shader1;
    glPointSize(25); // C'est juste pour mieux voir le point
    Point mesh1;
    //Triangle mesh2;
    //Cube mesh3;
    Transform trans1;
    auto trans2 = Transform()
        .setPos(0.5, 0, 0)
        .setScale(1.5, 1.5, 1.5);

    auto trans3 = Transform()
        .setPos(-0.75, 0.25, 0)
        .setScale(0.2, 0.2, 0.2);

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
        shader1.setUniform("color", vec4(0, 0.5, 1, 1));
        window.draw(mesh2, shader1, trans2);
        shader1.setUniform("color", vec4(1, 0, 0.5, 1));
        window.draw(mesh3, shader1, trans3);
        window.display();
    }

    return 0;
}