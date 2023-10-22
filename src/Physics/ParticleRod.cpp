#include "ParticleRod.hpp"

namespace Physics {
	void ParticleRod::addContact(std::vector<ParticleContact>& contacts) const {
		float currentLength = getLength();
		if (abs(currentLength - length) < 10e-6) {
			return;
		}

		ParticleContact contact;
		contact.particles[0] = particles[0];
		contact.particles[1] = particles[1];
		Vecteur3D normal = particles[0]->getPosition() - particles[1]->getPosition();
		normal.normalize();
		int sign = currentLength > length ? 1 : -1;
		contact.normal = sign * normal;
		contact.penetration = sign * (currentLength - length);
		contact.restitution = 0;
		contacts.push_back(contact);
	}
}