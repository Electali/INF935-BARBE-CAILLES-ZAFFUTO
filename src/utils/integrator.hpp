#pragma once

#include <iostream>
#include "math.h"
#include "particle.hpp"
#include "RigidBody.hpp"



class integrator
{
    public:

    integrator()
    {
    }

    ~integrator()
    {
    }

    //////////////////
    /// PARTICULES ///
    //////////////////

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


    /////////////////
    /// RIGIDBODY ///
    /////////////////
    
    public:

    void integrate(RigidBody& rb, float t)   // Equivalent au update des particules
    {

        // 1 Mettre � jour la position
        updatePositionRigidBody(rb, t);

        // 2 Mettre a jour l'orientation
        updateAngularPositionRigidBody(rb, t);


        // 3 Calculer les valeurs derivees
        rb.CalculateDerivedData();

        // 4 Calculer l�acc�l�ration lin�aire
        updateAccelerationRigidBody(rb,t);

        // 5 Calculer l�acc�l�ration angulaire
        updateangularaccelerationRigidBody(rb, t);
       
        // 6 Mettre � jour la v�locit� lin�aire
        updateVelocityRidBody(rb, t);

        // 7 Mettre � jour la v�locit� angulaire
        updateAngularVelocityRidBody(rb, t);
       
        // 8 Clear les accumulateurs 
        rb.clearAccumulators();
        
    }

    private:
    //1 
    void updatePositionRigidBody(RigidBody& rb, float t) 
    {
        vec3 m1 = multiplication(rb.velocity, t);

        rb.position = rb.position + m1;
        rb.position.show();
    }
    
    //2
    void updateAngularPositionRigidBody(RigidBody& rb, float t)
    {
        rb.orientation.UpdateByAngularVelocity(rb.rotationVelocity,t);
    }

    //4 
    void updateAccelerationRigidBody(RigidBody& rb, float t)
    {
        rb.acceleration = multiplication(rb.forceAccu, rb.inverseMass);
    }
   
    //5 
    void updateangularaccelerationRigidBody(RigidBody& rb, float t)
    {
        rb.rotationAcceleration = rb.invInertiaMatrix * rb.torqueAccu;
    }


    //6
    void updateVelocityRidBody(RigidBody& rb, float t)
    {
        vec3 m1 = multiplication(rb.velocity,rb.damping);
        vec3 m2 = multiplication(rb.acceleration, t);
        rb.velocity = m1 + m2;
    }

    //7
    void updateAngularVelocityRidBody(RigidBody& rb, float t)
    {
        vec3 m1 = multiplication(rb.rotationVelocity, rb.angularDamping);
        vec3 m2 = multiplication(rb.rotationAcceleration, t);
        rb.rotationVelocity = m1 + m2;
    }

};