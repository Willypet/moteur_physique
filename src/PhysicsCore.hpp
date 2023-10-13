#ifndef PHYSICS_CORE
#define PHYSICS_CORE

#include "Particule.hpp"
#include "ParticleForceGenerator.hpp"
#include <map>
#include<vector>

namespace Physics {
	class PhysicsCore {
	public:
		std::map<ParticleForceGenerator, std::vector<Particule>> forces;

		void UpdateAll(const float duration);
	};
}
#endif
