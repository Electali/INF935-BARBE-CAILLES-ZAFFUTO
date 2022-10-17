#pragma once

class ParticuleContact
{

public: 

    //particule[1] peut être null
    particule* particles[2];

    //dans [0,1]
    float restitution;

    // distance de penetration
    float penetration;

    //vecteur de la normal du contact
    vec3 contactNormal;


protected:

    void resolve(float duration)
    {
        resolveVelocity(duration);
        resolveInterpenetration(duration);
    }

    float calculateSeparatingVelocity() const
    {
        vec3 relativeVelocity = particles[0]->getVelocity();
        if(particles[1]) relativeVelocity -= particles[1]->getVelocity();
        return relativeVelocity.prodScal(contactNormal);

    }

    void resolveVelocity(float duration)
    {
        float separatingVelocity = calculateSeparatingVelocity();

        if(separatingVelocity > 0) return;

        float newSepVelocity = -separatingVelocity * restitution;   
        float deltaVelocity = newSepVelocity - separatingVelocity;

        float totalInverseMass = particles[0]->getInverseMass();
        if(particle[1]) totalInverseMass += particles[1]->getInverseMass()

        if(totalInverseMass <= 0) return ; // Les deux ont une masse infinie donc rien ne se passe.

        float impulse = deltaVelocity /totalInverseMass;

        vec3 impulsePerMass = contactNormal * impulse;

        particle[0]->velocity += (impulsePerMass *= particle[0]->getInvMass);   

        if(particle[1])
        {    
            particle[1]->velocity += (impulsePerMass *= -(particle[1]->getInvMass));
        }

    }

    void  resolveInterpenetration(float duration)
    {
        if(penetration<=0) return; // skip si pas de penetration

        float totalInvMass = particle[0]->getInvMass;
        if(particle[1]) totalInvMass += particle[1]->getInvMass;

        if(totalInvMass<=0) return; // Masse(s) infinie(s) donc ne fait rien.

        vec3 movePerMass = multiplication(contactNormal,(penetration/totalInvMass));

        // Calcul des mouvements
        vec3 particleMovement[2];
        particleMovement[0] = multiplication(movePerMass,particle[0]->getInvMass);  
        if(particle[1]){
            particleMovement[1] = = multiplication(movePerMass,particle[1]->getInvMass);  
        }

        //Application des mouvements
        particle[0]->position += particleMovement[0];
        if(particle[1]) particle[1]->position += particleMovement[1];

    }



}