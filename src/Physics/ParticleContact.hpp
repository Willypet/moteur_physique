#pragma once
#include "Particule.hpp"

namespace Physics {
	class ParticleContact {
	public:
		Particule* particles[2];

		//Coefficient d'elasticité entre 0 et 1
		float restitution;

		//Interpenetration du contact
		float penetration;

		Vecteur3D normal;

		void resolve(float duration);

		float computeVelocity() const;

	private:
		void resolveVelocity(float duration);

		void resolveInterpenetration(float duration);
	};
}