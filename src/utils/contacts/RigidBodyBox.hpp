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
      typeP = BoxT;

      for (int i = 0; i < 8; i++)
        {
         int x = (i & 4) ? halfSize.x : -halfSize.x;   // On alterne tous les 4 coups
         int y = (i & 2) ? halfSize.y : -halfSize.y;   // On alterne tous les 2 coups
         int z = (i & 1) ? halfSize.z : -halfSize.z;   // On alterne un coup sur 2
         vertices[i] = vec3(x,y,z);
        }
   }

   void show()
   {
      std::cout << "Box" << std::endl;
      for(int i = 0; i<8;i++)
      {
         vertices[i].show();
      }
   }  

public:
   vec3 halfSize;
   vec3 vertices [8];
};