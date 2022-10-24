#include "vector4.hpp"
#include "../maths/vector3.hpp"

/**
 * @brief Classe Matrice de taille 3 par 4,
 * regroupe 3 Vecteur4 de meme type de manière contigüe dans la mémoire.
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
        struct
        {
            Vector4T<T> x, y, z;
        };
        struct
        {
            T xx, xy, xz, xw;
            T yx, yy, yz, yw;
            T zx, zy, zz, zw;
        };
        Vector4T<T> data[3]; //=> Membres de la Matrice accessible comme des Lignes de Vecteurs.
        T data34[12];         //=> Membres de la Matrice accessible comme un Tableau.
    };

public:
    ////////////////////////
    //// Constructeurs. ////
    ////////////////////////

    /**
     * @brief Constructeur d'une Matrice 3x4 de base.
     */
    Matrix34T(T val = 1) : data34{
                               val,0,0,0,
                               0,val,0,0, 
                               0,0,val,0
                           }
    {
    }

    /**
     * @brief Constructeur d'une Matrice 3x4 par copie.
     */
    Matrix34T(const Matrix34T &oth) : data{
                                          oth.data[0],
                                          oth.data[1],
                                          oth.data[2],
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
    Vector34T<T> &operator[](size_t index)
    {
        return data[index];
    }

public:
    


};

// Nouveaux Alias sur des Matrices34.
using mat34 = Matrix34T<float>;
using mat34i = Matrix34T<int>;
