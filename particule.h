#include "vector3D.h"

class particule {

    private :

        vector3D Position;
        vector3D Velocity;
        vector3D Acceleration;

        float InverseMass;
        float Damping;

    public :

    particule();

    particule(vector3D p; vector3D v; vector3D a; float m; float d);

    setPosition(vector3D p);

    setVelocity(vector3D v);

    setAcceleration(vector3D a);

    setMass(float m);

    setDamping(float d);

}