#pragma once
#include "./maths/vector3.hpp"
#include "./maths/Quaternion.hpp"
#include "./maths/Matrix34.hpp"
#include "./maths/Matrix33.hpp"


class RigidBody
{
    public:

    // Physique de base comme les particules
    vec3 position;
    vec3 velocity;
    vec3 acceleration;
    float inverseMass;
    float damping;     

    //Orientation et rotation

    //orientation = position
    Quaternion orientation;

    //vitesse angulaire = vitesse
    vec3 rotationVelocity;
    vec3 rotationAcceleration;
    mat34 transformMatrix; 

    mat3 invInertiaMatrix;

    // forces = acceleration
    float angularDamping;
    vec3 forceAccu;
    vec3 torqueAccu;


    public:
    RigidBody(const vec3 p, const vec3 v, const float invm, const Quaternion orient,const vec3 rotv, float cote)
    {
        //physique linéaire
        position = p;
        velocity = v;
        acceleration = {};
        inverseMass = invm;
        damping = 0.99;  //hardcoder mais on peut le mettre en parametre par la suite;
        
        //physique rotationelle
        orientation = orient;
        rotationVelocity = rotv;
        rotationAcceleration = {};

        transformMatrix.setOrientationAndPosition(orientation, position);
        
        angularDammping = 0.99;
        forceAccu = {};
        torqueAccu = {};


        // Calcul de la matrice inverse d'inertie
        // pour le moment nous utiliserons des cubes
        invInertiaMatrix();
        float coeff = ((1 / inverseMass) / 6) * cote * cote;
        invInertiaMatrix[0] = coeff;
        invInertiaMatrix[4] = coeff;
        invInertiaMatrix[8] = coeff;
        invInertiaMatrix.inverse();

    };


    public:
    
    void AddForce(const vec3& force)
    {
        forceAccu += force;
    }

    void AddForceAtPoint(const vec3& force, const vec3& worldPoint)
    {
        vec3 pt = worldPoint;
        pt = pt - position;

        forceAccu += force;
        torqueAccu += prodVectExt(pt, force);
    }


    void AddForceAtBodyPoint(const vec3& force, const vec3& LocalPoint)
    {
        vec3 ptInWorld = LocalToWorld(localPoint); 
        AddForceAtPoint(ptInWorld);

    }

    void clearAccumulators()
    {
        rb.torqueAccu = {};
        rb.forceAccu = {};
    }
   
    vec3 WorldToLocal(const vec3& world)
    {
        return transformMatrix.transformInverseDirection(wolrd);
    }

    vec3 LocalToWorld(const vec3& local)
    {
        return transformMatrix.transformDirection(local);
    }
    
    void CalculateDerivedData()
    {
        orientation.Normalize();
        transformMatrix.setOrientationAndPosition(orientation, position);
        // Calcule la matrice de torseur inverse 

    }

    

    

    

};