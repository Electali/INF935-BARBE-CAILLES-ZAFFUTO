#pragma once
#include "../RigidBody3D.hpp"
#include "../maths/Maths.hpp"

enum TypePrimitive
{
    SphereT,
    BoxT,
    PlaneT
};

class Primitive
{
public:

    Primitive()
    {
    }


    virtual void show(){};

    RigidBody3D body;
    float boundingBox;
    TypePrimitive typeP;
};