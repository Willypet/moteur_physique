#pragma once

#ifndef PARTICLE_FORCE_GENERATOR_HPP
#define PARTICLE_FORCE_GENERATOR_HPP

#include "Particule.hpp"

namespace Physics {
    class ParticleForceGenerator {
        public:
            virtual void UpdateForce(Particule* particule, float duration) = 0;
    };
} // namespace Physics

#endif // PARTICLE_FORCE_GENERATOR_HPP