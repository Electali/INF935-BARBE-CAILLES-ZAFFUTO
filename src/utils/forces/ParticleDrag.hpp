#pragma once

#include "ParticleForceGenerator.hpp"
#include "../particle.hpp"
#include "../utils/vector3D.hpp"

class ParticleDrag : public ParticleForceGenerator
{
    private:
        // drag coefficients
        float k1;
        float k2;

    public:
        //apply simplified drag based on particle's velocity
        void UpdateForce(particle &p, float duration) {
            vector3D op1 = p.velocity;
            op1.normalise();

            vector3D velocity = p.velocity;
            float magnitude = velocity.norme();

            float op2  = k1*magnitude + k2*magnitude;

            vector3D forceDrag = multiplication(op1, op2);
            forceDrag.inversion();

            p.totalForce += forceDrag;
        }
};