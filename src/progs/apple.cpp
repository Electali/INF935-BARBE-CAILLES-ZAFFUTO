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
#include "../utils/Engine.hpp"
#include "../utils/forces/ParticleGravity.hpp"
#include "../utils/forces/ParticleAnchoredSpring.hpp"
#include "../utils/forces/ParticleSpring.hpp"
#include "../utils/forces/ParticleBuoyancy.hpp"
#include "particleWorld.hpp"
#include "../utils/contacts/ParticleRod.hpp"
#include "../utils/contacts/ParticleCable.hpp"


using namespace std;

int main(int argc, char **argv)
{

    if (argc != 2)
    {
        cout << "Pour utiliser le programme, il suffit de rentrer en parametre une hauteur (en metres)." << endl;
        return 0;
    }
    Engine engine = Engine();

    particleWorld world = particleWorld(10, 10);

    // Creation des elements d'OpenGl
    Window window;
    window.setWireFrame(false);
    window.setBackFaceCulling(false);

    Shader shader1;
    glPointSize(25); // C'est juste pour mieux voir le point
    Point mesh1;

    Transform trans1;
    Transform trans2;

    Point meshSpring;

    Transform transSpring;

    float hauteur = (float)strtod(argv[1], NULL);

    vec3 Pomme = vec3(0.1, hauteur, 0);
    vec3 VitesseChute = vec3(0, 0, 0);
    vec3 AccelPomme = vec3(0, 0, 0);
    vec3 GraviteVec = vec3(0, -10, 0);
    vec3 Newton = vec3(0, 1.63, 0);

    vec3 PommeVolante = (0.25, hauteur, 0);
    vec3 VitessePommeVolante = vec3(0, 0, 0);
    vec3 AccelPommeVolante = vec3(0, 0, 0);

    particle Projectile = particle(Pomme, VitesseChute, AccelPomme, 0.5, 0.97);
    particle Projectile2 = particle(PommeVolante, VitessePommeVolante, AccelPommeVolante, 0.5, 0.999);

    ParticleGravity Gravity = ParticleGravity(GraviteVec);

    vec3 springPoint = vec3(0, hauteur, 0);

    ParticleAnchoredSpring anchoredSpring = ParticleAnchoredSpring(springPoint, 200, 0.1);
    ParticleSpring PommeSpring = ParticleSpring(&Projectile2, 200, 0.5);
    ParticleSpring PommeSpring2 = ParticleSpring(&Projectile, 200, 0.5);

    //ParticleBuoyancy Buoyancy = ParticleBuoyancy(0.5, 50, 0, 2);

    //transSpring.setPos(springPoint.x, springPoint.y, 0);
    Projectile.show();

    engine.addParticle(Projectile);
    engine.addParticle(Projectile2);

    engine.registry.add(Projectile, Gravity);

    engine.registry.add(Projectile, anchoredSpring);
    engine.registry.add(Projectile, PommeSpring);
    engine.registry.add(Projectile2, PommeSpring2);

    // Creation de particules pour collisions
    vec3 pos1 = vec3(0, 0, 0);
    vec3 pos2 = vec3(1, 0, 0);
    vec3 pos3 = vec3(0, 1, 0);

    vec3 vitesse = vec3(1, 0, 0);
    vec3 accel = vec3(0, 0, 0);

    particle particule1 = particle(pos1, vitesse, accel, 0.5, 0.999);
    particle particule2 = particle(pos2, vitesse, accel, 0.5, 0.999);
    particle particule3 = particle(pos3, vitesse, accel, 0.5, 0.999);

    ParticleCable cable1 = ParticleCable(2, 3, particule1, particule2);
    ParticleCable cable2 = ParticleCable(2, 3, particule2, particule3);
    ParticleCable cable3 = ParticleCable(2, 3, particule3, particule1);

    ParticleContact* contacts[3] = {&cable1, &cable2, &cable3};



    //engine.registry.add(Projectile, Buoyancy);

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

        float oldX = Projectile.getPosition().getX();
        float oldY = Projectile.getPosition().getY();
        float oldZ = Projectile.getPosition().getZ();

        float oldX2 = Projectile2.getPosition().getX();
        float oldY2 = Projectile2.getPosition().getY();
        float oldZ2 = Projectile2.getPosition().getZ();

        engine.Update(dt);
        if (Projectile.getPosition().getY() <= Newton.getY())
            // falling = false;
            Projectile.show();
            chrono += dt;

        trans1.moveX(Projectile.getPosition().getX() - oldX);
        trans1.moveY(Projectile.getPosition().getY() - oldY);
        trans1.moveZ(Projectile.getPosition().getZ() - oldZ);

        trans2.moveX(Projectile2.getPosition().getX() - oldX2);
        trans2.moveY(Projectile2.getPosition().getY() - oldY2);
        trans2.moveZ(Projectile2.getPosition().getZ() - oldZ2);

        // Affichage
        window.clear();
        shader1.setUniform("color", vec4(1, 0.5, 0, 1));
        window.draw(mesh1, shader1, trans1);
        shader1.setUniform("color", vec4(0.5, 1, 0, 1));
        window.draw(mesh1, shader1, transSpring);
        shader1.setUniform("color", vec4(1, 0.3, 1, 1));
        window.draw(mesh1, shader1, trans2);
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