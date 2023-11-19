#include "AnchoredSpringForceGenerator.hpp"

namespace Physics {
    AnchoredSpringForceGenerator::AnchoredSpringForceGenerator(Vecteur3D m_worldAnchor, Vecteur3D m_bodyAnchor, float m_k, float m_restLength)
        : m_worldAnchor(m_worldAnchor),
        m_bodyAnchor(m_bodyAnchor),
        m_k(m_k),
        m_restLength(m_restLength) {}

    void AnchoredSpringForceGenerator::UpdateForce(Rigidbody* body) {
        auto d = m_worldAnchor - (body->getPosition() + m_bodyAnchor);
        auto norme_d = sqrt(pow(d.x, 2) + pow(d.y, 2) + pow(d.z, 2));
        auto force = m_k * (norme_d - m_restLength) * d.normalized();
        body->AddForceAtBodyPoint(force, m_bodyAnchor);
    }
}