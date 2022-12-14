#pragma once
#include "../particle.hpp"
#include "ParticleForceGenerator.hpp"
#include <vector>

using namespace std;

class ParticleForceRegistry
{
private:
	struct ParticleForceEntry
	{
		particle *particle;
		ParticleForceGenerator *fg;
	};

	using Registry = vector<ParticleForceEntry>;
	Registry registry;

	// ParticleForceEntry

public:
	ParticleForceRegistry() {

	}

	~ParticleForceRegistry() {
		
	}

	void add(particle &p, ParticleForceGenerator &fg)
	{
		ParticleForceEntry newForce = ParticleForceEntry{&p, &fg};
		registry.push_back(newForce);
	}

	void remove(particle &p, ParticleForceGenerator &fg)
	{
		Registry::iterator i = registry.begin();
		for (; i != registry.end(); i++)
		{
			if (((i->particle) == &p) && ((i->fg) == &fg))
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
			registry[i].fg->UpdateForce(*(registry[i].particle),duration);
		}
	}
};
