#ifndef VECTOR4_HPP
#define VECTOR4_HPP

/**
 * @brief Classe Vecteur de taille 4,
 * regroupe 4 elements de meme type de manière contigüe dans la mémoire.
 */
template <typename T>
class Vector4T
{
public:
    ////////////////////////
    //// Constructeurs. ////
    ////////////////////////

    /**
     * @brief Constructeur d'un Vector4 de base.
     */
    Vector4T(T newX = 0, T newY = 0, T newZ = 0, T newW = 0):
        x(newX),
        y(newY),
        z(newZ),
        w(newW)
    {
    }

    /**
     * @brief Constructeur d'un Vector4 par copie.
     */
    Vector4T(const Vector4T& oth):
        data{oth.x, oth.y, oth.z, oth.w}
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
    T operator [](size_t index) const
    {
        assert(index < 4);
        return data[index];
    }

    /**
     * @brief Envoie le Vector4 comme un Vector Compatible OpenGL.
     * 
     * @return const float* 
     */
    operator const float*() const
    {
        // La fonction ne marche que sur des Vecteurs de type Float.
        return nullptr;
    }

public:
    //////////////////////////////////////////////////
    //// Surcharge d'Opérateur Binaire par Valeur. ////
    //////////////////////////////////////////////////

    /**
     * @brief Additionne chaque element du Vecteur par la Valeur d'entrée.
     * 
     * @param val 
     * @return Vector4 
     */
    Vector4T operator +(T val) const
    {
        return {
            x + val,
            y + val,
            z + val,
            w + val
        };
    }

    /**
     * @brief Multiplie chaque element du Vecteur par la Valeur d'entrée.
     * 
     * @param val 
     * @return Vector4 
     */
    Vector4T operator *(T val) const
    {
        // Soon le SIMD, j'ai pas le temps ce soir.
        return {
            x * val,
            y * val,
            z * val,
            w * val
        };
    }

public:
    ///////////////////////////////////////////////////
    //// Surcharge d'Opérateur Binaire par Vecteur. ////
    ///////////////////////////////////////////////////

    /**
     * @brief Additionne chaque element du Vecteur par les Valeurs d'un autre Vecteur.
     * 
     * @param val 
     * @return Vector4 
     */
    Vector4T operator +(const Vector4T& oth) const
    {
        return {
            x + oth.x,
            y + oth.y,
            z + oth.z,
            w + oth.w
        };
    }

    /**
     * @brief Multiplie chaque element du Vecteur par les Valeurs d'un autre Vecteur.
     * 
     * @param val 
     * @return Vector4 
     */
    Vector4T operator *(const Vector4T& oth) const
    {
        return {
            x * oth.x,
            y * oth.y,
            z * oth.z,
            w * oth.w
        };
    }

public:
    //////////////////
    //// Membres. ////
    //////////////////

    union
    {
        struct
        {
            T x, y, z, w; //=> Membres du Vecteur accessible comme des Coordonnées.
        };
        struct
        {
            T r, g, b, a; //=> Membres du Vecteur accessible comme des Couleurs.
        };
        struct
        {
            T minX, minY, maxX, maxY;  //=> Membres du Vecteur accessible comme des Rectangles.
        };
        T data[4]; //=> Membres du Vecteur accessible comme un Tableau.
    };
};

/**
 * @brief Envoie le Vector4 comme un Vector Compatible OpenGL.
 * 
 * @return const float* 
 */
template <>
Vector4T<float>::operator const float*() const
{
    return data;
}

// Nouveaux Alias sur des Vecteurs4 spécialisés.
using vec4 = Vector4T<float>;
using vec4f = Vector4T<float>;
using vec4float = Vector4T<float>;
using vec4i = Vector4T<int>;
using vec4int = Vector4T<int>;

#endif // VECTOR4_HPP