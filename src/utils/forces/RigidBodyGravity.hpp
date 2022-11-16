#pragma once
#include "RigidBodyForceGenerator.hpp"
#include "../RigidBody.hpp"

class RigidBodyGravity : public RigidBodyForceGenerator
{
private:
    vec3 m_gravity;

public:
    RigidBodyGravity(vec3 grav)
    {
        m_gravity = grav;
    }

    void UpdateForce(RigidBody& rb, float duration)
    {
        if (rb.inverseMass == 0)
            return; // Masse infinie

        vec3 vec = multiplication(m_gravity,(1/ rb.inverseMass));
        rb.AddForce(vec);
    }
};