#pragma once
#include "Vecteur3D.hpp"
#include "PrimitiveCollider.hpp"
#include "RigidbodyContact.hpp"
#include <vector>

namespace Physics {
	class Octree {
	public:
		Vecteur3D center;
		float halfSize;
		int minCapacity;
		int maxDepth;
		std::vector<PrimitiveCollider> values;
		Octree* children[8];

		Octree(Vecteur3D center, float halfSize, int capacity, int depth);
		void insertCollider(PrimitiveCollider &value);
		void checkCollisions(std::vector<RigidbodyContact> &contacts);

	private:
		void checkBodyCollision(const PrimitiveCollider& value, std::vector<RigidbodyContact>& contacts);
		void generateContact(const PrimitiveCollider& col1, const PrimitiveCollider& col2, std::vector<RigidbodyContact> &contacts);
	};
}