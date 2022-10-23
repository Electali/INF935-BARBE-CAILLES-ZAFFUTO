#pragma once
#include "ParticleForceGenerator.hpp"
#include "../OpenGl/vector3.hpp"
#include "../particle.hpp"

class ParticleAnchoredSpring : public ParticleForceGenerator
{
private:
    vec3 m_anchor;
    float m_k;
    float m_restlength;

public:
    ParticleAnchoredSpring(const vec3 &anchor, float k, float restlength)
    {
        m_anchor = anchor;
        m_k = k;
        m_restlength = restlength;
    }

    ~ParticleAnchoredSpring()
    {
    }

    void UpdateForce(particle &p, float duration)
    {
        vec3 force = p.getPosition();
        force -= m_anchor;
        float norme = force.norme();
        float coeff = -m_k * (norme - m_restlength);
        force.normalise();
        vec3 hooke = multiplication(force, coeff);
        p.totalForce += hooke;
    }
};