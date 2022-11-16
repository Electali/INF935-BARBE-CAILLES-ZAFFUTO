#pragma once
#include "../RigidBody.hpp"
#include "RigidBodyForceGenerator.hpp"
#include <vector>

using namespace std;

class RigidBodyForceRegistry
{
private:
	struct RigidBodyForceEntry
	{
		RigidBody *rigidbody;
		RigidBodyForceGenerator *fg;
	};

	using Registry = vector<RigidBodyForceEntry>;
	Registry registry;

	// RigidBodyForceEntry

public:
	RigidBodyForceRegistry() {

	}

	~RigidBodyForceRegistry() {
		
	}

	void add(RigidBody &rb, RigidBodyForceGenerator &fg)
	{
		RigidBodyForceEntry newForce = RigidBodyForceEntry{&rb, &fg};
		registry.push_back(newForce);
	}

	void remove(RigidBody &rb, RigidBodyForceGenerator &fg)
	{
		Registry::iterator i = registry.begin();
		for (; i != registry.end(); i++)
		{
			if (((i->rigidbody) == &rb) && ((i->fg) == &fg))
			{
				registry.erase(i);
			}
		}
	}

	void clear()
	{
		registry.clear();
	}

	void UpdateForce(float duration)
	{
		for (int i = 0; i < registry.size(); i++)
		{
			registry[i].fg->UpdateForce(*(registry[i].rigidbody),duration);
		}
	}
};