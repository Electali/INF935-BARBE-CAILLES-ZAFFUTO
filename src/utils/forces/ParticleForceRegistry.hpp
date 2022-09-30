#pragma once

class ParticleForceRegistry 
{
private:
	struct ParticleForceEntry
	{
		particle& particle;
		ParticleForceGenerator& forceGenerator;
	};

	using Registry = std::vector<ParticleForceEntry>;
	Registry registry;


public:

	void add(particle& p,ParticleForceGenerator& fg){
		ParticleForceEntry newForce = ParticleForceEntry(p,fg);
		registry.push_back(newForce);
	}

	void remove(particle& p,ParticleForceGenerator& fg){
		Registry::iterator i = registratry.begin();	
		for(; i!=registratry.end();i++){
			if((i->particle == *p) && (i->fg == fg))
			{	
				registry.erase(i);
			}
		}

	}

	void clear(){
		registry.clear();
	}

	void UpdateForce(float duration)
	{
		Registry::iterator i = registratry.begin();	
		for(; i!=registratry.end();i++){
			i->fg.updateForce(i->particle,duration);
		}
	}

};
