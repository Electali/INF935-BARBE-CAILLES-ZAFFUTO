#pragma once

#include <iostream>
#include "math.h"
#include "particle.hpp"

class integrator
{
    public:

    integrator()
    {
    }

    ~integrator()
    {
    }

    void update(particle &p, float t)
    {
        vec3 vec = p.totalForce;
        vec *= p.inverseMass;
        p.acceleration = vec;

        updatePosition(p,t,false);
        updateVelocity(p,t);
    }

    private:

    void updatePosition(particle &p, float t, bool approx)
    {   

        vec3 m1 = multiplication(p.velocity,t);
        if (approx) p.position = addition(p.position,m1) ;

        else {
            vec3 m2 = multiplication(p.acceleration,0.5*t*t);
            vec3 a1 = addition(m1,m2);
            p.position = addition(p.position,a1);
        }
        
    }

    void updateVelocity(particle &p, float t)
    {   
        vec3 m1 = multiplication(p.velocity,p.damping);
        vec3 m2 = multiplication(p.acceleration,t);
        p.velocity = addition(m1,m2);
    }

};