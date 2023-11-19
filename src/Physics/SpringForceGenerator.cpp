#include "SpringForceGenerator.hpp"

namespace Physics {
	SpringForceGenerator::SpringForceGenerator(const Vecteur3D& bodyAnchor, Rigidbody* otherBody,
		const Vecteur3D& otherBodyAnchor, float k, float restLength) :
		m_bodyAnchor(bodyAnchor),
		m_otherBody(otherBody),
		m_otherBodyAnchor(otherBodyAnchor),
		m_k(k),
		m_restLength(restLength){}

	void SpringForceGenerator::UpdateForce(Rigidbody* rigidBody) {
		auto d = m_otherBody->getPosition() + m_otherBodyAnchor - (rigidBody->getPosition() + m_bodyAnchor);
		auto norme_d = sqrt(pow(d.x, 2) + pow(d.y, 2) + pow(d.z, 2));
		auto force = m_k * (norme_d - m_restLength) * d.normalized();
		rigidBody->AddForceAtBodyPoint(force, m_bodyAnchor);
		m_otherBody->AddForceAtBodyPoint(-1 * force, m_otherBodyAnchor);
	}

}