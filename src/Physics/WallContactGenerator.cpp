#include "WallContactGenerator.hpp"

namespace Physics {
	WallContactGenerator::WallContactGenerator(Vecteur3D normal, Vecteur3D point): wall(normal, point){}

	void WallContactGenerator::addContact(std::vector<ParticleContact>& contacts) const {
		for (auto& particle : particles) {
			float distance = wall.SignedDistance(particle->getPosition());
			if (abs(distance) <= particle->getRadius()) {
				ParticleContact contact;
				contact.particles[0] = particle;
				contact.particles[1] = nullptr;
				contact.normal = wall.getNormal();
				contact.restitution = restitution;
				contact.penetration = particle->getRadius() - distance;
				contacts.push_back(contact);
			}
		}
	}
}