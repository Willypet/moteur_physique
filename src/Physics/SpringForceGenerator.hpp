#pragma once
#include "ForceGenerator.hpp"

namespace Physics {
	class SpringForceGenerator : public ForceGenerator {
	private:
		Vecteur3D m_bodyAnchor;

		Rigidbody* m_otherBody = nullptr;
		Vecteur3D m_otherBodyAnchor;

		float m_k;
		float m_restLength;

	public:
		SpringForceGenerator(const Vecteur3D& bodyAnchor, Rigidbody* otherBody, const Vecteur3D& otherBodyAnchor, float k, float restLength);
		void UpdateForce(Rigidbody* rigidBody) override;
	};
}