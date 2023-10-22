#pragma once
#include "ParticleLink.hpp"

namespace Physics {
	class ParticleRod : public ParticleLink {
	public:
		ParticleRod(Particule* _particles[2], float length);

		void addContact(std::vector<ParticleContact>& contacts) const;

	private:
		float length;
	};
}