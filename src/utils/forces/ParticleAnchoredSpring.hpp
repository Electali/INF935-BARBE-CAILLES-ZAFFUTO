#pragma once
#include "ParticleForceGenerator.hpp";
#include "../particle.hpp"

class ParticleAnchoredSpring : public ParticleForceGenerator
{
private:
    vector3D &m_anchor;

    float m_k;
    float m_restlength;

public:
    void UpdateForce(particle &p, float duration)
    {
        vector3D force = p.getPosition();
        force -= m_anchor;
        float norme = force.norme();
        float coeff = -m_k * (norme - m_restlength);
        vector3D hooke = multiplication(force, coeff);
        p.totalForce += hooke;
    }
};