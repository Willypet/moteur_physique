#include "ParticleCable.hpp"

namespace Physics {
	ParticleCable::ParticleCable(Particule* _particles[2], float maxLength, float restitution) : maxLength{maxLength}, restitution{restitution}
	{
		particles[0] = _particles[0];
		particles[1] = _particles[1];
	}

	void ParticleCable::addContact(std::vector<ParticleContact>& contacts) const {
		float length = getLength();
		if (length < maxLength) {
			return;
		}
 		ParticleContact contact;
		contact.particles[0] = particles[0];
		contact.particles[1] = particles[1];
		contact.normal = (particles[1]->getPosition() - particles[0]->getPosition());
		contact.normal.normalize();
		contact.penetration = length - maxLength;
		contact.restitution = restitution;
		contacts.push_back(contact);
	}
}