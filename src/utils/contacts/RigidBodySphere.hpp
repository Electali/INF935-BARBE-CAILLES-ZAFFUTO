#pragma once
#include "RigidBodyPrimitive.hpp"

class Sphere : public Primitive
{
public:
    float radius;

    Sphere(RigidBody3D &_body, mat4 _offset, float _radius)
    {
        body = _body;
        offset = _offset;
        radius = _radius;
    }
};