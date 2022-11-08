#pragma once
#include "./vector3.hpp"
#include "./Quaternion.hpp"
#include "./Matrix33.hpp"


/**
 * @brief Classe Matrice de taille 3 par 4,
 */

class Matrix34
{
    public:
    //////////////////
    //// Membres. ////
    //////////////////
    float data[12]; //=> Membres de la Matrice accessible comme un Tableau.
    


    public:
    ////////////////////////
    //// Constructeurs. ////
    ////////////////////////

    Matrix34()
    {
    }
    /**
     * @brief Constructeur d'une Matrice 3x4 par copie d'une matrice 3x4.
     */

    Matrix34(const mat3& oth, const vec3& vect)
    {

        data[0] = oth[0];
        data[1] = oth[1];
        data[2] = oth[2];
        data[3] = vect.x;
        data[4] = oth[3];
        data[5] = oth[4];
        data[6] = oth[5];
        data[7] = vect.y;
        data[8] = oth[6];
        data[9] = oth[7];
        data[10] = oth[8];
        data[11] = vect.z;
     }
        
  

    /**
     * @brief Récupère un élément de la Matrice.
     *
     * @param index position de l'élément à récuperer dans la Matrice.
     * @return élément numéro index.
     */
    float operator[](size_t index) const
    {
        return data[index];
    };


    Matrix33 getMatrix() const
    {
        vec3 L1 = { data[0], data[1], data[2] };
        vec3 L2 = { data[4], data[5], data[6] };
        vec3 L3 = { data[8], data[9], data[10] };
        Matrix33 result(L1,L2,L3);
        return result;
    }

    vec3 getVelocityVector() const
    {
        vec3 result = { data[3],data[7],data[11] };
        return result;
    }

    public:
    /////////////////////
    //// Operations. ////
    /////////////////////

    Matrix34 operator*(const Matrix34& oth) const
    {
        Matrix34 result;
        result.data[0] = oth[0]*data[0] + oth[4]*data[1] + oth[8]*data[2];
        result.data[1] = oth[1]*data[0] + oth[5]*data[1] + oth[9]*data[2];
        result.data[2] = oth[2]*data[0] + oth[6]*data[1] + oth[10]*data[2];
        result.data[3] = oth[3]*data[0] + oth[7]*data[1] + oth[11]*data[2] + data[3];
        result.data[4] = oth[0]*data[4] + oth[4]*data[5] + oth[8]*data[6];
        result.data[5] = oth[1]*data[4] + oth[5]*data[5] + oth[9]*data[6];
        result.data[6] = oth[2]*data[4] + oth[6]*data[5] + oth[10]*data[6];
        result.data[7] = oth[3]*data[4] + oth[7]*data[5] + oth[11]*data[6] + data[7];
        result.data[8] = oth[0]*data[8] + oth[4]*data[9] + oth[8]*data[10];
        result.data[9] = oth[1]*data[8] + oth[5]*data[9] + oth[9]*data[10];
        result.data[10] = oth[2]*data[8] + oth[6]*data[9] + oth[10]*data[10];
        result.data[11] = oth[3]*data[8] + oth[7]*data[9] + oth[11]*data[10] + data[11];
        return result;
    }

    vec3 operator*(const vec3& oth) const
    {
        vec3 result = { oth.x* data[0] + oth.y * data[1] + oth.z * data[2] + data[3],
                        oth.x* data[4] + oth.y * data[5] + oth.z * data[6] + data[7],
                        oth.x* data[8] + oth.y * data[9] + oth.z * data[10] + data[11]
                      };
        return result; 
        
    }

 
    Matrix34 inverse() const
    {
        Matrix33 mat = getMatrix();
        vec3 vec = getVelocityVector();
        Matrix34 result(mat.transpose(), multiplication(vec, -1)); // Renvoie la matrice composé de la matrice 3x3 inverse et de l'opposé du vecteur.  
        return result;
    }
 

    /// @brief 
    /// @param q quaternion de la rotation. 
    /// @param p position à set.
    void setOrientationAndPosition(Quaternion& q, vec3& p)
    {
        // Position
        data[3] = p.x;
        data[7] = p.y;
        data[11] = p.z;

        // Orientation
        data[0] = 1 - (2*q.j*q.j + 2*q.k*q.k) ;
        data[1] = 2*q.i*q.j + 2*q.k*q.r ;
        data[2] = 2*q.i*q.k - 2*q.j*q.r ;
        data[4] = 2*q.i*q.j - 2*q.k*q.r ;
        data[5] = 1 - (2*q.i*q.i + 2*q.k*q.k) ;
        data[6] = 2*q.j*q.k + 2*q.i*q.r ;
        data[8] = 2*q.i*q.k + 2*q.j*q.r ;
        data[9] = 2*q.j*q.k - 2*q.i*q.r ;
        data[10] = 1 - (2*q.i*q.i + 2*q.j*q.j) ;

    };


    /// @brief Calcule le changement de position 
    /// @param vect 
    /// @return 
    vec3 transformPosition(const vec3& vect)
    {
        vec3 temp = vect;
        tmp.x -= data[3];
        tmp.y -= data[7];
        tmp.z -= data[11];
        
        return vec3( temp.x * data[0] + temp.y * data[4] + temp.z * data[8],
                     temp.x * data[1] + temp.y * data[5] + temp.z * data[9],
                     temp.x * data[2] + temp.y * data[6] + temp.z * data[10])
    };

    /// @brief Calcule la nouvelle direction sans toucher à la partie translation
    /// @param vect 
    /// @return 
    vec3 transformDirection(const vec3 vect)
    {
        
        vec3 result = {
            vect.x * data[0] + vect.y * data[1] + vect.z * data[2],
            vect.x * data[4] + vect.y * data[5] + vect.z * data[6], 
            vect.x * data[8] + vect.y * data[9] + vect.z * data[10],   
        };
        return result;
    };


    void show()
    {
        for (int i = 0; i < 3; i++)
        {
            std::cout << data[0 + 4 * i] << " , " << data[1 + 4 * i] << " , " << data[2 + 4 * i] << " , " << data[3 + 4 * i] << std::endl;
        }
    }
};

using mat34 = Matrix34;

