#pragma once

#include "RigidBodyPrimitive.hpp"

enum TypeContact
{
    PointFace,
    EdgeEdgeNP,
    EdgeFace,
    FaceFace,
    PointEdge,
    PointPoint,
    EdgeEdgeP
};

class CollisionData
{
public:
    CollisionData(Primitive &primitive1, Primitive &primitive2, TypeContact typeContact)
    {
        Prim1 = primitive1;
        Prim2 = primitive2;
        type = typeContact;
    }

private:
    Primitive Prim1;
    Primitive Prim2;
    TypeContact type;
};