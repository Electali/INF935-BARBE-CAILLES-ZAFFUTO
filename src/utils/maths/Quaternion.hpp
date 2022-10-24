#pragma once

#include <iostream>

#include "vector3.hpp"

class Quaternion
{

public:
    //////////////////
    //// Membres. ////
    //////////////////

    union
    {
        struct
        {
            float r, i, j, k; //=> Membres du Quaternion accessible comme des Coordonnées.
        };
        float data[4]; //=> Membres du Quaternion accessible comme un Tableau.
    };

public:
    Quaternion(/* args */);
    ~Quaternion();

    void Normalized();

    Quaternion operator*(const Quaternion &other);

    void RotateByVector(const vec3 &vector);

    void UpdateByAngularVelocity(const vec3 &rotation, float duration);

    void show()
    {
        std::cout << r << " + " << i << "*i + " << j << "*j + " << k << "*k" << std::endl;
    }
};
