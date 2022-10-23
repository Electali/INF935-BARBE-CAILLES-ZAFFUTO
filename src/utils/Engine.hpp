#pragma once

#include "integrator.hpp"
#include "particle.hpp"
#include "./forces/ParticleForceRegistry.hpp"
#include "./contacts/ParticleContactGenerator.hpp"
#include "./contacts/ParticleContactResolver.hpp"

#include <vector>

class Engine
{
public:
    /// Definitions ///
    using ParticleList = vector<particle *>;
    using ContactGenerators = vector<ParticleContactGenerator *>;

    integrator integr;

    ParticleList particles;

    unsigned int maxContacts;

    ParticleForceRegistry registry;

    ParticleContactResolver resolver;

    ContactGenerators contactGenerators;

    ParticleContact *contacts;

    Engine()
    {
        integr = integrator();
        registry = ParticleForceRegistry();
    }

    Engine(unsigned int newMaxContacts, unsigned int iterations)
    {
        maxContacts = newMaxContacts;
        registry = ParticleForceRegistry();
        resolver = ParticleContactResolver(iterations);
        contactGenerators = ContactGenerators();
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

    void addContact(ParticleContactGenerator &cont)
    {
        contactGenerators.push_back(&cont);
    }


    void Update(float dt)
    {
        registry.UpdateForce(dt);

       
        for (int i; i < particles.size(); i++)
        {
            integr.update(*particles[i], dt);
            particles[i]->totalForce = 0;
        }
        unsigned usedContacts = generateContacts();
        cout << "Le nombre de contacts generé est :" << usedContacts << "\n";

        if (usedContacts)
        {
            resolver.setIterations(usedContacts * 2 );
            resolver.resolveContacts(contacts, usedContacts, dt);
        }
    }

    unsigned int generateContacts()
    {
        unsigned int limit = maxContacts;
        ParticleContact *nextContact = contacts;

        
        for (int g = 0; g < contactGenerators.size(); g++)
        {
            unsigned int used = contactGenerators[g]->addContact(nextContact, limit);
            limit -= used;
            nextContact += used;
        
            if (limit <= 0)
                break;
             
        }

        return maxContacts - limit;
    }

};