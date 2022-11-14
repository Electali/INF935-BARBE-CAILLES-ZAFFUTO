#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "../maths/vector3.hpp"
#include "../maths/matrix44.hpp"

class Transform
{
public:
    ////////////////////////
    //// Constructeurs. ////
    ////////////////////////

    Transform():
        model(1),
        pos(0, 0, 0),
        scale(1, 1, 1),
        rotAxis(0, 0, 0),
        rotAngle(0),
        isDirty(true) {
    }

public:
    ////////////////////////////////////
    //// Fonctions sur la Position. ////
    ////////////////////////////////////

    const vec3& getPos() const
    {
        return pos;
    }

    vec3& getPos()
    {
        return pos;
    }

    Transform& setPos(float x, float y, float z)
    {
        pos = {x, y, z};
        isDirty = true;
        return *this;
    }

    void move(float x, float y, float z)
    {
        pos += {x, y, z};
        isDirty = true;
    }

    void moveX(float val)
    {
        pos.x += val;
        isDirty = true;
    }

    void moveY(float val)
    {
        pos.y += val;
        isDirty = true;
    }

    void moveZ(float val)
    {
        pos.z += val;
        isDirty = true;
    }

public:
    /////////////////////////////////
    //// Fonctions sur le Scale. ////
    /////////////////////////////////

    Transform& setScale(float x, float y, float z)
    {
        scale = {x, y, z};
        isDirty = true;
        return *this;
    }

public:
    ////////////////////////////////////
    //// Fonctions sur la Rotation. ////
    ////////////////////////////////////

    void setRotation(float x, float y, float z, float angle)
    {
        rotAxis = {x, y, z};
        rotAngle = angle;
        isDirty = true;
    }

public:
    /////////////////////////////////////////////////
    //// Fonctions de regeneration du Transform. ////
    /////////////////////////////////////////////////

    /**
     * @brief Récupération de la Matrice de Transformation, avec Recalcul si Alteration durant la Frame.
     * 
     * @return const mat4& 
     */
    const mat4& getModel()
    {
        if (isDirty)
        {
            model = mat4();
            model.setPos(pos);
            model.setScale(scale);
            // Mettre un SetRotation(x, y, z, angle) ici.
            isDirty = false;
        }
        return model;
    }

private:
    //////////////////
    //// Membres. ////
    //////////////////

    mat4 model; //=> La Matrice de Transformation de l'Objet à Afficher.
    vec3 pos; //=> La Position de l'Objet.
    vec3 scale; //=> La Taille de l'Objet.
    vec3 rotAxis; //=> L'Axe de Rotation de l'Objet.
    float rotAngle; //=> L'Angle de Rotation de l'Objet.
    bool isDirty; //=> Flag evitant un recalcul permanent de la Matrice de Transformation.
};

#endif // TRANSFORM_HPP