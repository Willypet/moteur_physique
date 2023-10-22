#pragma once
#include "ParticleLink.hpp"

namespace Physics {
	class ParticleRod : public ParticleLink {
	public:
		float length;
		void addContact(std::vector<ParticleContact>& contacts) const;
	};
}