#pragma once
#include "ParticleContactGenerator.hpp"
#include<vector>

namespace Physics {
	class NaiveParticleCollisionGenerator : public ParticleContactGenerator {
	public:
		std::vector<Particule*> particles;
		void addContact(std::vector<ParticleContact> &contacts) const;
	};
}