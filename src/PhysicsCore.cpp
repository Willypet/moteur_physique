#include "PhysicsCore.hpp"

namespace Physics {
	void PhysicsCore::UpdateAll(const float duration) {
		for (const auto & [force, particules] : forces) {
			for (const Particule* particule : particules) {
				force->UpdateForce(*particule, duration);
			}
		}
	}

	void PhysicsCore::AddForce(ParticleForceGenerator* force, Particule* particule) {
		if (auto elem = forces.find(force); elem != forces.end()) {
			std::vector<Particule*> particules = elem->second;
			particules.insert(particules.end(), particule);
		}
		else {
			forces.insert({ force, std::vector<Particule*>({ particule }) });
		}
	}

	void PhysicsCore::AddForce(ParticleForceGenerator* force, std::vector<Particule*> particules) {
		if (auto elem = forces.find(force); elem != forces.end()) {
			std::vector<Particule*> particules = elem->second;
			particules.insert(particules.end(), particules.begin(), particules.end());
		}
		else {
			forces.insert({ force, std::vector<Particule*>(particules) });
		}
	}
}