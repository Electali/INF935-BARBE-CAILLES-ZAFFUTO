#pragma once
#include "ParticleForceGenerator.hpp"
#include "../maths/Maths.hpp"
#include "../RigidBody.hpp"

class RigidBodyAnchoredSpring : public ParticleForceGenerator
{
private:
    vec3 m_anchor;
    vec3 m_ptAttach;
    float m_k;
    float m_restlength;


public:
    RigidBodyAnchoredSpring(const vec3 &anchor,const vec3 &attach ,float k, float restlength)
    {
        m_anchor = anchor;
        m_ptAttach = attach;
        m_k = k;
        m_restlength = restlength;
    }

    ~RigidBodyAnchoredSpring()
    {
    }

    void UpdateForce(RigidBody &rb, float duration)
    {
        vec3 pt = rb.LocalToWorld(m_ptAttach);
        vec3 force = pt - m_anchor;
        float norme = force.norme();
        float coeff = -m_k * (norme - m_restlength);
        force.normalise();
        vec3 hooke = multiplication(force, coeff);
        rb.AddForceAtPoint(force,pt);
    }
};