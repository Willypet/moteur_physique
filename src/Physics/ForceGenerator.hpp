#pragma once
#include "Rigidbody.hpp"

namespace Physics {
    class ForceGenerator {
    public:
        virtual void UpdateForce(Rigidbody* particule) = 0;
    };
}
