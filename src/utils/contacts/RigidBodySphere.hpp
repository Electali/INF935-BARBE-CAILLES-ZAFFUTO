#pragma once
#include "RigidBodyPrimitive.hpp"

class Sphere : public Primitive
{
public:
    float radius;

    Sphere(RigidBody3D &_body, float _boundingBox, float _radius)
    {
        body = _body;
        boundingBox = _boundingBox;
        radius = _radius;
        typeP = SphereT;
    }

    void show()
   {
      std::cout << "Sphere" << std::endl;
   }
};