#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "../utils/OpenGl/window.hpp"
#include "../utils/OpenGL/Camera.hpp"

#include <iostream>
#include <vector>

#include "../utils/Engine.hpp"
#include "../utils/RigidBody3D.hpp"
#include "../utils/forces/RigidBodyGravity.hpp"
#include "../utils/forces/RigidBodySpring.hpp"

using RB3DVect = vector<RigidBody3D*>;

using namespace std;

int main(int argc, char** argv)
{

    //****** Partie OPENGL ******//
    
    
    float playerSpeed = 1; //vitesse de la camera

    Window window;
    window.setWireFrame(false);
    window.setBackFaceCulling(false);
    window.setDepthTest(true);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Création du moteur et de la liste des corps rigides du jeu.
	Engine engine; 
	RB3DVect rigidbodies;

	//Creation d'un rigibody 
	vec3 pos = {};
	vec3 vel = {};
	Quaternion orient = Quaternion(1, 0, 0, 0);
    vec3 rotvel = { 5,0,0 };
	
	RigidBody3D RB1 = RigidBody3D(pos, vel, 0.01, orient, rotvel, 2);

	rigidbodies.push_back(&RB1);
	engine.addRigidBody(RB1.rb);
    
	//Creation d'une force de gravité pour les RigidBodies
    vec3 gravVect = {0,1,0};
	RigidBodyGravity gravityRB = RigidBodyGravity(gravVect);

	engine.rigidbodyRegistry.add(RB1.rb, gravityRB);
    

    /*
    //Creation d'un deuxieme rigibody 
    vec3 rotvel2 = { };
    vec3 pos2 = { 0,5,0 };

    RigidBody3D RB2 = RigidBody3D(pos2, vel, 0.01, orient, rotvel2, 2);

    rigidbodies.push_back(&RB2);
    engine.addRigidBody(RB2.rb);


    //Creation d'un ressort
   
    RigidBodySpring spring = RigidBodySpring(&(RB2.rb), pos , pos2, 10.f, 4.f);
    engine.rigidbodyRegistry.add(RB1.rb, spring);

    */

    // ************* Loop Delta Time Flexible ************** //

    double duration = 0;
    double dt = 1.0 / 60.0;
    clock_t start;

    Shader shad;

    Camera cam(45, { 0, 0, 3 });

    while (window.isOpen())
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

        engine.Update(duration);


        // Affichage
        window.clear();


        for (auto* rb : rigidbodies)
        {
            rb->UpdateGraphics();
            window.draw(rb->mesh, shad, rb->trans);  
            rb->setColor(vec4(1, 0.5, 1, 1), shad);
        }

        window.display();
        duration = (clock() - start) / (double)CLOCKS_PER_SEC;
    }


	return 0; 
};