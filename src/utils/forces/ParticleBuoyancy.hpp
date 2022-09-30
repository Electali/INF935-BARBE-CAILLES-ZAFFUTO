#pragma once
#include "ParticleForceGenerator.hpp";
#include "../utils/vector3D.hpp"
#include "../utils/integrator.hpp"

class ParticleBuoyancy : public ParticleForceGenerator
{
private:
    float maxDepth;
    float volume;

    float waterHeight;
    float liquidDensity;

public: 
    void UpdateForce(particle &p, float duration){
        float d =(p.getY() - waterHeight - maxDepth) / (2* maxDepth);

        if(d>=1){
            vector3D totalbuoy = vector3D(0,volume*liquidDensity,0);
             p.totalForce += totalbuoy;
        }
        else if (d<1 && d>0){
            vector3D totalbuoy = vector3D(0,d*volume*liquidDensity,0);
            p.totalForce += totalbuoy;
        }        
    }
};
