#pragma once

#include <iostream>
#include <math.h>

using namespace std;

class vector3D
{

public:

    union
    {

        struct
        {
            float x, y, z;   
        };

        float data[3]; 
    };
    

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

    ~vector3D()  // Destructeur
    {
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

    void show()
    {
        cout << "(" << x << "," << y << "," << z << ")\n";
    }

    // NORMALISATION

     float normeCarre()
    {
        float res = pow(x, 2) + pow(y, 2) + pow(z, 2);
        return res;
    }

    float norme()
    {
        float res = sqrt(this->normeCarre());
        return res;
    }

    void normalise()
    {
        float norme = this->norme();
        if (norme > 0){
            *this *= 1/norme;
        }

    }

    friend vector3D normalisation(vector3D v)
    {
        vector3D res = vector3D(v.x,v.y,v.z);
        res.normalise();
        return res ;
    }


    // INVERSION 

    void inversion()
    {
        x = -x;
        y = -y;
        z = -z;
    }

    vector3D inverse()
    {
        return vector3D(-x,-y,-z);
    }


    // ADDITION

    friend vector3D addition(vector3D &v1, vector3D &v2)
    {
        return vector3D((v1.x + v2.x), (v1.y + v2.y), (v1.z + v2.z));
    }

    void operator+=(vector3D &v){
        x += v.x;
        y += v.y;
        z += v.z;
    }

    // SOUSTRACTION

    friend vector3D soustraction(vector3D &v1, vector3D &v2)
    {
        return vector3D((v1.x - v2.x), (v1.y - v2.y), (v1.z - v2.z));
    }

    void operator-=(vector3D &v){
        x -= v.x;
        y -= v.y;
        z -= v.z;
    }


    // DILATATION

    friend vector3D multiplication(vector3D &v, float lambda)
    {
        return vector3D(v.x * lambda, v.y * lambda, v.z * lambda);
    }

    void operator*=(float a){
        x *= a;
        y *= a;
        z *= a;
    }


    // PRODUITS DE VECTEURS 

    float prodScal(vector3D v)
    {
        return  x * v.x + y * v.y + z * v.z;
    }

    friend float prodScalExt(vector3D &v1, vector3D &v2)
    {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    void prodVect(vector3D v)
    {
        float nx = y * v.z - z * v.y;
        float ny = z * v.x - x * v.z;
        float nz = x * v.y - y * v.x;
        
        x = nx;
        y = ny;
        z = nz;
    }

    friend vector3D prodVectExt(vector3D &v1, vector3D &v2)
    {
        return vector3D(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
    }
    
    // BASE ORTHONORME

    friend void baseOrtho(vector3D &v1, vector3D &v2, vector3D &v3)
    {
        v1.normalise();
        v3 = prodVectExt(v1,v2);

        if(v3.normeCarre() == 0.0) return ; // v1 et v2 paralleles 
        v3.normalise();
        v2 = prodVectExt(v3,v1);
        return ;
    }



};
