#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "../utils/OpenGl/window.hpp"
#include <vector>
#include <cstdlib>

#include "../utils/maths/Octree.hpp"
#include "../utils/contacts/RigidBodySphere.hpp"
#include "../utils/contacts/RigidBodyContactPotentiel.hpp"


using namespace std;

    int main(int argc, char **argv)
{
    Window window;
    srand(time(NULL));

    Pool primitives;
    vec3 nul = {};
    vector<float> randnumb;
    Quaternion q = Quaternion(1,0,0,0);
    int nb_prim = 10;

    
    for(int n=0; n<nb_prim*3; n++)
    {
        randnumb.push_back(rand() % 16 - 8); // generate numbers  
    }
    

    for(int a = 0; a<nb_prim*3; a+=3)
    {
        float x = randnumb[a];
        float y = randnumb[a+1];
        float z = randnumb[a+2];
        vec3 ajout = vec3(x,y,z);
        RigidBody3D rb = RigidBody3D(ajout, nul, 1,q, nul, 1);
        Sphere * prim = new Sphere(rb, 1.5f, 1.5f);
        primitives.push_back(prim);
    }
    cout << "Le nombre de prim générés est de " << primitives.size() << endl;

    Potentiels vexit;

    Octree octree = Octree(0, 1, nul, 8, primitives);
    octree.Build(vexit);
    cout << "La profondeur de l'octree est " << octree.Profondeur() << endl;
    octree.AfficherEtat();
    cout << vexit.size();

    cout <<"Liberation de mémoire" << endl;
    cout << primitives.size() << endl;
    for(auto p : vexit)
    {
        p.Prim1->show();
    }

}