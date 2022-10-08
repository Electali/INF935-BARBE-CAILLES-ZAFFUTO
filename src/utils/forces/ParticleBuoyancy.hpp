#pragma once
#include "ParticleForceGenerator.hpp"
#include "../OpenGl/vector3.hpp"
#include "../integrator.hpp"

class ParticleBuoyancy : public ParticleForceGenerator
{
private:
    float maxDepth;
    float volume;

    float waterHeight;
    float liquidDensity;

public: 
    void UpdateForce(particle &p, float duration){
        float d =(p.position.getY() - waterHeight - maxDepth) / (2* maxDepth);

        if(d>=1){
            vec3 totalbuoy = vec3(0,volume*liquidDensity,0);
             p.totalForce += totalbuoy;
        }
        else if (d<1 && d>0){
            vec3 totalbuoy = vec3(0,d*volume*liquidDensity,0);
            p.totalForce += totalbuoy;
        }        
    }
};
