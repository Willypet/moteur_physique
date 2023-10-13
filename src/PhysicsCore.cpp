#include "PhysicsCore.hpp"

namespace Physics {
	void PhysicsCore::UpdateAll(const float duration) {
		for (const auto & [force, particules] : forces) {
			for (const Particule& particule : particules) {
				force.UpdateForce(particule, duration);
			}
		}
	}
}