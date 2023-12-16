#include "RigidPhysicsCore.hpp"

namespace Physics {

	void RigidPhysicsCore::UpdateAll(const float duration, const unsigned int substep) {
		float timestep = duration / substep;
		for (unsigned int i = 0; i < substep; i++) {
			ApplyForces();
			UpdateRigidBodies(timestep);
			std::vector<RigidbodyContact> contacts = GenerateContacts();
			contactResolver.resolveContacts(contacts, timestep);
			ResetRigidBodiesAcc();
		}
	}

	std::vector<RigidbodyContact> RigidPhysicsCore::GenerateContacts() {
		std::vector<RigidbodyContact> res;
		tree = new Octree(Vecteur3D(0, 0, 0), 1000.f, 2, 8);
		if (collidersInSim.size() == 0) {
			return res;
		}
		for (int i = 0; i < collidersInSim.size(); i++) {
			collidersInSim[i]->rigidbody = rigidBodiesInSim[i];
			tree->insertCollider(collidersInSim[i]);
		}
		tree->checkCollisions(res);
		return res;
	}

	void RigidPhysicsCore::ApplyForces() {
		for (auto iter_forces = forces.begin(); iter_forces != forces.end();) {
			auto& [force, bodies] = *iter_forces;
			if (force == nullptr) {
				iter_forces = forces.erase(iter_forces);
				continue;
			}
			for (auto iter_bodies = bodies.begin(); iter_bodies != bodies.end();) {
				Rigidbody* body = *iter_bodies;
				if (body == nullptr) {
					iter_bodies = bodies.erase(iter_bodies);
					continue;
				}
				force->UpdateForce(body);
				iter_bodies++;
			}
			iter_forces++;
		}
	}

	void RigidPhysicsCore::UpdateRigidBodies(const float duration) {
		for (Rigidbody* body : rigidBodiesInSim) {
			body->Integrate(duration);
		}
	}

	void RigidPhysicsCore::ResetRigidBodiesAcc() {
		for (Rigidbody* body : rigidBodiesInSim) {
			body->ClearAccumulator();
		}
	}

	void RigidPhysicsCore::AddForce(ForceGenerator* force, Rigidbody* body) {
		if (auto elem = forces.find(force); elem != forces.end()) {
			std::vector<Rigidbody*> bodies = elem->second;
			bodies.insert(bodies.end(), body);
		}
		else {
			forces.insert({ force, std::vector<Rigidbody*>({ body }) });
		}
	}

	void RigidPhysicsCore::AddForce(ForceGenerator* force, std::vector<Rigidbody*> bodies) {
		if (auto elem = forces.find(force); elem != forces.end()) {
			std::vector<Rigidbody*> existingBodies = elem->second;
			existingBodies.insert(existingBodies.end(), bodies.begin(), bodies.end());
		}
		else {
			forces.insert({ force, std::vector<Rigidbody*>(bodies) });
		}
	}

	void RigidPhysicsCore::AddCollider(PrimitiveCollider* col) {
		//collidersInSim.insert(col);
	}

	void RigidPhysicsCore::AddRigidBody(Rigidbody* body) {
		rigidBodiesInSim.push_back(body);
		collidersInSim.push_back(body->getCollider());
	}

	RigidPhysicsCore::~RigidPhysicsCore() {
		for (auto& [force, bodies] : forces) {
			delete force;
		}
	}
}