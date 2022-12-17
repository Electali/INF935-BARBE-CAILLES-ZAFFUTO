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


    //****** Partie Physique ******//

	// Creation du moteur et de la liste des corps rigides du jeu.
	Engine engine; 
	RB3DVect rigidbodies;

	//Creation des spinning rigibodies  
    vec3 vel = {0,0,0};
    vec3 vel5 = {1,1,0};
	Quaternion orient = Quaternion(1, 0, 0, 0);


	vec3 pos = {-1,-1,0};
    vec3 pos2 = {-1,0,0};
    vec3 pos3 = {-1,1,0};
    vec3 pos4 = {0,0,0};
    vec3 pos5 = {-0.5,0.5,0};
    vec3 pos6 = {0,-0.5,0};

    vec3 rotvel = {1,0,0};
    vec3 rotvel2 = {1,1,1};
    vec3 rotvel3 = {0,0,1};
    vec3 rotvel4 = {0,1,0};
    vec3 rotvel5 = {1,1,1};
    vec3 rotvel6 = {};
	

    //Spinning RB en X 
	RigidBody3D RB1 = RigidBody3D(pos, vel, 0.01, orient, rotvel, 2);
    rigidbodies.push_back(&RB1);
	engine.addRigidBody(RB1.rb);

    //Spinning RB en Y 
    RigidBody3D RB2 = RigidBody3D(pos2, vel, 0.01, orient, rotvel2, 2);
    rigidbodies.push_back(&RB2);
	engine.addRigidBody(RB2.rb);

    //Spinning RB en Z 
    RigidBody3D RB3 = RigidBody3D(pos3, vel, 0.01, orient, rotvel3, 2);
    rigidbodies.push_back(&RB3);
	engine.addRigidBody(RB3.rb);


    //Spinning RB en X,Y,Z 
    RigidBody3D RB4 = RigidBody3D(pos4, vel, 0.01, orient, rotvel4, 2);
    rigidbodies.push_back(&RB4);
	engine.addRigidBody(RB4.rb);


    //RB tournant en X,Y,Z et jette en l'air
    RigidBody3D RB5 = RigidBody3D(pos5, vel5, 0.01, orient, rotvel5, 2);
    rigidbodies.push_back(&RB5);
	engine.addRigidBody(RB5.rb);


    //RB accroché vi un ressort au RB4
    RigidBody3D RB6 = RigidBody3D(pos6, vel, 0.1, orient, rotvel6, 2);
    rigidbodies.push_back(&RB6);
	engine.addRigidBody(RB6.rb);

	//Creation d'une force de gravite pour les RigidBodies
    vec3 gravVect = {0,-0.5,0};
	RigidBodyGravity gravityRB = RigidBodyGravity(gravVect);

	engine.rigidbodyRegistry.add(RB5.rb, gravityRB);


    //Creation d'un ressort
   
    RigidBodySpring spring = RigidBodySpring(&(RB4.rb), {0,0.5,0} , {0.2,0,0}, 100.f, 1.0f);
    engine.rigidbodyRegistry.add(RB6.rb, spring);
 

    // ************* Loop Delta Time Flexible ************** //

    double duration = 0;
    double dt = 1.0 / 60.0;
    clock_t start;

    Shader shad;

    Camera cam(45, { 0, 0, 5 });

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

        int col = 0;
        for (auto* rb : rigidbodies)
        {
            rb->UpdateGraphics();
            rb->setColor(vec4(0.0625, 0.01367, 0.4453125, 1), shad);
            if (col<=2) rb->setColor(vec4(0.0625, 0.01367, 0.4453125, 1), shad);
            else if (col == 3) rb->setColor(vec4(150,255,0, 1), shad);
            else if (col == 4) rb->setColor(vec4(150,0,255, 1), shad);
            else if (col == 5) rb->setColor(vec4(255,150,0, 1), shad);

            window.draw(*(rb->mesh()), shad, rb->trans);

            col++;
        }

        window.display();
        duration = (clock() - start) / (double)CLOCKS_PER_SEC;
    }


	return 0; 
};