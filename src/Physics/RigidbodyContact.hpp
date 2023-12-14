#pragma once

#include "PrimitiveCollider.hpp"

namespace Physics {
	class RigidbodyContact {
	public:
		PrimitiveCollider* bodies[2];

		//Coefficient d'elasticité entre 0 et 1
		float restitution;

		//Interpenetration du contact
		float penetration;

		Vecteur3D contactPoint;

		Vecteur3D normal;

		void resolve(float duration);

		float computeVelocity() const;

	private:
		void resolveVelocity(float duration);

		void resolveInterpenetration(float duration);
	};
}