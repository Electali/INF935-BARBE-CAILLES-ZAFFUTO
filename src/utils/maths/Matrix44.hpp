#ifndef MATRIX44_HPP
#define MATRIX44_HPP

#include "vector4.hpp"
#include "vector3.hpp"
#include <cmath>
#include "Quaternion.hpp"

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

    void setRotation(const Quaternion &quat) {
        Matrix44T rot = Matrix44T(1);
         
        //std::cout << "Quaternion en matrice"<< std::endl;
        rot.tomat44(quat);
        
       // rot.show();
        *this = rot.inverse() * (* this) ;

    }

    Matrix44T inverse()
    {
        Matrix44T res = Matrix44T(0);
        res.data2[0] = data2[0];
        res.data2[1] = data2[4];
        res.data2[2] = data2[8];
        res.data2[3] = data2[12];

        res.data2[4] = data2[1];
        res.data2[5] = data2[5];
        res.data2[6] = data2[9];
        res.data2[7] = data2[13];

        res.data2[8] = data2[2];
        res.data2[9] = data2[6];
        res.data2[10] = data2[10];
        res.data2[11] = data2[14];

        res.data2[12] = data2[3];
        res.data2[13] = data2[7];
        res.data2[14] = data2[11];
        res.data2[15] = data2[15];

        return res;

    }

    void tomat44(Quaternion q)
    {
        data2[0] = 1 - (2 * q.j * q.j + 2 * q.k * q.k);
        data2[1] = 2 * q.i * q.j + 2 * q.k * q.r;
        data2[2] = 2 * q.i * q.k - 2 * q.j * q.r;
        data2[4] = 2 * q.i * q.j - 2 * q.k * q.r;
        data2[5] = 1 - (2 * q.i * q.i + 2 * q.k * q.k);
        data2[6] = 2 * q.j * q.k + 2 * q.i * q.r;
        data2[8] = 2 * q.i * q.k + 2 * q.j * q.r;
        data2[9] = 2 * q.j * q.k - 2 * q.i * q.r;
        data2[10] = 1 - (2 * q.i * q.i + 2 * q.j * q.j);
        return ;
    }

    Matrix44T<T> operator*(const Matrix44T& other) const
    {
        Matrix44T result;
        result.data2[0] = data2[0] * other.data2[0] + data2[1] * other.data2[4] + data2[2] * other.data2[8] + data2[3] * other.data2[12];
        result.data2[1] = data2[0] * other.data2[1] + data2[1] * other.data2[5] + data2[2] * other.data2[9] + data2[3] * other.data2[13];
        result.data2[2] = data2[0] * other.data2[2] + data2[1] * other.data2[6] + data2[2] * other.data2[10] + data2[3] * other.data2[14];
        result.data2[3] = data2[0] * other.data2[3] + data2[1] * other.data2[7] + data2[2] * other.data2[11] + data2[3] * other.data2[15];

        result.data2[4] = data2[4] * other.data2[0] + data2[5] * other.data2[4] + data2[6] * other.data2[8] + data2[7] * other.data2[12];
        result.data2[5] = data2[4] * other.data2[1] + data2[5] * other.data2[5] + data2[6] * other.data2[9] + data2[7] * other.data2[13];
        result.data2[6] = data2[4] * other.data2[2] + data2[5] * other.data2[6] + data2[6] * other.data2[10] + data2[7] * other.data2[14];
        result.data2[7] = data2[4] * other.data2[3] + data2[5] * other.data2[7] + data2[6] * other.data2[11] + data2[7] * other.data2[15];

        result.data2[8] = data2[8] * other.data2[0] + data2[9] * other.data2[4] + data2[10] * other.data2[8] + data2[11] * other.data2[12];
        result.data2[9] = data2[8] * other.data2[1] + data2[9] * other.data2[5] + data2[10] * other.data2[9] + data2[11] * other.data2[13];
        result.data2[10] = data2[8] * other.data2[2] + data2[9] * other.data2[6] + data2[10] * other.data2[10] + data2[11] * other.data2[14];
        result.data2[11] = data2[8] * other.data2[3] + data2[9] * other.data2[7] + data2[10] * other.data2[11] + data2[11] * other.data2[15];

        result.data2[12] = data2[12] * other.data2[0] + data2[13] * other.data2[4] + data2[14] * other.data2[8] + data2[15] * other.data2[12];
        result.data2[13] = data2[12] * other.data2[1] + data2[13] * other.data2[5] + data2[14] * other.data2[9] + data2[15] * other.data2[13];
        result.data2[14] = data2[12] * other.data2[2] + data2[13] * other.data2[6] + data2[14] * other.data2[10] + data2[15] * other.data2[14];
        result.data2[15] = data2[12] * other.data2[3] + data2[13] * other.data2[7] + data2[14] * other.data2[11] + data2[15] * other.data2[15];
        return result;
    }


    void show()
    {
        std::cout << "|" << data2[0] << "|" << data2[1] << "|" << data2[2] << "|" << data2[3] << "|" << std::endl;
        std::cout << "|" << data2[4] << "|" << data2[5] << "|" << data2[6] << "|" << data2[7] << "|" << std::endl;
        std::cout << "|" << data2[8] << "|" << data2[9] << "|" << data2[10] << "|" << data2[11] << "|" << std::endl;
        std::cout << "|" << data2[12] << "|" << data2[13] << "|" << data2[14] << "|" << data2[15] << "|" << std::endl;
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