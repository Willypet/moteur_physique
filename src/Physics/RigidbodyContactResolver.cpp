#include "RigidbodyContactResolver.hpp"

namespace Physics {

	RigidbodyContactResolver::RigidbodyContactResolver() {
		this->maxIterations = 0;
		this->currentIteration = 0;
	}

	RigidbodyContactResolver::RigidbodyContactResolver(unsigned int maxIterations) {
		this->maxIterations = maxIterations;
		this->currentIteration = 0;
	}

	void RigidbodyContactResolver::setMaxIterations(unsigned int newMax) {
		maxIterations = newMax;
	}

	void RigidbodyContactResolver::resolveContacts(std::vector<RigidbodyContact> contacts, float duration) {
		//Interpenetration
		currentIteration = 0;
		unsigned int contactsNumber = contacts.size();
		while (currentIteration < maxIterations) {
			float maxPenetration = -1;
			int maxIndex = contactsNumber;
			for (unsigned int i = 0; i < contactsNumber; i++) {
				float penetration = contacts[i].penetration;

				if (penetration > maxPenetration) {
					maxPenetration = penetration;
					maxIndex = i;
				}
			}

			if (maxPenetration <= 0) {
				break;
			}
			contacts[maxIndex].resolveInterpenetration(duration);
		}

		//Vitesse
		currentIteration = 0;
		while(currentIteration < maxIterations){
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

			contacts[minIndex].resolveVelocity(duration);
			currentIteration++;
		}
	}
}