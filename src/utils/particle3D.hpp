#pragma once

#include "particle.hpp"
#include "./OpenGl/shader.hpp"
#include "./OpenGl/transform.hpp"
#include "./OpenGl/point.hpp"
#include "./OpenGL/vector4.hpp"

/**
 * @brief Classe regroupant la particule physique et sa representation graphique
 */

class particle3D{

public:

    // Partie Physique
    particle part;

    // Partie Graphique 
    Shader shad;
    Point mesh;
    Transform trans;
    

    particle3D(vec3 pos, vec3 vit, vec3 accel, float invMass, float damping) {
        part = particle(pos, vit, accel, invMass, damping);
        trans;
        trans.setPos(pos.x,pos.y,pos.z);
        shad.setUniform("color", vec4(1, 1, 1, 1));
    }

    void setColor(vec4 color) {
        shad.setUniform("color", color);
    }

    void UpdateGraphics(){
        trans.move(part.position.x - trans.getPos().x,part.position.y - trans.getPos().y, part.position.z - trans.getPos().z);
    }

    operator particle&()
    {
        return part;
    }

};