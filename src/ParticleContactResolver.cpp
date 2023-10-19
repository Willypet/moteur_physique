#include "ParticleContactResolver.hpp"
namespace Physics {

	ParticleContactResolver::ParticleContactResolver(int maxIterations) {
		this->maxIterations = maxIterations;
		this->currentIteration = 0;
	}

	void ParticleContactResolver::setMaxIterations(int newMax) {
		maxIterations = newMax;
	}

	void ParticleContactResolver::resolveContacts(ParticleContact* contacts, int contactsNumber, float duration) {
		currentIteration = 0;
		while (currentIteration < maxIterations) {
			float maxVelocity = 0;
			int maxIndex = contactsNumber;
			for (int i = 0; i < contactsNumber; i++) {
				float separatingVelocity = contacts[i].computeVelocity();

				if (separatingVelocity > maxVelocity) {
					maxVelocity = separatingVelocity;
					maxIndex = i;
				}
			}
			contacts[maxIndex].resolve(duration);
			currentIteration++;
		}
	}
}