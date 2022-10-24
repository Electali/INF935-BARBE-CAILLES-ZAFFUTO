#pragma once
#include "ParticleForceGenerator.hpp"
#include "../maths/vector3.hpp"
#include "../particle.hpp"

class ParticleAnchoredBungee : public ParticleForceGenerator
{
private:
    vec3 m_anchor;
    float m_k;
    float m_restlength;

public:
    ParticleAnchoredBungee(vec3 &anchor, float k, float restlength) 
    {
        m_anchor = anchor;
        m_k = k;
        m_restlength = restlength;
    }

    ~ParticleAnchoredBungee() 
    {    
    }

    void UpdateForce(particle &p, float duration)
    {
        vec3 force = p.getPosition();
        force -= m_anchor;
        float norme = force.norme();
        float coeff = -m_k * (norme - m_restlength);
        force.normalise();
        vec3 hooke = multiplication(force, -coeff);
        p.totalForce += hooke;
    }
};