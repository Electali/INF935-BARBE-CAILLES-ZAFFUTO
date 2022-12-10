#pragma once

#include <iostream>
#include "math.h"
#include "maths/vector3.hpp"

using namespace std;

class particle
{

public:
    vec3 position;
    vec3 velocity;
    vec3 acceleration;
    vec3 totalForce;

    float inverseMass;
    float damping;

    // Neutral constructor

    particle()
    {
        position = vec3(0.f, 0.f, 0.f);
        velocity = vec3(0.f, 0.f, 0.f);
        acceleration = vec3(0.f, 0.f, 0.f);

        inverseMass = 1;
        damping = 0;
    }

    // constructor with arguments
    particle(vec3 p, vec3 v, vec3 a, float invm, float d)
    {
        position = p;
        velocity = v;
        acceleration = a;

        inverseMass = invm;
        damping = d;
    }

    /*
    ~particule()
    {
        cout << "Particle Destroyed";
    }
    */

    vec3 getPosition()
    {
        return position;
    }

    vec3 getVelocity()
    {
        return velocity;
    }

    vec3 getAcceleration()
    {
        return acceleration;
    }

    float getInvMass()
    {
        return inverseMass;
    }

    float getMass()
    {
        return 1/inverseMass;
    }

    float getDamping()
    {
        return damping;
    }

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