#pragma once

#ifndef PARTICLE_DRAG_HPP
#define PARTICLE_DRAG_HPP

#include "ParticleForceGenerator.hpp"

namespace Physics {
    class ParticleDrag : public ParticleForceGenerator {
        private:
            float m_k1, m_k2;
    public:
        // TODO
        ParticleDrag(float m_k1, float m_k2);
        void UpdateForce(Particule* Particule, float duration);
    };
} // namespace Physics

#endif // PARTICLE_DRAG_HPP