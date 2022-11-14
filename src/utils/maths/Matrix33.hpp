#pragma once

#include "vector3.hpp"



class Matrix33 {

public :
    float data[9];

public : 
    /// Constructeur

    Matrix33()
    {
        for (int i = 0; i < 9; i++)
        {
            data[i] = 0;
        }
    }

    Matrix33(const vec3& l1, const vec3& l2, const vec3& l3)
    {
        data[0] = l1.x;
        data[1] = l1.y;
        data[2] = l1.z;
        data[3] = l2.x;
        data[4] = l2.y;
        data[5] = l2.z;
        data[6] = l3.x;
        data[7] = l3.y;
        data[8] = l3.z;
    }

public :

    /// <summary>
    /// Sert à récupérer une ligne de la matrice sous forme de vec3, par défaut il renvoit la première.
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    float operator[](size_t index) const
    {
        return data[index];
    };

public : 

    Matrix33 operator*(const Matrix33& other) const
    {
        Matrix33 result;
        result.data[0] = data[0] * other[0] + data[1] * other[3] + data[2] * other[6];
        result.data[1] = data[0] * other[1] + data[1] * other[4] + data[2] * other[7];
        result.data[2] = data[0] * other[2] + data[1] * other[5] + data[2] * other[8];

        result.data[3] = data[3] * other[0] + data[4] * other[3] + data[5] * other[6];
        result.data[4] = data[3] * other[1] + data[4] * other[4] + data[5] * other[7];
        result.data[5] = data[3] * other[2] + data[4] * other[5] + data[5] * other[8];

        result.data[6] = data[6] * other[0] + data[7] * other[3] + data[8] * other[6];
        result.data[7] = data[6] * other[1] + data[7] * other[4] + data[8] * other[7];
        result.data[8] = data[6] * other[2] + data[7] * other[5] + data[8] * other[8];
        
        return result;
       
    };

    vec3 operator*(const vec3& vector) const
    {
        vec3 result = { data[0] * vector.x + data[1] * vector.y + data[2] * vector.z,
                        data[3] * vector.x + data[4] * vector.y + data[5] * vector.z,
                        data[6] * vector.x + data[7] * vector.y + data[8] * vector.z
        };
        return result;
    };

    Matrix33 operator*(const float& coeff) const
    {
        Matrix33 result;
        for (int i = 0; i < 9; i++) {
            result.data[i] = coeff * data[i];
        }
        return result;
    };

    Matrix33 inverse()
    {
        float Det = data[0] * data[4] * data[8] +
                    data[2] * data[3] * data[7] +
                    data[1] * data[5] * data[6] -
                    data[0] * data[5] * data[7] -
                    data[2] * data[4] * data[6] -
                    data[1] * data[3] * data[8];
        float invDet = 1/ Det;

        Matrix33 inv;
        inv.data[0] = data[4] * data[8] - data[5] * data[7];
        inv.data[1] = data[2] * data[7] - data[1] * data[8];
        inv.data[2] = data[1] * data[5] - data[2] * data[4];

        inv.data[3] = data[5] * data[6] - data[3] * data[8];
        inv.data[4] = data[0] * data[8] - data[2] * data[6];
        inv.data[5] = data[2] * data[3] - data[5] * data[0];

        inv.data[6] = data[3] * data[7] - data[4] * data[6];
        inv.data[7] = data[1] * data[6] - data[0] * data[7];
        inv.data[8] = data[4] * data[0] - data[1] * data[3];


        return inv * invDet;
    };

    Matrix33 transpose()
    {
        Matrix33 transp;

        transp.data[0] = data[0];
        transp.data[1] = data[3];
        transp.data[2] = data[6];

        transp.data[3] = data[1];
        transp.data[4] = data[4];
        transp.data[5] = data[7];

        transp.data[6] = data[2];
        transp.data[7] = data[5];
        transp.data[8] = data[8];

        return transp;
    };

    void show()
    {
        for (int i = 0; i < 3; i++)
        {
            std::cout << data[0 + 3*i] << " , " << data[1 + 3*i] << " , " << data[2 + 3*i] << std::endl;
        }
    }

};

using mat3 = Matrix33;
