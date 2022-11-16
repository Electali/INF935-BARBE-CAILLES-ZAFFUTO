#pragma once
#include "./maths/Maths.hpp"

class RigidBody
{
public:
    // Physique de base comme les particules
    vec3 position;
    vec3 velocity;
    vec3 acceleration;
    float inverseMass;
    float damping;

    // Orientation et rotation

    // orientation = position
    Quaternion orientation;

    // vitesse angulaire = vitesse
    vec3 rotationVelocity;
    vec3 rotationAcceleration;
    mat34 transformMatrix;

    mat3 invInertiaMatrix;

    // forces = acceleration
    float angularDamping;
    vec3 forceAccu;
    vec3 torqueAccu;

public:
    RigidBody() {}

    RigidBody(const vec3 p, const vec3 v, const float invm, const Quaternion orient, const vec3 rotv, float cote)
    {
        // physique lin�aire
        position = p;
        velocity = v;
        acceleration = {};
        inverseMass = invm;
        damping = 1; // hardcoder mais on peut le mettre en parametre par la suite;

        // physique rotationelle
        orientation = orient;
        rotationVelocity = rotv;
        rotationAcceleration = {};

        transformMatrix.setOrientationAndPosition(orientation, position);

        angularDamping = 1;
        forceAccu = {};
        torqueAccu = {};

        // Calcul de la matrice inverse d'inertie
        // pour le moment nous utiliserons des cubes
        invInertiaMatrix = Matrix33();
        float coeff = ((1 / inverseMass) / 6) * cote * cote;
        invInertiaMatrix.data[0] = coeff;
        invInertiaMatrix.data[4] = coeff;
        invInertiaMatrix.data[8] = coeff;
        invInertiaMatrix.inverse();
    };

public:
    void AddForce(const vec3 &force)
    {
        forceAccu += force;
    }

    void AddForceAtPoint(vec3 &force, const vec3 &worldPoint)
    {
        vec3 pt = worldPoint;
        pt = pt - position;

        forceAccu += force;
        torqueAccu += prodVectExt(pt, force);
    }

    void AddForceAtBodyPoint(vec3 &force, const vec3 &LocalPoint)
    {
        vec3 ptInWorld = LocalToWorld(LocalPoint);
        AddForceAtPoint(force, ptInWorld);
    }

    void clearAccumulators()
    {
        torqueAccu = {};
        forceAccu = {};
    }

    vec3 WorldToLocal(const vec3 &world)
    {
        return transformMatrix.worldToLocal(world);
    }

    vec3 LocalToWorld(const vec3 &local)
    {
        return transformMatrix.localToWorld(local);
    }

    void CalculateDerivedData()
    {
        orientation.Normalize();
        transformMatrix.setOrientationAndPosition(orientation, position);
        // Calcule la matrice de torseur inverse dans les coordonn�es globales.
    }
};