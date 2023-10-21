#pragma once
#include "ParticleContact.hpp"
#include<vector>

namespace Physics {
	class ParticleContactResolver {
	public:
		ParticleContactResolver();
		ParticleContactResolver(unsigned int maxIterations);

		void setMaxIterations(unsigned int newMax);

		void resolveContacts(std::vector<ParticleContact> contacts, float duration);

	private:
		unsigned int maxIterations;

		unsigned int currentIteration;
	};
}