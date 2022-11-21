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
    mat3 transformInertiaMatrix;

    // forces = acceleration
    float angularDamping;
    vec3 forceAccu;
    vec3 torqueAccu;

public:
    RigidBody() {}

    RigidBody(const vec3 p, const vec3 v, const float invm, const Quaternion orient, const vec3 rotv, float cote)
    {
        // physique lineaire
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
        float coeff = ((1 / inverseMass * 6) ) * cote * cote;
        invInertiaMatrix.data[0] = coeff;
        invInertiaMatrix.data[4] = coeff;
        invInertiaMatrix.data[8] = coeff;
        invInertiaMatrix.inverse();
        
        //
        transformInertiaMatrix = Matrix33();
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

    void transformInertiaTensor(mat3& worldInert, const mat3& invInert, const mat34 transf)
    {

        float t1 = invInert.data[0] * transf.data [0];
        float t2 = invInert.data[0] * transf.data [4];
        float t3 = invInert.data[0] * transf.data [8];
        
        float t4 = invInert.data[4] * transf.data [1];
        float t5 = invInert.data[4] * transf.data [5];
        float t6 = invInert.data[4] * transf.data [9];

        float t7 = invInert.data[8] * transf.data [2];
        float t8 = invInert.data[8] * transf.data [6];
        float t9 = invInert.data[8] * transf.data [10];


        worldInert.data[0] = t1 * transf.data[0] + t2 * transf.data[1] + t3 * transf.data[2];
        worldInert.data[1] = t1 * transf.data[4] + t2 * transf.data[5] + t3 * transf.data[6];
        worldInert.data[2] = t1 * transf.data[8] + t2 * transf.data[9] + t3 * transf.data[10];

        worldInert.data[3] = t4 * transf.data[0] + t5 * transf.data[1] + t6 * transf.data[2];
        worldInert.data[4] = t4 * transf.data[4] + t5 * transf.data[5] + t6 * transf.data[6];
        worldInert.data[5] = t4 * transf.data[8] + t5 * transf.data[9] + t6 * transf.data[10];

        worldInert.data[6] = t7 * transf.data[0] + t8 * transf.data[1] + t9 * transf.data[2];
        worldInert.data[7] = t7 * transf.data[4] + t8 * transf.data[5] + t9 * transf.data[6];
        worldInert.data[8] = t7 * transf.data[8] + t8 * transf.data[9] + t9 * transf.data[10];

    }


    void CalculateDerivedData()
    {
        orientation.Normalize();
        transformMatrix.setOrientationAndPosition(orientation, position);
        transformInertiaTensor(transformInertiaMatrix, invInertiaMatrix, transformMatrix);
    }
};