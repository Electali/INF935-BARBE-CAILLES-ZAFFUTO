#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <iostream>
#include <vector>

#include "../utils/OpenGl/window.hpp"
#include "../utils/Engine.hpp"
#include "../utils/contacts/ParticleRod.hpp"
#include "../utils/contacts/ParticleCable.hpp"
#include "../utils/particle3D.hpp"
#include "../utils/forces/ParticleGravity.hpp"
#include "../utils/forces/ParticleAnchoredSpring.hpp"
#include "../utils/forces/ParticleDrag.hpp"

using namespace std;

using Particles3D = vector<particle3D *>;

int main(int argc, char **argv)
{
    // Vecteur des particules dans notre Moteur
    Particles3D particles;

    Engine engine;

    // Creation des elements d'OpenGl
    Window window;
    window.setWireFrame(false);
    window.setBackFaceCulling(false);

    glPointSize(25); // C'est juste pour mieux voir le point*

    // Creation de particules
    vec3 pos1 = {0, 0};
    vec3 pos2 = {0, -0.2};
    vec3 pos3 = {0, -0.3};
    vec3 pos4 = {0, -0.4};
    vec3 pos5 = {0, -0.5};
    vec3 pos6 = {0.5, 0};
    vec3 pos7 = {-0.92};

    vec3 vitesse; // De base à 0,0,0
    vec3 accel;

    particle3D particule1(pos1, vitesse, accel, 0.001, 0.99);
    engine.addParticle(particule1);

    particle3D particule2(pos2, vitesse, accel, 5, 0.99);
    engine.addParticle(particule2);

    particle3D particule3(pos3, vitesse, accel, 5, 0.99);
    engine.addParticle(particule3);

    particle3D particule4(pos4, vitesse, accel, 5, 0.99);
    engine.addParticle(particule4);

    particle3D particule5(pos5, vitesse, accel, 5, 0.99);
    engine.addParticle(particule5);

    particle3D particule6(pos6, vitesse, accel, 5, 0.99);
    engine.addParticle(particule6);


    particles.push_back(&particule1);
    particles.push_back(&particule2);
    particles.push_back(&particule3);
    particles.push_back(&particule4);
    particles.push_back(&particule5);
    particles.push_back(&particule6);



    // Creation des forces
    vec3 grav = vec3(0, -10, 0);
    ParticleGravity gravity = ParticleGravity(grav);
    engine.registry.add(particule2, gravity);
    engine.registry.add(particule3, gravity);
    engine.registry.add(particule4, gravity);
    engine.registry.add(particule5, gravity);
    engine.registry.add(particule6, gravity);


    ParticleAnchoredSpring anchoredSpring({0, 0, 0}, 5000, 0.4);
    engine.registry.add(particule1.part, anchoredSpring);

    //ParticleDrag ventviolent(1, 0.5);
    //engine.registry.add(particule5, ventviolent);
    //engine.registry.add(particule6, ventviolent);


    // Creation des Contacts generators
    ParticleCable cable1(0.5, 0, particule1, particule2);
    ParticleCable cable2(0.5, 0.5, particule1, particule3);
    ParticleCable cable3(0.3, 0.5, particule1, particule4);
    ParticleCable cable4(0.6, 0.5, particule1, particule5);
    ParticleCable cable5(0.2, 0.5, particule1, particule6);
    
    //ParticleRod rod(0.2, particule3, particule4);

    engine.addContact(cable1);
    engine.addContact(cable2);
    engine.addContact(cable3);
    engine.addContact(cable4);
    engine.addContact(cable5);
    //engine.addContact(rod);

    // ************* Loop Delta Time Fixe ************** //

    double duration = 0;
    double dt = 1.0 / 60.0;
    clock_t start;

    while (window.isOpen())
    {

        start = clock();
        // Traitement des evenements
        window.pollEvents();

        if (window.isKeyDown(ESCAPE))
            window.closeWindow();

        if (window.isKeyDown(ARROW_DOWN))
            particule1.part.position += vec3(0, -0.01, 0);

        else if (window.isKeyDown(ARROW_UP))
            particule1.part.position += vec3(0, 0.01, 0);

        if (window.isKeyDown(ARROW_RIGHT))
            particule1.part.position += vec3(0.01, 0, 0);

        else if (window.isKeyDown(ARROW_LEFT))
            particule1.part.position += vec3(-0.01, 0, 0);

        // Calcul avancement physique
        engine.Update(duration);
        // Affichage
        window.clear();

        float color = 1;

        for (auto *part : particles)
        {
            part->UpdateGraphics();
            part->setColor(vec4(color / (particles.size()), 0, color / (particles.size()), 1));
            if (color == 1)
                part->setColor(vec4(1, 1, 1, 1));
            window.draw(part->mesh, part->shad, part->trans);
            color++;
        }
        window.display();
        duration = (clock() - start) / (double)CLOCKS_PER_SEC;
    }

    return 0;
}