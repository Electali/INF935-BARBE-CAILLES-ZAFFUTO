#pragma once
#include "./maths/vector3.hpp"
#include "./maths/Quaternion.hpp"
#include "./maths/Matrix34.hpp"
#include "./maths/Matrix33.hpp"


class RigidBody
{
    private:

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
    void AddForce(const vec3& force)
    {
        forceAccu += force;
    }


    private:

    void CalculateDerivedData()
    {
        orientation.Normalize();
        transformMatrix.setOrientationAndPosition(orientation,position);
    }


};