#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <vector>


#include "../utils/Engine.hpp"
#include "../utils/maths/Octree.hpp"
#include "../utils/maths/vector3.hpp"
#include "../utils/contacts/RigidBodySphere.hpp"
#include "../utils/RigidBody3D.hpp"

using RB3DVect = vector<RigidBody3D*>;

using namespace std;

    int main(int argc, char **argv)
{

    //Engine engine; 
	//RB3DVect rigidbodies;

    
    vec3 vel = {0,0,0};
    vec3 p1 = {-6,6};
    vec3 p2 = {7,7};
    vec3 p3 = {4,4};
    vec3 p4  = {-7,7};
    Quaternion q = Quaternion(1,0,0,0);
    
    vec3 rotvel = {1,0,0};
    vec3 rotvel2 = {1,1,1};
    vec3 rotvel3 = {0,0,1};
    vec3 rotvel4 = {0,1,0};
    
    cout << "ta mère"<< endl;
    RigidBody3D rb1 = RigidBody3D(p1, vel, 0.1,q, rotvel, 1);
    RigidBody3D rb2 = RigidBody3D(p2, vel, 0.1,q, rotvel2, 1);
    RigidBody3D rb3 = RigidBody3D(p3, vel, 0.1,q, rotvel3, 1);
    RigidBody3D rb4 = RigidBody3D(p4, vel, 0.1,q, rotvel4, 1);
    cout << "main"<< endl;

    /*
    Sphere prim2 = Sphere(rb2, 1.5f, 1.5f);
    Sphere prim1 = Sphere(rb1, 1.5f, 1.5f);
    Sphere prim3 = Sphere(rb2, 1.5f, 1.5f);
    Sphere prim4 = Sphere(rb2, 1.5f, 1.5f);

   
    Pool primitives;

    primitives.push_back(prim1);
    primitives.push_back(prim2);
    primitives.push_back(prim3);
    primitives.push_back(prim4);

    cout << "LOL"<< endl;

    Octree octree = Octree(0, 1, nul, 8, primitives);

    cout << "JAJ"<< endl;
    octree.Build();
    cout << "La profondeur de l'octree est " << octree.Profondeur() << endl;
    octree.AfficherEtat();
    */
}