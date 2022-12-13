#pragma once
#include "../RigidBody3D.hpp"
#include "../maths/Maths.hpp"

class Primitive
{
public:
    Primitive()
    {
    }


    virtual void show(){};

    RigidBody3D body;
    float boundingBox;
};