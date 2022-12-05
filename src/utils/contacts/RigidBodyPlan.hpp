#pragma once

#include "RigidBodyPrimitive.hpp"
#include "../maths/Maths.hpp"

class Plane : public Primitive
{
public:
    vec3 normal;
    float planeOffset;

    Plane(RigidBody3D &_body, mat4 _offset, vec3 _normal, float _planeOffset)
    {
        body = _body;
        offset = _offset;
        normal = _normal;
        planeOffset = _planeOffset;
    }
};