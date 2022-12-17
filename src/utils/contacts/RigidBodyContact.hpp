#pragma once

#include "../RigidBody.hpp"

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

class Contact
{
public:
    vec3 contactPoint;
    vec3 contactnormal;
    float interpenetration;
    RigidBody rb1,rb2;
    TypeContact type;

    Contact(vec3 &cp, vec3 &cn, float inter,RigidBody r1,RigidBody r2, TypeContact tc)
    {
        contactPoint = cp;
        contactnormal = cn;
        interpenetration = inter;
        rb1 = r1;
        rb2 = r2;
        type = tc;
    }
};
