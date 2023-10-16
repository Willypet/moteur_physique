#include "ParticleAnchoredSpring.hpp"

namespace Physics {
    ParticleAnchoredSpring::ParticleAnchoredSpring(Vecteur3D m_anchor, float m_k, float m_restLength)
        : m_anchor(m_anchor),
        m_k(m_k),
        m_restLength(m_restLength) {}

    void ParticleAnchoredSpring::UpdateForce(Particule *particule, float duration) {
        auto d = m_anchor - particule->getPosition();
        auto norme_d = sqrt(pow(d.x, 2) + pow(d.y, 2) + pow(d.z, 2));
        auto force = m_k * (norme_d - m_restLength) * d.normalized();
        particule->setAcceleration(particule->getAcceleration() - force / particule->getMasse());
    }
}
