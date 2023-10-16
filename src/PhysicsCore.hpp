#ifndef PHYSICS_CORE
#define PHYSICS_CORE

#include "Particule.hpp"
#include "ParticleForceGenerator.hpp"
#include <map>
#include<vector>
#include<set>

namespace Physics {
	class PhysicsCore {
	public:
		void UpdateAll(const float duration);

		void UpdateParticlePos(const float duration);

		void AddForce(ParticleForceGenerator* force, Particule* particule);

		void AddForce(ParticleForceGenerator* force, std::vector<Particule*> particules);

		void AddParticle(Particule* particule);
		~PhysicsCore();
	private:
		std::map<ParticleForceGenerator*, std::vector<Particule*>> forces;
		std::set<Particule*> particulesInSim;

	};
}
#endif
