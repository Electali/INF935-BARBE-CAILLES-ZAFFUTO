#pragma once

#include <iostream>
#include <math.h>

using namespace std;

class vector3D
{

public:
    float x;
    float y;
    float z;

    vector3D()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    vector3D(float i, float j, float k)
    {
        x = i;
        y = j;
        z = k;
    }

    void show()
    {
        cout << "(" << x << "," << y << "," << z << ")\n";
    }

    float norme()
    {
        float res = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
        return res;
    }

    float getX()
    {
        return x;
    }

    float getY()
    {
        return y;
    }

    float getZ()
    {
        return z;
    }

    friend vector3D addition(vector3D &v1, vector3D &v2)
    {
        return vector3D((v1.x + v2.x), (v1.y + v2.y), (v1.z + v2.z));
    }

    friend vector3D multiplication(vector3D &v, float lambda)
    {
        return vector3D(v.x * lambda, v.y * lambda, v.z * lambda);
    }

    friend float prodScal(vector3D &v1, vector3D &v2)
    {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    friend vector3D prodVect(vector3D &v1, vector3D &v2)
    {
        return vector3D((v1.y * v2.z - v1.z * v2.y), (v1.z * v2.x - v1.x * v2.z), (v1.x * v2.y - v1.y * v2.x));
    }
};
