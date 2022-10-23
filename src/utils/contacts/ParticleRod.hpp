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

    unsigned int addContact(vector<ParticleContact*> &contacts, unsigned int limit) const
    {
        float currentLen = currentLength();
        if (currentLen == m_length)
            return 0;
        contacts.push_back(new ParticleContact(particles[0],particles[1]));

        vec3 normal = particles[1]->getPosition() - particles[0]->getPosition();
        normal.normalise();
        if (currentLen > m_length)
        {
            contacts.back()->contactNormal = normal;
            contacts.back()->penetration = currentLen - m_length;
        }
        else
        {
            contacts.back()->contactNormal = multiplication(normal,-1);
            contacts.back()->penetration = m_length - currentLen;
        }

        contacts.back()->restitution = 0;
        return 1;
    }
};