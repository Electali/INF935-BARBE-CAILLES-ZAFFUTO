#pragma once

#include "vector3.hpp"
#include "../maths/vector3.hpp"

/**
 * @brief Classe Matrice de taille 3 par 3,
 * regroupe 3 Vecteur3 de meme type de manière contigüe dans la mémoire.
 */
template <typename T>
class Matrix33T
{
public:
    //////////////////
    //// Membres. ////
    //////////////////

    union
    {
        struct
        {
            Vector3T<T> x, y, z;
        };
        struct
        {
            T xx, xy, xz;
            T yx, yy, yz;
            T zx, zy, zz;
        };
        Vector3T<T> data[3]; //=> Membres de la Matrice accessible comme des Lignes de Vecteurs.
        T data2[9];          //=> Membres de la Matrice accessible comme un Tableau.
    };

public:
    ////////////////////////
    //// Constructeurs. ////
    ////////////////////////

    /**
     * @brief Constructeur d'une Matrice 3x3 de base.
     */
    Matrix33T(T val = 1) : data2{
                               val, 0, 0,
                               0, val, 0,
                               0, 0, val}
    {
    }

    /**
     * @brief Constructeur d'une Matrice 3x3 par copie.
     */
    Matrix33T(const Matrix33T &oth) : data{
                                          oth.data[0],
                                          oth.data[1],
                                          oth.data[2]}
    {
    }

public:
    ////////////////////////////
    //// Accès aux données. ////
    ////////////////////////////

    /**
     * @brief Accès aux Lignes de la Matrice selon la Colonne.
     *
     * @param index position de la Ligne à récuperer dans la Matrice.
     * @return 
     */
    Vector4T<T> &operator[](size_t index)
    {
        return data[index];
    }

public:
    /////////////////////////////////
    //// Fonctions. ////
    /////////////////////////////////

    Matrix33T operator*(const Matrix33T &other) const
    {
        return
        {
            xx *other.xx + xy *other.yx + xz *other.zx,
            xx *other.xy + xy *other.yy + xz *other.zy,
            xx *other.xz + xy *other.yz + xz *other.zz,
            yx *other.xx + yy *other.xy + yz *other.zx,
            yx *other.yx + yy *other.yy + yz *other.zy,
            yx *other.xz + yy *other.yz + yz *other.zz,
            zx *other.xx + zy *other.xy + zz *other.zx,
            zx *other.yx + zy *other.yy + zz *other.zy,
            zx *other.xz + zy *other.yz + zz *other.zz
        }
    }

    Matrix33T operator*(const Vector3T<T> &vector) const
    {
        return
        {
            xx *vector.x + xy *vector.y + xz *vector.z,
            yx *vector.x + yy *vector.x + yz *vector.z,
            zx *vector.x + zy *vector.x + zz *vector.z
        }
    }

    Matrix33T operator*(const float &coeff) const
    {
        return
        {
            coeff*xx, coeff*xy, coeff*xz,
            coeff*yx, coeff*yy, coeff*yz,
            coeff*zx, coeff*zy, coeff*zz
        }
    }

    Matrix33T inverse()
    {
        float invDet = 1 / (xx * yy * zz + yx * zx * xz + zx * xy * yz - xx * zx * yz - zx * yy * xz - yx * xy * zz);
        Matrix33T inv = 
        {
            
        };
        return;
        
    }
};

// Nouveaux Alias sur des Matrices33 spécialisés.
using mat3 = Matrix33T<float>;
using mat3i = Matrix33T<int>;