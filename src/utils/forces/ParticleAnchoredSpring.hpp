#pragma once
#include "ParticleForceGenerator.hpp";
#include "../particle.hpp"

class ParticleAnchoredSpring : public ParticleForceGenerator
{
private:
    vec3 &m_anchor;

    float m_k;
    float m_restlength;

public:
    void UpdateForce(particle &p, float duration)
    {
        vec3 force = p.getPosition();
        force -= m_anchor;
        float norme = force.norme();
        float coeff = -m_k * (norme - m_restlength);
        vec3 hooke = multiplication(force, coeff);
        p.totalForce += hooke;
    }
};