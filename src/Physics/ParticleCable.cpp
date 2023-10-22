#include "ParticleCable.hpp"

namespace Physics {
	void ParticleCable::addContact(std::vector<ParticleContact>& contacts) const {
		float length = getLength();
		if (length < maxLength) {
			return;
		}
		ParticleContact contact;
		contact.particles[0] = particles[0];
		contact.particles[1] = particles[1];
		contact.normal = (particles[0]->getPosition() - particles[1]->getPosition());
		contact.normal.normalize();
		contact.penetration = length - maxLength;
		contact.restitution = restitution;
	}
}