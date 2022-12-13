#pragma once

#include "RigidBodyPrimitive.hpp"
#include "../maths/Maths.hpp"

class Plane : public Primitive
{
public:
    vec3 normal;
    float planeOffset;

    Plane(RigidBody3D &_body,float _boundingBox , vec3 _normal, float _planeOffset)
    {
        body = _body;
        boundingBox = _boundingBox;
        normal = _normal;
        planeOffset = _planeOffset;
    }

    ~Plane()
   {}

    void show()
   {
      std::cout << "Plan" << std::endl;
   }
};