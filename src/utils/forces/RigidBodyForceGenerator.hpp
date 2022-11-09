#pragma once
#include "../RigidBody.hpp"

class RigidBodyForceGenerator
{
public:
    virtual void UpdateForce(RigidBody& rb, float duration) = 0;
};