#include "WallContactGenerator.hpp"

namespace Physics {
	void WallContactGenerator::addContact(std::vector<ParticleContact>& contacts) const {
		for (auto& particle : particles) {
			float distance = wall.SignedDistance(particle->getPosition());
			if (abs(distance) <= particle->getRadius()) {
				ParticleContact contact;
				contact.particles[0] = particle;
				contact.normal = wall.getNormal();
				contact.restitution = 1;
				contact.penetration = particle->getRadius() - distance;
				contacts.push_back(contact);
			}
		}
	}
}