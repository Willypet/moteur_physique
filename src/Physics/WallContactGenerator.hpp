#pragma once
#include "ParticleContactGenerator.hpp"
#include "Plane.hpp"
#include <vector>

namespace Physics {
	class WallContactGenerator : public ParticleContactGenerator
	{
	public:
		std::vector<Particule*> particles;
		Plane wall;
		void addContact(std::vector<ParticleContact>& contacts) const;
	};
}