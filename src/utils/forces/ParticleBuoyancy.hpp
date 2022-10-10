#pragma once
#include "ParticleForceGenerator.hpp"
#include "../OpenGl/vector3.hpp"
#include "../integrator.hpp"

class ParticleBuoyancy : public ParticleForceGenerator
{
private:
    float m_maxDepth;
    float m_volume;

    float m_waterHeight;
    float m_liquidDensity;

public: 
    ParticleBuoyancy(float maxDepth, float volume, float waterHeight, float liquidDensity) {
        m_maxDepth = maxDepth;
        m_volume = volume;
        m_waterHeight = waterHeight;
        m_liquidDensity = liquidDensity;
    }

    void UpdateForce(particle &p, float duration){
        float d =(p.position.getY() - m_waterHeight - m_maxDepth) / (2* m_maxDepth);

        if(d>=1){
            vec3 totalbuoy = vec3(0,m_volume*m_liquidDensity,0);
             p.totalForce += totalbuoy;
        }
        else if (d<1 && d>0){
            vec3 totalbuoy = vec3(0,d*m_volume*m_liquidDensity,0);
            p.totalForce += totalbuoy;
        }        
    }
};
