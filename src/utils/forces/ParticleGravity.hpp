#pragma once
#include "ParticleForceGenerator.hpp";
#include "../utils/vector3D.hpp"
#include "../utils/integrator.hpp"

class ParticleGravity : public ParticleForceGenerator
{
private:
    vector3D m_gravity;

public:
    ParticleGravity(vector3D &grav)
    {
        m_gravity = grav;
    }

    void UpdateForce(particle &p, float duration)
    {
        if (p.getMass() == 0)
            return; // Masse infinie

        vector3D vec = multiplication(m_gravity, p.getMass());
        p.totalForce += vec;
    }
};