#include "ParticleGravity.hpp"

namespace Physics {
    ParticleGravity::ParticleGravity(const Vecteur3D& m_gravity) {
        this->m_gravity = m_gravity;
    }

    void ParticleGravity::UpdateForce(Particule* particule, float duration) const{
        particule->setAcceleration(particule->getAcceleration() + m_gravity);
    }
}