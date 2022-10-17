#pragma once

#include "../particle.hpp"
#include "ParticleContactGenerator.hpp"
#include "ParticleContact.hpp"

class ParticleLink : public ParticleContactGenerator
{
public:
    float length;

    float currentLength() const;

    unsigned int addContact(ParticleContact* contact, unsigned int limit) const = 0;
};

