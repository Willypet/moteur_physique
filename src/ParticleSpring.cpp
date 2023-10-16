#include "ParticleSpring.hpp"
#include "ParticleSpring.hpp"

namespace Physics {
    ParticleSpring::ParticleSpring(Particule *m_other, float m_k, float m_restLength)
        : m_other(m_other),
        m_k(m_k),
        m_restLength(m_restLength) {}

    void ParticleSpring::UpdateForce(Particule *particule, float duration) {
        auto d = m_other->getPosition() - particule->getPosition();
        auto norme_d = sqrt(pow(d.x, 2) + pow(d.y, 2) + pow(d.z, 2));
        auto force = m_k * (norme_d - m_restLength) * d.normalized();
        particule->setAcceleration(particule->getAcceleration() + force / particule->getMasse());
        m_other->setAcceleration(m_other->getAcceleration() - force / m_other->getMasse());
    }
}