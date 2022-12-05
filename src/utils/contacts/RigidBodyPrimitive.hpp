#pragma once
#include "../RigidBody3D.hpp"
#include "../maths/Maths.hpp"

class Primitive
{
public:
    RigidBody3D body;
    mat4 offset;
};