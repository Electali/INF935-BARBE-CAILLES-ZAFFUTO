#pragma once

#include "RigidBodyPrimitive.hpp"

class ContactPotentiel
{
public:
    ContactPotentiel(Primitive &primitive1, Primitive &primitive2)
    {
        Prim1 = primitive1;
        Prim2 = primitive2;
    }

private:
    Primitive Prim1;
    Primitive Prim2;
};