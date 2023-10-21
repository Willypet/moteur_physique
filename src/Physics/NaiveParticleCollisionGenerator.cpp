#include "NaiveParticleCollisionGenerator.hpp"

namespace Physics {
	void NaiveParticleCollisionGenerator::addContact(std::vector<ParticleContact> &contacts) const {
		unsigned int size = particles.size();
		for (unsigned int i = 0; i < size - 1; i++) {
			for (unsigned int j = i + 1; j < size; j++) {
				float distance = (particles[i]->getPosition() - particles[j]->getPosition()).magnitude();
				float maxDistance = particles[i]->getRadius() + particles[j]->getRadius();
				if (distance <= maxDistance) {
					ParticleContact contact;
					contact.particles[0] = particles[i];
					contact.particles[1] = particles[j];
					contact.restitution = 1;
					contact.penetration = maxDistance - distance;
					contact.normal = (particles[i]->getPosition() - particles[j]->getPosition()).normalized();
					contacts.push_back(contact);
				}
			}
		}
	}
}