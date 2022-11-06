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
    
    void intigrate(Rigidbody& rb, float t)   // Equivalent au update des particules
    {

        // 1 Mettre à jour la position
        updatePositionRigidBody(rb, t, false);

        // 2 Mettre a jour l'orientation
        updateAngularPositionRigidBody(rb, t);

        // 3 Calculer les valeurs dérivées
        rb.CalculateDerivedData();

        // 4 Calculer l’accélération linéaire
        rb.acceleration = multiplication(rb.forceAccu, rb.inverseMass);

        // 5 Calculer l’accélération angulaire
        updateangularaccelerationRigidBody(rb, t);
       
        // 6 Mettre à jour la vélocité linéaire
        updateVelocityRidBody(rb, t);

        // 7 Mettre à jour la vélocité angulaire
        updateAngularVelocityRidBody(rb, t);
        // 8 Clear les accumulateurs 
        rb.torqueAccu = {};
        rb.forceAccu = {};
        
    }

    //1 
    void updatePositionRigidBody(RigidBody& rb, float t, bool approx) 
    {
        vec3 m1 = multiplication(rb.velocity, t);

        if (approx) rb.position = rb.position + m1;

        else {
            vec3 m2 = multiplication(rb.acceleration, 0.5 * t * t);
            vec3 a1 = m1 + m2:
            rb.position = rb.position + a1;
        }
    }
        
    
    //2
    void updateAngularPositionRigidBody(RigidBody& rb, float t)
    {
        Quaternion old = rb.orientation;
        rb.orientation.RotateByVector(rbrotationVelocity * (t / 2));
        rb.oriention = old * rb.orientation;

    }



   
    //5 
    void updateangularaccelerationRigidBody(RigidBody& rb, float t)
    {
        /// TO DO : Calculer lae changement de base 
        rb.rotationAcceleration = rb.invInertiaMatrix * rb.torqueAccu;
    }


    //6
    void updateVelocityRidBody(RigidBody& rb, float t)
    {
        vec3 m1 = multiplication(rb.velocity,pow(rb.damping,t));
        vec3 m2 = multiplication(rb.acceleration, t);
        rb.velocity = m1 + m2;
    }

    //7
    void updateAngularVelocityRidBody(RigidBody& rb, float t)
    {
        vec3 m1 = multiplication(rb.rotationVelocity, pow(rb.angularDamping,t));
        vec3 m2 = multiplication(rb.rotationAcceleration, t);
        rb.velocity = m1 + m2;
    }

    
    

};