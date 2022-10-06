#ifndef VECTOR3_HPP
#define VECTOR3_HPP

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
    Vector3T(T newX = 0, T newY = 0, T newZ = 0):
        x(newX),
        y(newY),
        z(newZ)
    {
    }

    /**
     * @brief Constructeur d'un Vector3 par copie.
     */
    Vector3T(const Vector3T& oth):
        data{oth.x, oth.y, oth.z}
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
        assert(index < 3);
        return data[index];
    }

public:
    ////////////////////////////////////////////////////
    //// Surcharge d'Opérateur Binaire par Vecteur. ////
    ////////////////////////////////////////////////////

    /**
     * @brief Additionne chaque element du Vecteur par les Valeurs d'un autre Vecteur.
     * 
     * @param val 
     * @return Vector4 
     */
    Vector3T operator +(const Vector3T& oth)
    {
        return {
            x + oth.x,
            y + oth.y,
            z + oth.z
        };
    }

public:
    ///////////////////////////////////////////////////
    //// Surcharge d'Opérateur Unaire par Vecteur. ////
    ///////////////////////////////////////////////////

    /**
     * @brief Additionne dans chaque element du Vecteur les Valeurs d'un autre Vecteur.
     * 
     * @param val 
     * @return Vector4 
     */
    Vector3T& operator +=(const Vector3T& oth)
    {
        x += oth.x;
        y += oth.y;
        z += oth.z;
        return *this;
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
};

// Nouveaux Alias sur des Vecteurs3 spécialisés.
using vec3 = Vector3T<float>;
using vec3f = Vector3T<float>;
using vec3float = Vector3T<float>;
using vec3i = Vector3T<int>;
using vec3int = Vector3T<int>;

#endif // VECTOR3_HPP