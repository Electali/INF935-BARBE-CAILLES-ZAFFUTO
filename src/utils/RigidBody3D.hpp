#pragma once

#include "./OpenGl/cube.hpp"
#include "./OpenGl/point.hpp"
#include "./OpenGl/shader.hpp"
#include "./OpenGl/transform.hpp"
#include "./RigidBody.hpp"
#include "./maths/Maths.hpp"

/**
 * @brief Classe regroupant la particule physique et sa representation graphique
 */

class RigidBody3D {

public:
  // Partie Physique
  RigidBody rb;

  // Point mesh;
  Cube cube;
  Point point;
  Transform trans;
  bool isCube;

  RigidBody3D() {}

  RigidBody3D(vec3 &p, vec3 &v, float invm, Quaternion &orient, vec3 &rotv,
              float cote) {
    rb = RigidBody(p, v, invm, orient, rotv, cote);
    trans.setPos(p.x, p.y, p.z);
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
  void UpdateGraphics() {
    trans.move(rb.position.x - trans.getPos().x,
               rb.position.y - trans.getPos().y,
               rb.position.z - trans.getPos().z);
    trans.setOrientation(rb.orientation);
  }

  operator RigidBody &() { return rb; }

  AbstractMesh *mesh() {
    if (isCube)
      return &cube;
    return &point;
  }
};