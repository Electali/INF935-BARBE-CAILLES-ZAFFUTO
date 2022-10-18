#pragma once
#include <vector>

class ParticleWorld
{
public:

    /// Definitions ///

    using ParticleList = vector<particle *>;
    using ContactGenerators = vector<ParticleContactGenerators *>;

protected: 
    ParticleList particles;
    
public: 

    unsigned maxContacts;
    
    ParticleForceRegistry registry;

    ParticleContactResolver resolver;

    ContactGenerators contactGenerators;

    ParticleContact *contacts;

public: 
    ParticleWorld(unsigned maxContacts, unsigned iterations = 0);

public:

    unsigned generateContacts()
    {
        unsigned limit = maxContacts;
        ParticleContact *nextContact = contacts;

        for(ContactGenerators::iterator g = contactGenerators.begin();g != contactGenerators.end();g++)
        {
            unsigned used = (*g)->addContact(nextContact,limit);
            limit -= used;
            nextContact+=used;

            if (limit <= 0) break;
        }

        return maxContact - limit;

    }

    void integrate(float duration)
    {
        for(particles::iterator p = particles.begin(); p!= particles.end(); p++)
        {
            p->integrate(duration);
        }
    }


    void runPhysics(float duration)
    {
        registry.updateForces(duration);
    
        integrate(duration);

        unsigned usedContacts = generateContacts();

        if(usedContacts)
        {
            resolver.setIterations(usedContacts*2);
            resolver.resolveContacts(contacts,usedContacts,duration)
        }
    }

    void startFrame()
    {
        vec3 zero = (0,0,0);
        for(particles::iterator p = particles.begin(); p!= particles.end(); p++)
        {
            p->totalForce = zero;
        }
    }

};