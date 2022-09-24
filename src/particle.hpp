#pragma once

#include <iostream>
#include "math.h"
#include "vector3D.hpp"

using namespace std;

class particle
{

public:
    vector3D position;
    vector3D velocity;
    vector3D acceleration;

    float inverseMass;
    float damping;


    // Neutral constructor

    particle()
    {
        position = vector3D(0, 0, 0);
        velocity = vector3D(0, 0, 0);
        acceleration = vector3D(0, 0, 0);

        inverseMass = 1;
        damping = 0;
    }

    // constructor with arguments
    particle(vector3D p, vector3D v, vector3D a, float invm, float d)
    {
        position = p;
        velocity = v;
        acceleration = a;

        inverseMass =  invm;
        damping = d;
    }

    /*
    ~particule()
    {
        cout << "Particle Destroyed";
    }
    */

    /*   IF WE CHANGE OUR MINDS 

    vector3D getPosition()
    {
        return position;
    }

    vector3D getVelocity()
    {
        return velocity;
    }

    vector3D getAcceleration()
    {
        return acceleration;
    }

    float getMass()
    {
        return 1 / inverseMass;
    }

    float getDamping()
    {
        return damping;
    }
    */

    void show()
    {
        cout << "position : ";
        position.show();
        cout << "velocity : ";
        velocity.show();
        cout << "acceleration : ";
        acceleration.show();
        cout << "Mass : " << (inverseMass) << "\n";
        cout << "damping : " << damping << "\n";
    }

    
};