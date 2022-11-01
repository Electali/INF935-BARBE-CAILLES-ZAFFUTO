#pragma once
#include "./maths/vector3.hpp"
#include "./maths/Quaternion.hpp"
#include "./maths/Matrix34.hpp"


class RigidBody
{
    private:

    // Physique de base comme les particules
    vec3 position;
    vec3 velocity;
    float inverseMass;
    float damping;     

    //Orientation et rotation
    Quaternion orientation;
    vec3 rotationVelocity;
    Mat34 transformMatrix; 

    public:

    void Integrate(float duration)
    {

    }

    private:
    void CalculateDerivedData()
    {
        
    }
};