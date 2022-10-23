#pragma once
#include "ParticleContact.hpp"

class ParticleContactGenerator
{
public:
// Take an array of contact and the number of contacts left to be generated
    virtual unsigned int addContact(vector<ParticleContact*> &contact, unsigned int limit) const = 0;
};