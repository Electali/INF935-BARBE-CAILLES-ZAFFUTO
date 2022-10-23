#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <windows.h>

#include <iostream>
#include <vector>

#include "../utils/OpenGl/window.hpp"
#include "../utils/Engine.hpp"
#include "../utils/contacts/ParticleRod.hpp"
#include "../utils/contacts/ParticleCable.hpp"
#include "../utils/particle3D.hpp"
#include "../utils/forces/ParticleGravity.hpp"

using namespace std;

using Particles3D = vector<particle3D *>;

int main(int argc, char **argv)
{
    // Vecteur des particules dans notre Moteur
    Particles3D particles;

    Engine engine = Engine();

    // Creation des elements d'OpenGl
    Window window;
    window.setWireFrame(false);
    window.setBackFaceCulling(false);

    glPointSize(25); // C'est juste pour mieux voir le point*

    // Creation de particules
    vec3 pos1 = vec3(0, 0, 0);
    vec3 pos2 = vec3(0.5, 0, 0);
    vec3 pos3 = vec3(0, 0.5, 0);

    vec3 vitesse = vec3(0, 0, 0);
    vec3 vitessex = vec3(0.5, 0, 0);
    vec3 accel = vec3(0, 0, 0);
    vec3 vitessey = vec3(-0.5, 2.5, 0);

    particle3D particule1 = particle3D(pos1, vitesse, accel, 0.1, 0.99);
    engine.addParticle(particule1.part);

    particle3D particule2 = particle3D(pos2, vitessex, accel, 0.2, 0.99);
    engine.addParticle(particule2.part);

    particle3D particule3 = particle3D(pos3, vitessey, accel, 0.1, 0.99);
    engine.addParticle(particule3.part);

    particles.push_back(&particule1);
    particles.push_back(&particule2);
    particles.push_back(&particule3);

    // Creation des Contacts generators
    ParticleCable cable1 = ParticleCable(0.6, 0, particule1.part, particule2.part);
    ParticleCable cable2 = ParticleCable(0.8, 0, particule2.part, particule3.part);
    ParticleCable cable3 = ParticleCable(0.6, 0, particule3.part, particule1.part);

    /*engine.addContact(cable1);
    engine.addContact(cable2);
    engine.addContact(cable3);*/

    // Creation des forces
    vec3 grav = vec3(0, -10, 0);
    ParticleGravity gravity = ParticleGravity(grav);
    engine.registry.add(particule1.part, gravity);
    engine.registry.add(particule3.part, gravity);

    // ************* Loop Delta Time Fixe ************** //

    double dt = 1.0 / 60.0;
    double duration = 0;
    clock_t start;


    while (window.isOpen())
    {
        start = clock();
        // Traitement des evenements
        window.pollEvents();

        if (window.isKeyDown(ESCAPE))
            window.closeWindow();

        // Calcul avancement physique
        engine.Update(duration);
    
        // Affichage
        window.clear();

        float color = 1;

        for (Particles3D::iterator i = particles.begin(); i != particles.end(); i++)
        {
            particle3D part = **i;
            part.UpdateGraphics();
            part.setColor(vec4(0, color/(particles.size()), 0, 1));
            window.draw(part.mesh, part.shad, part.trans);

            color++;
        }
        window.display();
        duration = (clock() - start) / (double) CLOCKS_PER_SEC;
    }

    return 0;
}