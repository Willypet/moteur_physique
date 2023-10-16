#include "PhysicsCore.hpp"

namespace Physics {
	void PhysicsCore::UpdateAll(const float duration) {
		for (auto iter_forces = forces.begin(); iter_forces != forces.end();){
			auto& [force, particules] = *iter_forces;
			if (force == nullptr) {
				iter_forces = forces.erase(iter_forces);
				continue;
			}
			for (auto iter_particules = particules.begin(); iter_particules != particules.end();) {
				Particule *particule = *iter_particules;
				if (particule == nullptr) {
					iter_particules = particules.erase(iter_particules);
					continue;
				}
				force->UpdateForce(particule, duration);
				iter_particules++;
			}
			iter_forces++;
		}
		UpdateParticlePos(duration);
	}

	void PhysicsCore::UpdateParticlePos(const float duration) {
		for (Particule* particule : particulesInSim) {
			particule->setPosition(particule->getPosition() + particule->getVitesse() * duration);
			particule->setVitesse(particule->getVitesse() + particule->getAcceleration() * duration);
			particule->setAcceleration(Vecteur3D(0, 0, 0));
		}
	}

	void PhysicsCore::AddForce(ParticleForceGenerator* force, Particule* particule){
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

	void PhysicsCore::AddParticle(Particule* particule) {
		particulesInSim.insert(particule);
	}

	PhysicsCore::~PhysicsCore() {
		for (auto& [force, particules] : forces) {
			delete force;
		}
	}
}