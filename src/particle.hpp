#pragma once

#include <iostream>
#include "math.h"
#include "vector3D.hpp"

using namespace std;

class particle
{

private:
    vector3D Position;
    vector3D Velocity;
    vector3D Acceleration;

    float InverseMass;
    float Damping;

public:
    // Neutral constructor

    particle()
    {
        Position = vector3D(0, 0, 0);
        Velocity = vector3D(0, 0, 0);
        Acceleration = vector3D(0, 0, 0);

        InverseMass = 1;
        Damping = 0;
    }

    // constructor with arguments
    particle(vector3D p, vector3D v, vector3D a, float m, float d)
    {
        Position = p;
        Velocity = v;
        Acceleration = a;

        InverseMass = 1 / m;
        Damping = d;
    }

    vector3D getPosition()
    {
        return Position;
    }

    vector3D getVelocity()
    {
        return Velocity;
    }

    vector3D getAcceleration()
    {
        return Acceleration;
    }

    float getMass()
    {
        return 1 / InverseMass;
    }

    float getDamping()
    {
        return Damping;
    }

    void show()
    {
        cout << "Position : ";
        Position.show();
        cout << "Velocity : ";
        Velocity.show();
        cout << "Acceleration : ";
        Acceleration.show();
        cout << "Mass : " << (1 / InverseMass) << "\n";
        cout << "Damping : " << Damping << "\n";
    }
};