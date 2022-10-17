#pragma once

#include "../particle.hpp"
#include "ParticleContactGenerator.hpp"
#include "ParticleContact.hpp"

class ParticleRod : public ParticleLink
{
public:
    float length;

    unsigned int addContact(ParticleContact* contact, unsigned int limit) const;
};

