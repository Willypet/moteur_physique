#pragma once

#ifndef PARTICLE_SPRING_HPP
#define PARTICLE_SPRING_HPP

#include "ParticleForceGenerator.hpp"

namespace Physics {

    class ParticleSpring : public ParticleForceGenerator {
        private:
            Particule* m_other;
            float m_k;
            float m_restLength;
        public:
            ParticleSpring(Particule* m_other, float m_k, float m_restLength);
            void UpdateForce(Particule* particule, float duration);
    };
} // namespace Physics

#endif // PARTICLE_SPRING_HPP
