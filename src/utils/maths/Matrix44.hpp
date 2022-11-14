#ifndef MATRIX44_HPP
#define MATRIX44_HPP

#include "vector4.hpp"
#include "vector3.hpp"
#include <cmath>

using namespace std;

/**
 * @brief Classe Matrice de taille 4 par 4,
 * regroupe 4 Vecteur4 de meme type de manière contigüe dans la mémoire.
 */
template <typename T>
class Matrix44T
{
public:
    ////////////////////////
    //// Constructeurs. ////
    ////////////////////////

    /**
     * @brief Constructeur d'une Matrice 4x4 de base.
     */
    constexpr Matrix44T(T val = 1) noexcept:
        data2{
            val, 0, 0, 0,
            0, val, 0, 0,
            0, 0, val, 0,
            0, 0, 0, val
        }
    {
    }

    /**
     * @brief Constructeur d'une Matrice 4x4 par copie.
     */
    constexpr Matrix44T(const Matrix44T& oth) noexcept:
        data {
            oth.data[0],
            oth.data[1],
            oth.data[2],
            oth.data[3]
        }
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
    [[nodiscard]] constexpr const Vector4T<T>& operator [](size_t index) const noexcept
    {
        return data[index];
    }

    /**
     * @brief Accès aux Lignes de la Matrice selon la Colonne.
     * 
     * @param index position de la Ligne à récuperer dans la Matrice.
     * @return Element à l'Index saisie. 
     */
    [[nodiscard]] constexpr Vector4T<T>& operator [](size_t index) noexcept
    {
        return data[index];
    }

    /**
     * @brief Envoie la Matrice44 comme une Matrice Compatible OpenGL.
     * 
     * @return const float* 
     */
    [[nodiscard]] constexpr operator const float*() const noexcept
    {
        // La fonction ne marche que sur des Matrice de type Float.
        return nullptr;
    }

public:
    /////////////////////////////////
    //// Fonctions de geometrie. ////
    /////////////////////////////////

    /**
     * @brief Déplace la Matrice à la Position voulue.
     * 
     * @param vec Nouvelle Position.
     */
    void setPos(const Vector3T<T> &vec) 
    {
        data[3] = data[0] * vec[0] + data[1] * vec[1] + data[2] * vec[2] + data[3];
    }

    void setScale(const Vector3T<T> &vec)
    {
        xx = vec.x;
        yy = vec.y;
        zz = vec.z;
    }

public:
    //////////////////
    //// Membres. ////
    //////////////////

    union
    {
        struct {
            Vector4T<T> x, y, z, w;
        };
        struct {
            T xx, xy, xz, xw;
            T yx, yy, yz, yw;
            T zx, zy, zz, zw;
            T wx, wy, wz, ww;
        };
        Vector4T<T> data[4]; //=> Membres de la Matrice accessible comme des Lignes de Vecteurs.
        T data2[16]; //=> Membres de la Matrice accessible comme un Tableau.
    };
};

// Nouveaux Alias sur des Matrices44 spécialisés.
using mat4 = Matrix44T<float>;
using mat4f = Matrix44T<float>;
using mat4float = Matrix44T<float>;
using mat4i = Matrix44T<int>;
using mat4int = Matrix44T<int>;

/**
 * @brief Envoie la Matrice44 comme une Matrice Compatible OpenGL.
 * 
 * @return const float* 
 */
template <>
[[nodiscard]] constexpr Matrix44T<float>::operator const float*() const noexcept
{
    return data2;
}

#endif // MATRIX44_HPP