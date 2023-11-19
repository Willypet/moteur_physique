#pragma once
#include "Collider.hpp"

namespace Physics {
	class Box : public Collider {
	private:
		Vecteur3D halfExtents;
		Vecteur3D center;
	public:
		Box(float mass, Vecteur3D center, Vecteur3D halfExtents);
		Matrix3 GetInverseInertiaTensor() const;
	};
}