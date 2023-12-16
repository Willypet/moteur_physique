#pragma once
#include "Vecteur3D.hpp"
#include "Rigidbody.hpp"
#include <vector>

namespace Physics {
	class Octree {
	public:
		Vecteur3D center;
		float halfSize;
		int minCapacity;
		int maxDepth;
		std::vector<PrimitiveCollider*> values;
		Octree* children[8];

		Octree();
		Octree(Vecteur3D center, float halfSize, int capacity, int depth);
		void insertCollider(PrimitiveCollider* value);
		void checkCollisions(std::vector<RigidbodyContact> &contacts);

	private:
		void checkBodyCollision(const PrimitiveCollider* value, std::vector<RigidbodyContact>& contacts);
	};
}