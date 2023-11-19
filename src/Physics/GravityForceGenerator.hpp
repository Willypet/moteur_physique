#pragma once
#include "ForceGenerator.hpp"

namespace Physics{
	class GravityForceGenerator : public ForceGenerator
	{
	private:
		Vecteur3D m_gravity;
	public:
		GravityForceGenerator(const Vecteur3D& m_gravity);
		void UpdateForce(Rigidbody* rigidBody) override;
	};
}
