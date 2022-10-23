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
    vec3 pos2 = vec3(0, -0.3, 0);
    vec3 pos3 = vec3(0, -0.5, 0);
    vec3 pos4 = vec3(0.4, 0, 0);
    vec3 pos5 = vec3(0, 0.4, 0);
    vec3 pos6 = vec3(0, 0.3, 0);
    vec3 pos7 = vec3(0.3, 0, 0);

    vec3 vitesse = vec3(0, 0, 0);
    vec3 accel = vec3(0, 0, 0);

    particle3D particule1 = particle3D(pos1, vitesse, accel, 0.0000001, 0.99);
    engine.addParticle(particule1.part);

    particle3D particule2 = particle3D(pos2, vitesse, accel, 5, 0.99);
    engine.addParticle(particule2.part);

    particle3D particule3 = particle3D(pos3, vitesse, accel, 5, 0.99);
    engine.addParticle(particule3.part);

    /*
    particle3D particule4 = particle3D(pos4, vitesse, accel, 5, 0.99);
    engine.addParticle(particule4.part);

    particle3D particule5 = particle3D(pos5, vitesse, accel, 5, 0.99);
    engine.addParticle(particule5.part);

    particle3D particule6 = particle3D(pos6, vitesse, accel, 5, 0.99);
    engine.addParticle(particule6.part);

    particle3D particule7 = particle3D(pos7, vitesse, accel, 5, 0.99);
    engine.addParticle(particule7.part);

    */
    
    particles.push_back(&particule1);
    particles.push_back(&particule2);
    particles.push_back(&particule3);
   /* particles.push_back(&particule4);
    particles.push_back(&particule5);
    particles.push_back(&particule6);
    particles.push_back(&particule7);
*/


    // Creation des forces
    vec3 grav = vec3(0, -10, 0);
    ParticleGravity gravity = ParticleGravity(grav);
    engine.registry.add(particule2.part, gravity);
    engine.registry.add(particule3.part, gravity);
 /* engine.registry.add(particule4.part, gravity);
    engine.registry.add(particule5.part, gravity);
    engine.registry.add(particule6.part, gravity);
    engine.registry.add(particule7.part, gravity);
*/

    // Creation des Contacts generators
    ParticleCable cable1 = ParticleCable(0.5, 0.5, particule1.part, particule2.part);
    ParticleCable cable2 = ParticleCable(0.5, 0.5, particule2.part, particule3.part);
   /* ParticleCable cable3 = ParticleCable(0.1, 0.5, particule3.part, particule4.part);
    ParticleCable cable4 = ParticleCable(0.1, 0.5, particule4.part, particule5.part);
    ParticleCable cable5 = ParticleCable(0.1, 0.5, particule5.part, particule6.part);
    ParticleCable cable6 = ParticleCable(0.1, 0.5, particule6.part, particule7.part);
    */

    engine.addContact(cable1);
    engine.addContact(cable2);
    /*
    engine.addContact(cable3);
    engine.addContact(cable4);
    engine.addContact(cable5);
    engine.addContact(cable6);
    */
    

    // ************* Loop Delta Time Fixe ************** //

    double duration = 0;
    double dt = 1.0 / 60.0;
    clock_t start;

    while (window.isOpen())
    {
        //particule1.part.position.show();

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
        engine.Update(dt);

        // Affichage
        window.clear();

        float color = 1;

        for (Particles3D::iterator i = particles.begin(); i != particles.end(); i++)
        {
            particle3D part = **i;

            part.UpdateGraphics();
            part.setColor(vec4(0, color / (particles.size()), color / (particles.size()), 1));
            window.draw(part.mesh, part.shad, part.trans);
            color++;
        }
        window.display();
        //duration = (clock() - start) / (double)CLOCKS_PER_SEC;
    }

    return 0;
}