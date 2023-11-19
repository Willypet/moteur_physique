#pragma once

#include "RigidBody.hpp"
#include "ForceGenerator.hpp"
#include <map>
#include<vector>
#include<set>

namespace Physics {
	class RigidPhysicsCore {
	public:
		void UpdateAll(const float duration, const unsigned int substep);

		void AddForce(ForceGenerator* force, Rigidbody* rigidBody);

		void AddForce(ForceGenerator* force, std::vector<Rigidbody*> rigidBodies);

		void AddRigidBody(Rigidbody* rigidBody);


		~RigidPhysicsCore();
	private:
		void ApplyForces();
		void UpdateRigidBodies(const float duration);
		void ResetRigidBodiesAcc();
		std::map<ForceGenerator*, std::vector<Rigidbody*>> forces;
		std::set<Rigidbody*> rigidBodiesInSim;
	};
}
