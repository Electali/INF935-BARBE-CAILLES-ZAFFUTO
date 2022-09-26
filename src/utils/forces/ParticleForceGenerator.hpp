#pragma once
#include "../particle.hpp"

class ParticleForceGenerator
{
public :
    virtual void UpdateForce(particle& p,float duration) = 0;  
};