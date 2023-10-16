#include "ParticleDrag.hpp"

namespace Physics {
    ParticleDrag::ParticleDrag(float m_k1, float m_k2)
        : m_k1(m_k1),
        m_k2(m_k2) {}

    void ParticleDrag::UpdateForce(Particule *particule, float duration) const {
        auto vitesse = particule->getVitesse();
        auto norme_vitesse = sqrt(pow(vitesse.x, 2) + pow(vitesse.y, 2) + pow(vitesse.z, 2));
        auto force = vitesse.normalized() * (m_k1 * norme_vitesse + m_k2 * pow(norme_vitesse, 2));
        particule->setAcceleration(particule->getAcceleration() - force / particule->getMasse());
    }
}