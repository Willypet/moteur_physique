#pragma once

#include "Rigidbody.hpp"

namespace Physics {
	class RigidbodyContact {
	public:
		Rigidbody* bodies[2];

		//Coefficient d'elasticité entre 0 et 1
		float restitution;

		//Interpenetration du contact
		float penetration;

		Vecteur3D contactPoint;

		Vecteur3D normal;

		float computeVelocity() const;

		void resolveVelocity(float duration);

		void resolveInterpenetration(float duration);
	};
}