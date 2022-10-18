#pragma once

#include <vector>

#include "particle.hpp"
#include "integrator.hpp"
#include "utils/contacts/ParticleContactGenerator.hpp"
#include "utils/contacts/ParticleContactResolver.hpp"
#include "utils/forces/ParticleForceRegistry.hpp"

class particleWorld
{
public:
    /// Definitions ///

    using ParticleList = vector<particle *>;
    using ContactGenerators = vector<ParticleContactGenerator *>;

public:
    ParticleList particles;

    unsigned int maxContacts;

    ParticleForceRegistry registry;

    ParticleContactResolver resolver;

    ContactGenerators contactGenerators;

    ParticleContact *contacts;

public:
    particleWorld(unsigned int newMaxContacts, unsigned int iterations = 0) {
        maxContacts = newMaxContacts;
        registry = ParticleForceRegistry();
        resolver = ParticleContactResolver(iterations);
        contactGenerators = ContactGenerators();
    }

public:
    unsigned generateContacts()
    {
        unsigned limit = maxContacts;
        ParticleContact *nextContact = contacts;

        for (ContactGenerators::iterator g = contactGenerators.begin(); g != contactGenerators.end(); g++)
        {
            unsigned used = (*g)->addContact(nextContact, limit);
            limit -= used;
            nextContact += used;

            if (limit <= 0)
                break;
        }

        return maxContacts - limit;
    }

    void integrate(float duration)
    {
        integrator integr = integrator();
        for (ParticleList::iterator p = particles.begin(); p != particles.end(); p++)
        {
            integr.update(**p, duration);
            //(*p)->integrate(duration);
        }
    }

    void runPhysics(float duration)
    {
        registry.UpdateForce(duration);

        integrate(duration);

        unsigned usedContacts = generateContacts();

        if (usedContacts)
        {
            resolver.setIterations(usedContacts * 2);
            resolver.resolveContacts(contacts, usedContacts, duration);
        }
    }

    /*
    void startFrame()
    {
        vec3 zero = (0, 0, 0);
        for (ParticleList::iterator p = particles.begin(); p != particles.end(); p++)
        {
            (*p)->totalForce = zero;
        }
    }
    */
};