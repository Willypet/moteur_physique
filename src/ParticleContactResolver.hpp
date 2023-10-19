#pragma once
#include "ParticleContact.hpp"

namespace Physics {
	class ParticleContactResolver {
	public:
		ParticleContactResolver(int maxIterations);

		void setMaxIterations(int newMax);

		void resolveContacts(ParticleContact* contacts, int contactsNumber, float duration);

	private:
		int maxIterations;

		int currentIteration;
	};
}