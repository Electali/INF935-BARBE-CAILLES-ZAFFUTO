#pragma once
#include "./maths/vector3.hpp"
#include "./maths/Quaternion.hpp"
#include "./maths/Matrix33.hpp"


/**
 * @brief Classe Matrice de taille 3 par 4,
 */
template <typename T>
class Matrix34T
{
    public:
    //////////////////
    //// Membres. ////
    //////////////////

    union
    {
        struct      //=> Representation par les 4 lignes
        {                           
            Vector4T<T> x, y, z, w;
        };

        struct //=> Representation d'une matrice comprenant une matrice 3*3,un vect3 et une ligne {0,0,0,1};
        {        
            Matrix33T<T> mat;
            Vector3T<T> vec;
        };

        Vector4T<T> data2[4]; //=> Membres de la Matrice accessible comme des Lignes de Vecteurs.
        T data[12]; //=> Membres de la Matrice accessible comme un Tableau.
    };


    public:
    ////////////////////////
    //// Constructeurs. ////
    ////////////////////////

    /**
     * @brief Constructeur d'une Matrice 3x4 par copie d'une matrice 3x4.
     */
    Matrix34T(const Matrix34T &oth) : data2{
                                          oth.data[0],
                                          oth.data[1],
                                          oth.data[2],
                                          }
    {
    }

    /**
     * @brief Constructeur d'une Matrice 3x4 par copie d'une matrice 3x4.
     */
    Matrix34T(const Matrix33T &oth, const Vecteur3T &vect) : data{
                                          oth.data[0],
                                          oth.data[1],
                                          oth.data[2],
                                          vec.x
                                          oth.data[3],
                                          oth.data[4],
                                          oth.data[5],
                                          vec.y
                                          oth.data[6],
                                          oth.data[2],
                                          oth.data[2],
                                          vec.z,
                                          }
    {
        mat = oth;
        vec = vect;
    }



    /**
     * @brief Récupère une ligne de la Matrice.
     *
     * @param index position de la Ligne à récuperer dans la Matrice.
     * @return ligne numéro index.
     */
    Vector4T<T> &operator[](size_t index)
    {
        return data2[index];
    }

    /**
     * @brief Récupère un élément de la Matrice.
     *
     * @param index position de l'élément à récuperer dans la Matrice.
     * @return élément numéro index.
     */
    T &operator[](size_t index)
    {
        return data[index];
    }


    public:
    /////////////////////
    //// Operations. ////
    /////////////////////

    Matrix34T operator*(const Matrix34T& oth) const
    {
        Matrix34T result;
        result.data[0] = oth.data[0]*data[0] + oth.data[4]*data[1] + oth.data[8]*data[2];
        result.data[1] = oth.data[1]*data[0] + oth.data[5]*data[1] + oth.data[9]*data[2];
        result.data[2] = oth.data[2]*data[0] + oth.data[6]*data[1] + oth.data[10]*data[2];
        result.data[3] = oth.data[3]*data[0] + oth.data[7]*data[1] + oth.data[11]*data[2] + data[3];
        result.data[4] = oth.data[0]*data[4] + oth.data[4]*data[5] + oth.data[8]*data[6]; 
        result.data[5] = oth.data[1]*data[4] + oth.data[5]*data[5] + oth.data[9]*data[6];
        result.data[6] = oth.data[2]*data[4] + oth.data[6]*data[5] + oth.data[10]*data[6];
        result.data[7] = oth.data[3]*data[4] + oth.data[7]*data[5] + oth.data[11]*data[6] + data[7];
        result.data[8] = oth.data[0]*data[8] + oth.data[4]*data[9] + oth.data[8]*data[10];
        result.data[9] = oth.data[1]*data[8] + oth.data[5]*data[9] + oth.data[9]*data[10];
        result.data[10] = oth.data[2]*data[8] + oth.data[6]*data[9] + oth.data[10]*data[10];
        result.data[11] = oth.data[3]*data[8] + oth.data[7]*data[9] + oth.data[11]*data[10] + data[11];
        return result;
    }

    vec3 operator*(const vec3& oth) const
    {
        return vec3(oth.x*data[0] + oth.y*data[1] + oth.z*data[2] + data[3], 
        oth.x*data[4] + oth.y*data[5] + oth.z*data[6] + data[7], 
        oth.x*data[8] + oth.y*data[9] + oth.z*data[10] + data[11] );
    }


    Matrix34T inverse() const
    {
        Matrix34T result;
        result.mat = mat.transpose();
        result.vec = multiplication(vec,-1);
        return result;
    }

    /// @brief 
    /// @param q quaternion de la rotation. 
    /// @param p position à set.
    void setOrientationAndPosition(const Quaternion& q, const Vector3T& p)
    {
        // Position
        vec = p; 

        // Orientation
        mat.xx = 1 - (2*q.j*q.j + 2*q.k*q.k) ;
        mat.xy = 2*q.i*q.j + 2*q.k*q.r ;
        mat.xz = 2*q.i*q.k - 2*q.j*q.r ;
        mat.yx = 2*q.i*q.j - 2*q.k*q.r ;
        mat.yy = 1 - (2*q.i*q.i + 2*q.k*q.k) ;
        mat.yz = 2*q.j*q.k + 2*q.i*q.r ;
        mat.zx = 2*q.i*q.k + 2*q.j*q.r ;
        mat.zy = 2*q.j*q.k - 2*q.i*q.r ;
        mat.zz = 1 - (2*q.i*q.i + 2*q.j*q.j) ;

    }


    /// @brief Calcule le changement de position
    /// @param vect 
    /// @return 
    Vector3T transformPosition(const &Vector3T vect)
    {
        Vector3T tmp(-data[3],-data[7],-data[11]);
        return Vector3T(
                tmp.x*data[0] + tmp.y*data[4] + tmp.z*data[8],
                tmp.x*data[1] + tmp.y*data[5] + tmp.z*data[9],
                tmp.x*data[2] + tmp.y*data[6] + tmp.z*data[10],
        )
    }

    /// @brief Calcule la nouvelle direction sans toucher à la partie translation
    /// @param vect 
    /// @return 
    Vector3T transformDirection(const &Vector3T vect)
    {
        return Vector3T(
            vect.x * data[0] + vect.y * data[1] + vect.z * data[2],
            vect.x * data[4] + vect.y * data[5] + vect.z * data[6], 
            vect.x * data[8] + vect.y * data[9] + vect.z * data[10],   
        );
    }

};

using Mat34 = Matrix34T<float>;
using Mat34i = Matrix34T<int>;
