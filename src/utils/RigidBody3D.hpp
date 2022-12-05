#pragma once

#include "./RigidBody.hpp"
#include "./OpenGl/shader.hpp"
#include "./OpenGl/transform.hpp"
#include "./OpenGl/point.hpp"
#include "./OpenGl/cube.hpp"
#include "./maths/Maths.hpp"

/**
 * @brief Classe regroupant la particule physique et sa representation graphique
 */

class RigidBody3D{

public:

    // Partie Physique
    RigidBody rb;

    //Point mesh;
    Cube mesh;
    Transform trans;

    RigidBody3D(vec3 &p,  vec3 &v, float invm, Quaternion &orient, vec3 &rotv, float cote) {
        rb = RigidBody(p, v, invm, orient, rotv, cote);
        trans.setPos(p.x,p.y,p.z);
        trans.setScale(0.1, 0.1, 0.1);
    }

    void setColor(const vec4 &color, Shader &shad) {
        shad.setUniform("color", color);
    }

/*
Equations

angle = 2 * acos(qw)
x = qx / sqrt(1-qw*qw)
y = qy / sqrt(1-qw*qw)
z = qz / sqrt(1-qw*qw)
*/
    void UpdateGraphics(){
        trans.move(rb.position.x - trans.getPos().x,rb.position.y - trans.getPos().y, rb.position.z - trans.getPos().z);
        trans.setOrientation(rb.orientation);
    }

    operator RigidBody&()
    {
        return rb;
    }

};