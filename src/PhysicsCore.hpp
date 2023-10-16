#ifndef PHYSICS_CORE
#define PHYSICS_CORE

#include "Particule.hpp"
#include "ParticleForceGenerator.hpp"
#include <map>
#include<vector>

namespace Physics {
	class PhysicsCore {
	public:
		void UpdateAll(const float duration);

		void AddForce(ParticleForceGenerator* force, Particule* particule);

		void AddForce(ParticleForceGenerator* force, std::vector<Particule*> particules);
	private:
		std::map<ParticleForceGenerator*, std::vector<Particule*>> forces;
	};
}
#endif
