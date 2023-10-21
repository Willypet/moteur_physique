#ifndef PHYSICS_CORE
#define PHYSICS_CORE

#include "Particule.hpp"
#include "ParticleForceGenerator.hpp"
#include "ParticleContactGenerator.hpp"
#include "ParticleContactResolver.hpp"
#include <map>
#include<vector>
#include<set>

namespace Physics {
	class PhysicsCore {
	public:
		void UpdateAll(const float duration, const unsigned int substep);

		void AddForce(ParticleForceGenerator* force, Particule* particule);

		void AddForce(ParticleForceGenerator* force, std::vector<Particule*> particules);

		void AddParticle(Particule* particule);

		void AddContactGenerator(ParticleContactGenerator* contact);

		~PhysicsCore();
	private:
		std::vector<ParticleContact> GenerateContacts();
		void ApplyForces(const float duration);
		void ResolveContacts(std::vector<ParticleContact> &contacts, float duration);
		void UpdateParticlePos(const float duration);
		void ResetParticleAcc();
		std::vector<ParticleContactGenerator*> contactGenerators;
		std::map<ParticleForceGenerator*, std::vector<Particule*>> forces;
		std::set<Particule*> particulesInSim;
		ParticleContactResolver resolver;
	};
}
#endif
