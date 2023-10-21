#include "ParticleContactResolver.hpp"
namespace Physics {

	ParticleContactResolver::ParticleContactResolver() {
		this->maxIterations = 0;
		this->currentIteration = 0;
	}

	ParticleContactResolver::ParticleContactResolver(unsigned int maxIterations) {
		this->maxIterations = maxIterations;
		this->currentIteration = 0;
	}

	void ParticleContactResolver::setMaxIterations(unsigned int newMax) {
		maxIterations = newMax;
	}

	void ParticleContactResolver::resolveContacts(std::vector<ParticleContact> contacts, float duration) {
		currentIteration = 0;
		while (currentIteration < maxIterations) {
			unsigned int contactsNumber = contacts.size();
			float minSeparatingVelocity = 0;
			int minIndex = contactsNumber;
			for (unsigned int i = 0; i < contactsNumber; i++) {
				float separatingVelocity = contacts[i].computeVelocity();

				if (separatingVelocity < minSeparatingVelocity) {
					minSeparatingVelocity = separatingVelocity;
					minIndex = i;
				}
			}

			if (minSeparatingVelocity >= 0) { //Tous les contacts sont résolus
				return;
			}

			contacts[minIndex].resolve(duration);
			currentIteration++;
		}
	}
}