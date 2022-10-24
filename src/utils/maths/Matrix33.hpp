#pragma once

#include "vector3.hpp"
#include "../maths/vector3.hpp"

/**
 * @brief Classe Matrice de taille 4 par 4,
 * regroupe 4 Vecteur4 de meme type de manière contigüe dans la mémoire.
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
     * @return Element à l'Index saisie.
     */
    Vector3T<T> &operator[](size_t index)
    {
        return data[index];
    }

public:
    /////////////////////////////////
    //// Fonctions. ////
    /////////////////////////////////

    Matrix33T operator*(const Matrix33T &other) const
    {
        return {
            xx*other.xx + xy*other.yx + xz*other.zx +
            
            }
    }
};

// Nouveaux Alias sur des Matrices33 spécialisés.
using mat3 = Matrix33T<float>;
using mat3i = Matrix33T<int>;