#include <iostream>
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
#include "../utils/integrator.hpp"

int main(int argc, char **argv)
{

    if (argc != 2)
    {
        cout << "Pour utiliser le programme, il suffit de rentrer en parametre une hauteur (en metres)." << endl;
        return 0;
    }

    // Creation des elements d'OpenGl
    Window window;
    window.setWireFrame(false);
    window.setBackFaceCulling(false);

    Shader shader1;
    glPointSize(25); // C'est juste pour mieux voir le point
    Point mesh1;

    Transform trans1;


    float hauteur = (float)strtod(argv[1], NULL);


    vector3D Pomme = vector3D(0, hauteur, 0);
    vector3D VitesseChute = vector3D(0, 0, 0);
    vector3D Gravite = vector3D(0, -5, 0);
    vector3D Newton = vector3D(0, 1.63, 0);

    particle Projectile = particle(Pomme, VitesseChute, Gravite, 10, 0.999);
    Projectile.show();

    integrator Integr = integrator();

    // Delta Time fixe

    double chrono = 0.0;
    double dt = 1.0 / 60.0;
    bool falling = true;

    while (window.isOpen() && falling)
    {
        // Traitement des evenements
        window.pollEvents();

        if (window.isKeyDown(ESCAPE))
            window.closeWindow();

        float oldY = Projectile.getPosition().getY();
        float oldX = Projectile.getPosition().getX();

        Integr.update(Projectile, dt);
        if (Projectile.getPosition().getY() <= Newton.getY())
            falling = false;
        Projectile.show();
        chrono += dt;

        trans1.moveY(Projectile.getPosition().getY() - oldY);
        trans1.moveX(Projectile.getPosition().getX() - oldX);

        // Affichage
        window.clear();
        shader1.setUniform("color", vec4(1, 0.5, 0, 1));
        window.draw(mesh1, shader1, trans1);
        window.display();
    }

    /*

        // Delta Time variant

        clock_t start;
        double duration = 0;
        double chrono = 0;
        bool falling = true;

        Projectile.show();


        while(falling){
            start = clock();

            Integr.update(Projectile,duration);
            Projectile.show();  // Equivalent de demander l'affichage
            cout<<endl;


            duration = (clock() - start) / (double) CLOCKS_PER_SEC;
            chrono += duration;
       }

    */

    cout << "La pomme a mis " << chrono << " secondes pour tomber sur Newton a partir d'une hauteur de " << hauteur << " metres." << endl;
    Projectile.show();

    return 0;
}