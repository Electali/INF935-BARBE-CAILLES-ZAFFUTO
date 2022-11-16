#pragma once

#include "integrator.hpp"
#include "particle.hpp"
#include "./forces/ParticleForceRegistry.hpp"
#include "./contacts/ParticleContactGenerator.hpp"
#include "./contacts/ParticleContactResolver.hpp"
#include "./forces/RigidBodyForceRegistry.hpp"

#include <vector>

class Engine
{
public:
    /// Definitions ///
    using ParticleList = vector<particle *>;
    using RigidBodyList = vector<RigidBody *>;
    using ContactGenerators = vector<ParticleContactGenerator *>;
    

    integrator integr;

    ParticleList particles;

    RigidBodyList rigidbodies;

    unsigned int maxContacts = 0;

    ParticleForceRegistry particleRegistry;

    RigidBodyForceRegistry rigidbodyRegistry;

    ParticleContactResolver resolver;

    ContactGenerators contactGenerators;

    vector<ParticleContact *> contacts;

    Engine()
    {
        integr = integrator();
        particleRegistry = ParticleForceRegistry();
    }

    Engine(unsigned int newMaxContacts, unsigned int iterations)
    {
        maxContacts = newMaxContacts;
        particleRegistry = ParticleForceRegistry();
        resolver = ParticleContactResolver(iterations);
        contactGenerators = ContactGenerators();
    }

    ~Engine()
    {
        for (auto *contact : contacts)
        {
            delete contact;
        }
    }

    void addParticle(particle &p)
    {
        particles.push_back(&p);
    }

    void addRigidBody(RigidBody &rb)
    {
        rigidbodies.push_back(&rb);
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

    void removeRigidBody(RigidBody &rb)
    {
        RigidBodyList::iterator i = rigidbodies.begin();

        for (; i != rigidbodies.end(); i++)
        {
            if (*i == &rb)
            {
                rigidbodies.erase(i);
            }
        }
    }

    void addContact(ParticleContactGenerator &cont)
    {
        contactGenerators.push_back(&cont);
    }

    void Update(float dt)
    {

        particleRegistry.UpdateForce(dt);

        rigidbodyRegistry.UpdateForce(dt);

        // Boucle Integration Particules 
        for (int i=0; i < particles.size(); i++)
        {
            integr.update(*particles[i], dt);
            particles[i]->totalForce = 0;
        }

        // Boucle Integration RigidBodies
        for (int i=0; i < rigidbodies.size(); i++)
        {
            integr.integrate(*rigidbodies[i], dt);
            //(*rigidbodies[i]).velocity.show();
        }

        contacts.clear();

        unsigned int usedContacts = generateContacts();

        if (usedContacts)
        {
            resolver.setIterations(usedContacts * 2);
            resolver.resolveContacts(contacts, usedContacts, dt);
        }
    }

    unsigned int generateContacts()
    {
        unsigned int limit = maxContacts;

        for (int g = 0; g < contactGenerators.size(); g++)
        {
            unsigned int used = contactGenerators[g]->addContact(contacts, limit);
            limit -= used;
            if (limit <= 0)
                break;
        }

        return maxContacts - limit;
    }
};