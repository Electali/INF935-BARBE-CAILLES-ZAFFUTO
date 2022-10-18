#pragma once

#include "../particle.hpp"
#include "ParticleContactGenerator.hpp"
#include "ParticleContact.hpp"
#include "ParticleLink.hpp"

class ParticleRod : public ParticleLink
{
public:
    float m_length;

    ParticleRod(float length, particle &p0, particle &p1)
    {
        m_length = length;
        particles[0] = &p0;
        particles[1] = &p1;
    }

    unsigned int addContact(ParticleContact *contact, unsigned int limit) const
    {
        float currentLen = currentLength();
        if (currentLen == m_length)
            return 0;

        contact->particles[0] = particles[0];
        contact->particles[1] = particles[1];

        vec3 normal = particles[1]->getPosition() - particles[0]->getPosition();
        normal.normalise();
        if (currentLen > m_length)
        {
            contact->contactNormal = normal;
            contact->penetration = currentLen - m_length;
        }
        else
        {
            contact->contactNormal = multiplication(normal,-1);
            contact ->penetration = m_length - currentLen;
        }

        contact->restitution = 0;
        
        return 1;
    }
};