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
        struct {
            Vector4T<T> x, y, z, w;
        };
        struct {
            T xx, xy, xz, xw;
            T yx, yy, yz, yw;
            T zx, zy, zz, zw;
            T wx, wy, wz, ww;
        };
        struct {        //=> Representation d'une matrice comprenant une matrice 3*3,un vect3 et une ligne {0,0,0,1};
            Matrix33T<T> mat;
            Vector3T<T> vec;
        };
        
        Vector4T<T> data[4]; //=> Membres de la Matrice accessible comme des Lignes de Vecteurs.
        T data2[16]; //=> Membres de la Matrice accessible comme un Tableau.
    };


    /**
     * @brief Récupère une ligne de la Matrice.
     *
     * @param index position de la Ligne à récuperer dans la Matrice.
     * @return ligne numéro index.
     */
    Vector4T<T> &operator[](size_t index)
    {
        return data[index];
    }

    /**
     * @brief Récupère un élément de la Matrice.
     *
     * @param index position de l'élément à récuperer dans la Matrice.
     * @return élément numéro index.
     */
    T &operator[](size_t index)
    {
        return data2[index];
    }


    public:
    /////////////////////
    //// Operations. ////
    /////////////////////

    Matrix34T operator*(const Matrix34T& oth) const
    {

    }

    vec4 operator*(const Matrix34T& oth) const
    {

    }

    Matrix34T inverse();


};

using Mat34 = Matrix34T<float>;
using Mat34i = Matrix34T<int>;
