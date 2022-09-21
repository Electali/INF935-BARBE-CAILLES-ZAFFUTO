#pragma once

#include <iostream>
#include "math.h"
#include "particle.hpp"

class integrator
{
    public:

    void update(particle &p, float t)
    {
        updatePosition(p,t,false);
        updateVelocity(p,t);
    }

    private:

    void updatePosition(particle &p, float t, bool approx)
    {
        if (approx) p.position = addition(&p.position, &multiplication(&p.velocity,t)) ;

        else p.position = addition(&p.position, &addition(&multiplication(&p.velocity,t), &multiplication(&p.acceleration,0.5*t*t)));
    }

    void updateVelocity(particle &p, float t)
    {
        p.velocity = addition(&multiplication(&p.velocity,p.damping),&multiplication(&p.acceleration,t));
    }


};