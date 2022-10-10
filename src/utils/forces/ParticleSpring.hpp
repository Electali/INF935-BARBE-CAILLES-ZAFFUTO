#pragma once
#include "ParticleForceGenerator.hpp"
#include "../OpenGl/vector3.hpp"
#include "../particle.hpp"

class ParticleSpring : public ParticleForceGenerator
{
private:
    particle *m_other;
    float m_k;
    float m_restlength;

public:
    ParticleSpring(particle *other, float k, float restlength)
    {
        m_other = other;
        m_k = k;
        m_restlength = restlength;
    }

    ~ParticleSpring()
    {
    }

    void UpdateForce(particle &p, float duration)
    {
        cout << "la pomme volante est en : " << m_other->getPosition().getX() << endl;
        vec3 force = p.getPosition();
        vec3 vec = m_other->getPosition();
        force -= vec;
        float norme = force.norme();
        float coeff = -m_k * (norme - m_restlength);
        force.normalise();
        vec3 hooke = multiplication(force, coeff);
        p.totalForce += hooke;
    }
};