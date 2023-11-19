#include "GravityForceGenerator.hpp"

namespace Physics {
	GravityForceGenerator::GravityForceGenerator(const Vecteur3D& m_gravity) : m_gravity(m_gravity){}

	void GravityForceGenerator::UpdateForce(Rigidbody* rigidBody) {
		rigidBody->AddForce(rigidBody->getMass() * m_gravity);
	}
}