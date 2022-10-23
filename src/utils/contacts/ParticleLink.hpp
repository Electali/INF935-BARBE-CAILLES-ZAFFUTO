#pragma once

#include "../particle.hpp"
#include "ParticleContactGenerator.hpp"
#include "ParticleContact.hpp"

class ParticleLink : public ParticleContactGenerator
{
public:
    particle* particles[2];
    
    float currentLength() const {
        vec3 relativePos = particles[0]->getPosition() - particles[1]->getPosition();
        return relativePos.norme();
    }

    unsigned int addContact(vector<ParticleContact*> &contact, unsigned int limit) const;
};