#pragma once
#include "Vecteur3D.hpp"

namespace Physics {
	class Plane {
	public:
		Plane(Vecteur3D normal, Vecteur3D point);
		float SignedDistance(Vecteur3D point) const;
		const Vecteur3D getNormal() const;
	private:
		Vecteur3D normal;
		Vecteur3D point;
	};
}