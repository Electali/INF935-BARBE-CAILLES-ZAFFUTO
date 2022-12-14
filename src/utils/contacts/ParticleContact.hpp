#pragma once

#include "../particle.hpp"
#include "../maths/Vector3.hpp"

using namespace std;


class ParticleContact
{

public:
    // particule[1] peut être null
    particle *particles[2];

    // dans [0,1]
    float restitution;

    // distance de penetration
    float penetration;

    // vecteur de la normal du contact
    vec3 contactNormal;

~ParticleContact()
{
    for (auto* particle: particles)
        {
            delete particle;
        }
}

public:
    ParticleContact(particle* p1, particle* p2) {
        particles[0] = p1;
        particles[1] = p2;
    }

    void resolve(float duration)
    {
        resolveVelocity(duration);
        resolveInterpenetration(duration);
    }

    float calculateSeparatingVelocity() const
    {
        vec3 relativeVelocity = particles[0]->getVelocity();
        if (particles[1])
            relativeVelocity -= particles[1]->getVelocity();
        return relativeVelocity.prodScal(contactNormal);
    }

    void resolveVelocity(float duration)
    {
        float separatingVelocity = calculateSeparatingVelocity();
        
        if (separatingVelocity > 0)
            return;

        float newSepVelocity = -separatingVelocity * restitution;

        vec3 accCausedVelocity = particles[0]->acceleration;
        if(particles[1] ) accCausedVelocity -= particles[1]->acceleration;
        
        accCausedVelocity*=duration;
        float  accCausedSepVelocity = prodScalExt(contactNormal,accCausedVelocity);

        if(accCausedSepVelocity < 0)
        {
            newSepVelocity += (accCausedSepVelocity*=restitution);

            if(newSepVelocity < 0) newSepVelocity = 0;
        }

        float deltaVelocity = newSepVelocity - separatingVelocity;

        float totalInverseMass = particles[0]->getInvMass();

        
        if (particles[1])
            totalInverseMass += particles[1]->getInvMass();

        
        if (totalInverseMass <= 0)
            return; // Les deux ont une masse infinie donc rien ne se passe.

        float impulse = deltaVelocity / totalInverseMass;   
          
        vec3 impulsePerMass = multiplication(contactNormal, impulse);

        float invmass = particles[0]->getInvMass();
        vec3 vect = multiplication(impulsePerMass,invmass );
     
        particles[0]->velocity += vect;

        if (particles[1])
        {
            invmass = particles[1]->getInvMass();
            vect = multiplication(impulsePerMass, -invmass);
            particles[1]->velocity += vect;
        }
        
    }

    void resolveInterpenetration(float duration)
    {
        if (penetration <= 0)
            return; // skip si pas de penetration

        float totalInvMass = particles[0]->getInvMass();
        if (particles[1])
            totalInvMass += particles[1]->getInvMass();

        if (totalInvMass <= 0)
            return; // Masse(s) infinie(s) donc ne fait rien.

        vec3 movePerMass = multiplication(contactNormal, (penetration / totalInvMass));
        // Calcul des mouvements
        vec3 particleMovement[2];
        particleMovement[0] = multiplication(movePerMass, particles[0]->getInvMass());

        if (particles[1])
        {
            particleMovement[1] = multiplication(movePerMass, -particles[1]->getInvMass());
        }

        // Application des mouvements
        particles[0]->position += particleMovement[0];
        if (particles[1])
            particles[1]->position += particleMovement[1];

    }


};