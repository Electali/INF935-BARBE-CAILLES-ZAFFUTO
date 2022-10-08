#pragma once

#include "integrator.hpp"
#include "particle.hpp"
#include "./forces/ParticleForceRegistry.hpp"
#include <vector>

class Engine
{
public:
    integrator integr;

    using ParticleList = vector<particle *>;
    ParticleList particles;

    ParticleForceRegistry registry;

    Engine()
    {
        integr = integrator();
        registry = ParticleForceRegistry();
    }

    ~Engine()
    {
    }

    void addParticle(particle &p)
    {
        particles.push_back(&p);
    }

    void removeParticle(particle &p)
    {
        ParticleList::iterator i = particles.begin();

        for (; i != particles.end(); i++)
        {
            if (*i == &p)
            {
                particles.erase(i);
            }
        }
    }

    void Update(float dt)
    {
        registry.UpdateForce(dt);

        ParticleList::iterator i = particles.begin();
        for (; i != particles.end(); i++)
        {
            integr.update(**i, dt);
            (*i)->totalForce = 0;
        }
    }
};