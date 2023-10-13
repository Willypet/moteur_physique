#pragma once

#ifndef PARTICLE_FORCE_GENERATOR_HPP
#define PARTICLE_FORCE_GENERATOR_HPP

#include "Particule.hpp"

namespace Physics {
    class ParticleForceGenerator {
        public:
            virtual void UpdateForce(const Particule& particule, float duration) const = 0;
    };
} // namespace Physics

#endif // PARTICLE_FORCE_GENERATOR_HPP