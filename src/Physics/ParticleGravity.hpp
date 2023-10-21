#pragma once

#ifndef PARTICLE_GRAVITY_HPP
#define PARTICLE_GRAVITY_HPP

//#include "Vecteur3D.hpp"
#include "ParticleForceGenerator.hpp"

namespace Physics {
    class ParticleGravity : public ParticleForceGenerator {
        private:
            Vecteur3D m_gravity;
        public:
            ParticleGravity(const Vecteur3D& m_gravity);
            void UpdateForce(Particule* particule, float duration);
    };
} // namespace Physics

#endif // PARTICLE_GRAVITY_HPP