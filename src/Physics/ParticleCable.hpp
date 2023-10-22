#pragma once
#include "ParticleLink.hpp"

namespace Physics {
	class ParticleCable : public ParticleLink
	{
	public:
		ParticleCable(Particule* _particles[2], float maxLength, float restitution);
		void addContact(std::vector<ParticleContact>& contacts) const;

	private:
		float maxLength;
		float restitution;
	};
}