#pragma once
#include "RigidBodyPrimitive.hpp"

class Box : public Primitive
{

public:
   Box(RigidBody3D &_body, float _boundingBox, vec3 &_halfsize)
   {
      body = _body;
      boundingBox = _boundingBox;
      halfSize = _halfsize;
   }

private:
   vec3 halfSize;
};