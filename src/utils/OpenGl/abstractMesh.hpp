#ifndef ABSTRACT_MESH_HPP
#define ABSTRACT_MESH_HPP

#include "shader.hpp"
#include "transform.hpp"

class AbstractMesh
{
public:
    virtual void draw(const Shader &shader, Transform& transform) {};
};

#endif