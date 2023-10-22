#pragma once
#include "ParticleContactGenerator.hpp"

namespace Physics {
	class ParticleLink : public ParticleContactGenerator
	{
	public:
		Particule* particles[2];
		virtual void addContact(std::vector<ParticleContact>& contacts) const = 0;

	protected:
		float getLength() const;
	};
}