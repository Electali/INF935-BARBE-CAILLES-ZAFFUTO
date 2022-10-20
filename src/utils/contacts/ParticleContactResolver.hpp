#pragma once
#include <limits>

#include "ParticleContact.hpp"

using namespace std;

class ParticleContactResolver
{
protected:
    unsigned int m_iterations;

public:
    ParticleContactResolver(){
    };

    ParticleContactResolver(unsigned int iterations)
    {
        m_iterations = iterations;
    }

    void setIterations(unsigned it)
    {
        m_iterations = it;
    }

    void resolveContacts(ParticleContact* contacts, unsigned int nbContacts, float duration)
    {
        unsigned int iterations = 0;
        while (iterations < m_iterations)
        {
            float max = numeric_limits<float>::max();
            unsigned int maxIndex = nbContacts;
            for(unsigned int i = 0; i < nbContacts; i++)
            {
                float sepVel = contacts[i].calculateSeparatingVelocity();
                if (sepVel < max && (sepVel < 0 || contacts[i].penetration > 0))
                {
                    max = sepVel;
                    maxIndex = i;
                }
            }
            if(maxIndex == nbContacts) break;
            contacts[maxIndex].resolve(duration);
            iterations ++;
        }
        
    }

};