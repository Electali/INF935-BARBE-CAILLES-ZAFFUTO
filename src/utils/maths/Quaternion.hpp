#pragma once

#include <iostream>
#include <cmath>
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
    Quaternion()
    {
        r = 0;
        i = 0;
        j = 0;
        k = 0;
    }

    Quaternion(float newR, float newI, float newJ, float newK)
    {
        r = newR;
        i = newI;
        j = newJ;
        k = newK;
    }

    // ~Quaternion();

    void Normalize()
    {
        float d = r * r + i * i + j * j + k * k;

        if (d == 0)
        {
            r = 1;
            return;
        }

        d = 1.0f / (sqrt(d));

        r *= d;
        i *= d;
        j *= d;
        k *= d;
    }

    //Quaternion operator*(const Quaternion &other);

    void operator*=(const Quaternion &multiplier)
    {
        Quaternion q = *this;

        r = q.r * multiplier.r - q.i * multiplier.i - q.j * multiplier.j - q.k * multiplier.k;
        i = q.r * multiplier.i + q.i * multiplier.r + q.j * multiplier.k - q.k * multiplier.j;
        j = q.r * multiplier.j + q.j * multiplier.r + q.k * multiplier.i - q.i * multiplier.k;
        k = q.r * multiplier.k + q.k * multiplier.r + q.i * multiplier.j - q.j * multiplier.i;
    }

    void RotateByVector(const vec3 &vector)
    {
        Quaternion q(0, vector.x, vector.y, vector.z);
        (*this) *= q;
    }

    void UpdateByAngularVelocity(const vec3 &rotation, float duration)
    {
        Quaternion q(0, rotation.x * duration, rotation.y * duration, rotation.z * duration);

        q *= *this;
        r += q.r * 0.5;
        i += q.i * 0.5;
        j += q.j * 0.5;
        k += q.k * 0.5;
    }


    void show()
    {
        std::cout << r << " + " << i << "*i + " << j << "*j + " << k << "*k" << std::endl;
    }
};
