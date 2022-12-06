#pragma once
#include "../RigidBody3D.hpp"
#include "../maths/Maths.hpp"

class Primitive
{
public:
    Primitive()
    {
    }

    RigidBody3D body;
    float boundingBox;
};