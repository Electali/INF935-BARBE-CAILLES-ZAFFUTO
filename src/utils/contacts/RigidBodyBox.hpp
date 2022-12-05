#pragma once
#include "RigidBodyPrimitive.hpp"

class Sphere : public Primitive
{

public:
   Sphere(RigidBody3D &_body, mat4 _offset, vec3 &_halfsize)
   {
      body = _body;
      offset = _offset;
      halfSize = _halfsize;
   }

private:
   vec3 halfSize;
};