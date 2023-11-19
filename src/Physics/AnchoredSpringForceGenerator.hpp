#pragma once

#include "ForceGenerator.hpp"

namespace Physics {
    class AnchoredSpringForceGenerator : public ForceGenerator {
    private:
        Vecteur3D m_worldAnchor;
        Vecteur3D m_bodyAnchor;
        float m_k;
        float m_restLength;
    public:
        AnchoredSpringForceGenerator(Vecteur3D m_worldAnchor, Vecteur3D m_bodyAnchor, float m_k, float m_restLength);
        void UpdateForce(Rigidbody* body);
    };
}