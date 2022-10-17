#pragma once
#include "ParticleContact.hpp"

class ParticleContactGenerator
{
public:
// Take a pointer to an array of contact and the number of contacts left to be generated
    virtual unsigned int addContact(ParticleContact* contact, unsigned int limit) const = 0;
};