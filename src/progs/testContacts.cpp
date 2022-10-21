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
#include "../utils/Engine.hpp"
#include "../utils/contacts/ParticleRod.hpp"
#include "../utils/contacts/ParticleCable.hpp"


using namespace std;

int main(int argc, char **argv)
{

    
    Engine engine = Engine();


    // Creation des elements d'OpenGl
    Window window;
    window.setWireFrame(false);
    window.setBackFaceCulling(false);

    Shader shader1;
    glPointSize(25); // C'est juste pour mieux voir le point
    Point mesh1;

    Transform trans1;
    Transform trans2;
    Transform trans3;

    // Creation de particules pour collisions
    vec3 pos1 = vec3(0, 0, 0);
    vec3 pos2 = vec3(0.5, 0, 0);
    vec3 pos3 = vec3(0, 0.5, 0);

    vec3 vitesse = vec3(0, 0, 0);
    vec3 vitessex = vec3(0.1,0,0);
    vec3 accel = vec3(0, 0, 0);

    particle particule1 = particle(pos1, vitesse, accel, 0.1, 0.99);
    engine.addParticle(particule1);
    trans1.setPos(particule1.getPosition().getX(),particule1.getPosition().getY(),particule1.getPosition().getZ());


    particle particule2 = particle(pos2, vitessex, accel, 0.2, 0.99);
    engine.addParticle(particule2);
    trans2.setPos(particule2.getPosition().getX(),particule2.getPosition().getY(),particule2.getPosition().getZ());

    particle particule3 = particle(pos3, vitesse, accel, 0.1, 0.99);
    engine.addParticle(particule3);
    trans3.setPos(particule3.getPosition().getX(),particule3.getPosition().getY(),particule3.getPosition().getZ());
    

    ParticleCable cable1 = ParticleCable(0.6,0,particule1, particule2);
    ParticleCable cable2 = ParticleCable(0.6,0,particule1, particule3);
    ParticleCable cable3 = ParticleCable(10,0,particule3, particule2);

    engine.addContact(cable1);
    engine.addContact(cable2);
    engine.addContact(cable3);


    // Delta Time fixe

    double chrono = 0.0;
    double dt = 1.0 / 60.0;

    while (window.isOpen())
    {
        // Traitement des evenements
        window.pollEvents();

        if (window.isKeyDown(ESCAPE))
            window.closeWindow();

        float oldX = particule1.getPosition().getX();
        float oldY = particule1.getPosition().getY();
        float oldZ = particule1.getPosition().getZ();

        float oldX2 = particule2.getPosition().getX();
        float oldY2 = particule2.getPosition().getY();
        float oldZ2 = particule2.getPosition().getZ();


        float oldX3 = particule3.getPosition().getX();
        float oldY3 = particule3.getPosition().getY();
        float oldZ3 = particule3.getPosition().getZ();

        engine.Update(dt);
        
        trans1.moveX(particule1.getPosition().getX() - oldX);
        trans1.moveY(particule1.getPosition().getY() - oldY);
        trans1.moveZ(particule1.getPosition().getZ() - oldZ);
        trans2.moveX(particule2.getPosition().getX() - oldX2);
        trans2.moveY(particule2.getPosition().getY() - oldY2);
        trans2.moveZ(particule2.getPosition().getZ() - oldZ2);

        trans3.moveX(particule3.getPosition().getX() - oldX3);
        trans3.moveY(particule3.getPosition().getY() - oldY3);
        trans3.moveZ(particule3.getPosition().getZ() - oldZ3);

        // Affichage    
        window.clear();
        shader1.setUniform("color", vec4(1, 0, 0, 1));
        window.draw(mesh1, shader1, trans1);
        shader1.setUniform("color", vec4(0, 1, 0, 1));
        window.draw(mesh1, shader1, trans2);
        shader1.setUniform("color", vec4(0, 0, 1, 1));
        window.draw(mesh1, shader1, trans3);
        window.display();
    }

    /*

        // Delta Time variant

        clock_t start;
        double duration = 0;
        double chrono = 0;
        bool falling = true;

        particule1.show();


        while(falling){
            start = clock();

            Integr.update(particule1,duration);
            particule1.show();  // Equivalent de demander l'affichage
            cout<<endl;


            duration = (clock() - start) / (double) CLOCKS_PER_SEC;
            chrono += duration;
       }

    */

    return 0;
}