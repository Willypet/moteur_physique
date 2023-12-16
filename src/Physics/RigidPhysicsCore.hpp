#pragma once

#include "RigidBody.hpp"
#include "ForceGenerator.hpp"
#include "RigidbodyContactResolver.hpp"
#include "Octree.hpp"
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

		void AddCollider(PrimitiveCollider* col);

		~RigidPhysicsCore();
	private:
		void ApplyForces();
		void UpdateRigidBodies(const float duration);
		void ResetRigidBodiesAcc();
		std::vector<RigidbodyContact> GenerateContacts();
		Octree tree;
		std::map<ForceGenerator*, std::vector<Rigidbody*>> forces;
		std::vector<Rigidbody*> rigidBodiesInSim;
		std::vector<PrimitiveCollider*> collidersInSim;
		RigidbodyContactResolver contactResolver;
	};
}
