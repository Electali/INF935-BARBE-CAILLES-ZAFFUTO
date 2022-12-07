#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <vector>

#include "../utils/maths/Maths.hpp"
#include "../utils/contacts/RigidBodySphere.hpp"


using namespace std;

    int main(int argc, char **argv)
{
    vec3 nul = {};
    vec3 p1 = {-6,6};
    vec3 p2 = {7,7};
    vec3 p3 = {4,4};
    vec3 p4  = {-7,7};
    Quaternion q = Quaternion(1,0,0,0);
    
    RigidBody3D rb1 = RigidBody3D(p1, nul, 1,q, nul, 1);
    RigidBody3D rb2 = RigidBody3D(p2, nul, 1,q, nul, 1);
    RigidBody3D rb3 = RigidBody3D(p3, nul, 1,q, nul, 1);
    RigidBody3D rb4 = RigidBody3D(p4, nul, 1,q, nul, 1);

    Sphere prim2 = Sphere(rb2, 1.5f, 1.5f);
    Sphere prim1 = Sphere(rb1, 1.5f, 1.5f);
    Sphere prim3 = Sphere(rb2, 1.5f, 1.5f);
    Sphere prim4 = Sphere(rb2, 1.5f, 1.5f);

    Pool primitives;

    primitives.push_back(prim1);
    primitives.push_back(prim2);
    primitives.push_back(prim3);
    primitives.push_back(prim4);

    Octree octree = Octree(0, 1, nul, 8, primitives);


    octree.Build();
    cout << "La profondeur de l'octree est " << octree.Profondeur() << endl;
    octree.AfficherEtat();
}