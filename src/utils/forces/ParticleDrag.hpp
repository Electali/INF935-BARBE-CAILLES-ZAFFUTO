#pragma once

#include "ParticleForceGenerator.hpp"
#include "../particle.hpp"
#include "../OpenGl/vector3.hpp"

class ParticleDrag : public ParticleForceGenerator
{
    private:
        // drag coefficients
        float k1;
        float k2;

    public:

        ParticleDrag(float a1=0,float a2=0)
        {
            k1 = a1;
            k2 = a2;
        }

        //apply simplified drag based on particle's velocity
        void UpdateForce(particle &p, float duration) {
            vec3 op1 = p.velocity;
            op1.normalise();

            vec3 velocity = p.velocity;
            float magnitude = velocity.norme();

            float op2  = k1*magnitude + k2*magnitude;

            vec3 forceDrag = multiplication(op1, op2);
            forceDrag.inversion();

            p.totalForce += forceDrag;
        }
};