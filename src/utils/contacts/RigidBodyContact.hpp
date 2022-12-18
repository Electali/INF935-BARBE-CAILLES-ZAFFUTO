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

    void show()
    {
        std::cout << "************************************************* " << std::endl;
        std::cout << "Le point d'impact est : " << std::endl;
        contactPoint.show();
        std::cout << "La normal de contact est : " << std::endl;
        contactnormal.show();
        std::cout << "L'interpenetration du contact est de : " << interpenetration << std::endl;
        std::cout << "************************************************* " << std::endl;
    }
};
