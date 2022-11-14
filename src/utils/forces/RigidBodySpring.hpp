#include "RigidBodyForceGenerator.hpp"

class RigidBodySpring : public RigidBodyForceGenerator
{
public:

	vec3 ptAttach;
	vec3 othPtAttach;

	RigidBody* other;

	float springConstant;
	float restLength;

public:

	RigidBodySpring(RigidBody* oth, const vec3 attach, const vec3 othAttach, const sprCnst, const restLen)
	{
		other = oth;
		ptAttach = attach;
		othPtAttach = othAttach;
		springConstant = sprCnst;
		restLength = restLen;
	}

public :

	void UpdateForce(RigidBody& rb, float duration)
	{
		//Calcul du vecteur de force
		vec3 lws = rb.LocalToWorld(ptAttach);
		vec3 othws = other->LocalToWorld(othPtAttach);
		vec3 force = lws - othws;

		//Calcul la valeur de la force
		float valF = abs(force.norme() - restLength) * springConstant;

		//Calcul la force finale
		force.normalise();
		force *= -valF

		//Applique la force au point ou le resort est attache.
		rb.AddForceAtPoint(force,lws);

	}


};