#pragma once
#include "ParticleContactGenerator.hpp"

namespace Physics {
	class ParticleLink : public ParticleContactGenerator
	{
	public:
		virtual void addContact(std::vector<ParticleContact>& contacts) const = 0;
		
	protected:
		
		Particule* particles[2];
		float getLength() const;
	};
}