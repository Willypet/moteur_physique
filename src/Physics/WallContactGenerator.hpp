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
		float restitution;
		WallContactGenerator(Vecteur3D normal, Vecteur3D point);
		void addContact(std::vector<ParticleContact>& contacts) const;
	};
}