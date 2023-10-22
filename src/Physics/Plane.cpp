#include "Plane.hpp"

namespace Physics {
	Plane::Plane(Vecteur3D normal, Vecteur3D point) {
		this->normal = normal.normalized();
		this->point = point;
	}

	float Plane::SignedDistance(Vecteur3D point) const {
		return Vecteur3D::dot(normal, point - this->point);
	}

	const Vecteur3D Plane::getNormal() const {
		return normal;
	}
}