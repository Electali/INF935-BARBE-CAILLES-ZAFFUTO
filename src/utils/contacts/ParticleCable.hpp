#pragma once

#include "../particle.hpp"
#include "ParticleContactGenerator.hpp"
#include "ParticleContact.hpp"
#include "ParticleLink.hpp"

class ParticleCable : public ParticleLink
{
public:
    float maxLength;
    float restitution;

    ParticleCable(float newMaxLength, float newRestitution, particle &p0, particle &p1)
    {
        maxLength = newMaxLength;
        restitution = newRestitution;
        particles[0] = &p0;
        particles[1] = &p1;
    }

    unsigned int addContact(vector<ParticleContact*> &contacts, unsigned int limit) const
    {
        float length = currentLength();

        if (length < maxLength)
        {
            return 0;
        }
        contacts.push_back(new ParticleContact(particles[0],particles[1]));

        vec3 normal = particles[1]->getPosition() - particles[0]->getPosition();
        normal.normalise();
        contacts.back()->contactNormal = normal;
        contacts.back()->penetration = length - maxLength;
        contacts.back()->restitution = restitution;

        return 1;
    }
};