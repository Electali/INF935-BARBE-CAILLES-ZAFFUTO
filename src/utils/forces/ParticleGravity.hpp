#pragma once
#include "ParticleForceGenerator.hpp"
#include "../maths/vector3.hpp"
#include "../particle.hpp"

class ParticleGravity : public ParticleForceGenerator
{
private:
    vec3 m_gravity;

public:
    ParticleGravity(vec3 &grav)
    {
        m_gravity = grav;
    }

    void UpdateForce(particle &p, float duration)
    {
        if (p.getMass() == 0)
            return; // Masse infinie

        vec3 vec = multiplication(m_gravity, p.getMass());
        p.totalForce += vec;
    }
};