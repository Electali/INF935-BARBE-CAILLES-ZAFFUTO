#ifndef VECTOR3_HPP
#define VECTOR3_HPP

#include <iostream>
#include <math.h>
#include <assert.h>

/**
 * @brief Classe Vecteur de taille 3, regroupe 3 elements de meme Type de manière Contigüe dans la mémoire.
 */
template <typename T>
class Vector3T
{
public:
    ////////////////////////
    //// Constructeurs. ////
    ////////////////////////

    /**
     * @brief Constructeur d'un Vector3 de base.
     */
    Vector3T(T newX = 0, T newY = 0, T newZ = 0) : x(newX),
                                                   y(newY),
                                                   z(newZ)
    {
    }

    /**
     * @brief Constructeur d'un Vector3 par copie.
     */
    Vector3T(const Vector3T &oth) : data{oth.x, oth.y, oth.z}
    {
    }

public:
    ////////////////////////////
    //// Accès aux données. ////
    ////////////////////////////

    /**
     * @brief Accès aux élèments du vecteur comme un simple tableau.
     *
     * @param index position de l'élèment à récuperer dans le vecteur.
     * @return Element à l'Index saisie.
     */
    T operator[](size_t index) const
    {
        assert(index < 3);
        return data[index];
    }

    T getX() const
    {
        return x;
    }

    T getY() const
    {
        return y;
    }

    T getZ() const
    {
        return z;
    }

public:
    ////////////////////
    //// Inversion  ////
    ////////////////////

    void inversion()
    {
        x = -x;
        y = -y;
        z = -z;
    }

    Vector3T inverse() const
    {
        return Vector3T(-x, -y, -z);
    }

public:
    ///////////////////////
    //// Normalisation ////
    ///////////////////////
    float normeCarre() const
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
        if (norme > 0)
        {
            *this *= 1 / norme;
        }
    }

    friend Vector3T normalisation(Vector3T v)
    {
        Vector3T res = Vector3T(v.x, v.y, v.z);
        res.normalise();
        return res;
    }

public:
    //////////////////
    //// Addition ////
    //////////////////

    /**
     * @brief Additionne chaque element du Vecteur par les Valeurs d'un autre Vecteur.
     *
     * @param val
     * @return Vector3
     */
    Vector3T operator+(const Vector3T &oth)
    {
        return {
            x + oth.x,
            y + oth.y,
            z + oth.z};
    }

    /**
     * @brief Additionne dans chaque element du Vecteur les Valeurs d'un autre Vecteur.
     *
     * @param val
     * @return Vector3
     */
    Vector3T &operator+=(const Vector3T &oth)
    {
        x += oth.x;
        y += oth.y;
        z += oth.z;
        return *this;
    }

    friend Vector3T addition(Vector3T &v1, Vector3T &v2)
    {
        return Vector3T((v1.x + v2.x), (v1.y + v2.y), (v1.z + v2.z));
    }

public:
    //////////////////////
    //// Soustraction ////
    //////////////////////

    /**
     * @brief Soustrait chaque element du Vecteur par les Valeurs d'un autre Vecteur.
     *
     * @param val
     * @return Vector3
     */
    Vector3T operator-(const Vector3T &oth)
    {
        return {
            x - oth.x,
            y - oth.y,
            z - oth.z};
    }

    /**
     * @brief Soustrait dans chaque element du Vecteur les Valeurs d'un autre Vecteur.
     *
     * @param val
     * @return Vector3
     */
    Vector3T &operator-=(const Vector3T &oth)
    {
        x -= oth.x;
        y -= oth.y;
        z -= oth.z;
        return *this;
    }

    friend Vector3T soustraction(Vector3T &v1, Vector3T &v2)
    {
        return Vector3T((v1.x - v2.x), (v1.y - v2.y), (v1.z - v2.z));
    }

public:
    ////////////////////////
    //// Multiplication ////
    ////////////////////////

    friend Vector3T multiplication(Vector3T &v, float lambda)
    {
        return Vector3T(v.x * lambda, v.y * lambda, v.z * lambda);
    }

    void operator*=(float a)
    {
        x *= a;
        y *= a;
        z *= a;
    }

    float prodScal(Vector3T v)
    {
        return x * v.x + y * v.y + z * v.z;
    }

    friend float prodScalExt(Vector3T &v1, Vector3T &v2)
    {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    void prodVect(Vector3T v)
    {
        float nx = y * v.z - z * v.y;
        float ny = z * v.x - x * v.z;
        float nz = x * v.y - y * v.x;

        x = nx;
        y = ny;
        z = nz;
    }

    friend Vector3T prodVectExt(Vector3T &v1, Vector3T &v2)
    {
        return Vector3T(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
    }

public:
    /////////////////////////
    //// Base orthonorme ////
    /////////////////////////

    friend void baseOrtho(Vector3T &v1, Vector3T &v2, Vector3T &v3)
    {
        v1.normalise();
        v3 = prodVectExt(v1, v2);

        if (v3.normeCarre() == 0.0)
            return; // v1 et v2 paralleles
        v3.normalise();
        v2 = prodVectExt(v3, v1);
        return;
    }

public:
    //////////////////
    //// Membres. ////
    //////////////////

    union
    {
        struct
        {
            T x, y, z; //=> Membres du Vecteur accessible comme des Coordonnées.
        };
        struct
        {
            T r, g, b; //=> Membres du Vecteur accessible comme des Couleurs.
        };
        T data[3]; //=> Membres du Vecteur accessible comme un Tableau.
    };

    void show()
    {
        std::cout << "(" << x << "," << y << "," << z << ")\n";
    }
};

// Nouveaux Alias sur des Vecteurs3 spécialisés.
using vec3 = Vector3T<float>;
using vec3f = Vector3T<float>;
using vec3float = Vector3T<float>;
using vec3i = Vector3T<int>;
using vec3int = Vector3T<int>;

#endif // VECTOR3_HPP