#pragma once

#include "../particle.hpp"
#include "ParticleContactGenerator.hpp"
#include "ParticleContact.hpp"

class ParticleLink : public ParticleContactGenerator
{
private:
    float length;

public:
    float currentLength() const;

    unsigned int addContact(ParticleContact* contact, unsigned int limit) const = 0;
};

