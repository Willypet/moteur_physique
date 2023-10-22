#pragma once
#include "ParticleLink.hpp"

namespace Physics {
	class ParticleCable : public ParticleLink
	{
	public:
		float maxLength;
		float restitution;

		void addContact(std::vector<ParticleContact>& contacts) const;
	};
}