#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "../utils/OpenGl/window.hpp"
#include <vector>
#include <cstdlib>

#include "../utils/OpenGl/window.hpp"
#include "../utils/OpenGL/Camera.hpp"

#include "../utils/maths/Octree.hpp"
#include "../utils/contacts/RigidBodyPrimitive.hpp"
#include "../utils/contacts/RigidBodyContactPotentiel.hpp"
#include "../utils/contacts/RigidBodyContactGenerator.hpp"

#include "../utils/Engine.hpp"
#include "../utils/forces/RigidBodyGravity.hpp"

#include "../utils/RigidBody3D.hpp"


using RB3DVect = vector<RigidBody3D*>;




using namespace std;

    int main(int argc, char **argv)
{
    //****** Partie OPENGL ******//
    
    
    float playerSpeed = 1; //vitesse de la camera

    Window window;
    window.setWireFrame(false);
    window.setBackFaceCulling(false);
    window.setDepthTest(true);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



    //****** Partie Physique ******//

    // Creation du moteur et de la liste des corps rigides du jeu.
	Engine engine; 
	RB3DVect rigidbodies;
    
    
    
    vec3 nul = {};
    Quaternion q = Quaternion(1,0,0,0);


    // Création du sol
    vec3 p3 = vec3(0,0,0);
    RigidBody3D rb3 = RigidBody3D(p3, nul, 1,q, nul, 1);
    vec3 normal = vec3(0, 1, 0);
    Plane * prim3 = new Plane (&rb3, 10.0f, normal, 0);
    engine.addPrimitive(prim3);
    rigidbodies.push_back(&rb3);
	engine.addRigidBody(rb3.rb);


    // Création du cube qui tombe
    vec3 p4 = vec3(0,5,0);
    vec3 rotvel4 = vec3(2,2,2);
    RigidBody3D rb4 = RigidBody3D(p4, nul, 1,q, rotvel4, 1);
    vec3 halfSize = vec3(0.5f, 0.5f, 0.5f);
    Box * prim4 = new Box (&rb4, 0.5f, halfSize);
    engine.addPrimitive(prim4);
    rigidbodies.push_back(&rb4);
	engine.addRigidBody(rb4.rb);


    vec3 gravVect = {0,-0.5,0};
	RigidBodyGravity gravityRB = RigidBodyGravity(gravVect);

	engine.rigidbodyRegistry.add(rb4.rb, gravityRB);

    bool iscollisioning = false;

    // ************* Loop Delta Time Flexible ************** //

    double duration = 0;
    double dt = 1.0 / 60.0;
    clock_t start;

    Shader shad;

    Camera cam(45, { 0, 0, 5 });

    while (window.isOpen() && !iscollisioning ) // Arrete le programme lors de la collision
    {
        start = clock();
        // Traitement des evenements
        window.pollEvents();

        if (window.isKeyDown(CTRL)) {
            playerSpeed = 2;
            //cam.fov = 30;
        }
        else {
            playerSpeed = 1;
            //cam.fov = 45;
        }

        if (window.isKeyDown(ESCAPE))
            window.closeWindow();


        if (window.isKeyDown(S))
        {
            cam.moveBackwards(playerSpeed, dt);
        }
        else if (window.isKeyDown(Z))
        {
            cam.moveForward(playerSpeed, dt);
        }

        if (window.isKeyDown(Q))
        {
            cam.moveLeft(playerSpeed, dt);
        }
        else if (window.isKeyDown(D))
        {
            cam.moveRight(playerSpeed, dt);
        }

        if (window.isKeyDown(SHIFT))
        {
            cam.moveDown(playerSpeed, dt);
        }
        else if (window.isKeyDown(SPACE))
        {
            cam.moveUp(playerSpeed, dt);
        }

        shad.setUniform("view", cam.view());
        shad.setUniform("projection", cam.projection(window));

        // Calcul avancement physique

        iscollisioning = engine.Update(duration);

        // Affichage
        window.clear();

        int col = 0;
        for (auto* rb : rigidbodies)
        {
            rb->UpdateGraphics();
            if (col == 0) rb->setColor(vec4(0.42001, 0.61367, 0.04535, 1), shad);
            if (col == 1) rb->setColor(vec4(0.0625, 0.01367, 0.4453125, 1), shad);
            window.draw(*(rb->mesh()), shad, rb->trans);

            col++;
        }

        window.display();
        duration = (clock() - start) / (double)CLOCKS_PER_SEC;
    }

    engine.showCollisions();

	return 0; 
}