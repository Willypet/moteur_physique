#pragma once

#ifndef PARTICLE_ANCHORED_SPRING_HPP
#define PARTICLE_ANCHORED_SPRING_HPP

#include "ParticleForceGenerator.hpp"

namespace Physics {
    class ParticleAnchoredSpring : public ParticleForceGenerator {
        private:
            Vecteur3D m_anchor;
            float m_k;
            float m_restLength;
        public:
            ParticleAnchoredSpring(Vecteur3D m_anchor, float m_k, float m_restLength);
            void UpdateForce(Particule* particule, float duration);
    };
} // namespace Physics


#endif // PARTICLE_ANCHORED_SPRING_HPP