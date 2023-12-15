#include "Octree.hpp"
#include "SphereCollider.hpp"

#include<typeinfo>

namespace Physics {

	Octree::Octree() {
		Octree(Vecteur3D(0, 0, 0), 1000, 2, 8);
	}

	Octree::Octree(Vecteur3D center, float halfSize, int capacity, int depth) :
	center(center),
	halfSize(halfSize),
	minCapacity(capacity),
	maxDepth(depth),
	children(){}

	void Octree::insertCollider(PrimitiveCollider* value) {

		if (values.size() < minCapacity || maxDepth == 0) {
			values.push_back(value);
			return;
		}

		int childIndex = 0;

		Vecteur3D colliderCenter = value->rigidbody->getPosition() + value->offset.TransformDirection(Vecteur3D(0, 0, 0));
		Vecteur3D colSize = value->getHalfSize();

		float offsetX, offsetY, offsetZ;
		offsetX = colliderCenter.x - center.x;
		if (abs(offsetX) < colSize.x) {
			values.push_back(value);
			return;
		}

		offsetY = colliderCenter.y - center.y;
		if (abs(offsetY) < colSize.y) {
			values.push_back(value);
			return;
		}

		offsetZ = colliderCenter.z - center.z;
		if (abs(offsetZ) < colSize.z) {
			values.push_back(value);
			return;
		}
		
		//La forme loge entièrement dans un octant
		if (offsetX > 0.f) childIndex += 1;
		if (offsetY > 0.f) childIndex += 2;
		if (offsetZ > 0.f) childIndex += 4;

		if (children[childIndex] == nullptr) {
			float childSize = halfSize / 2;
			Vecteur3D childOffset = Vecteur3D(childSize, childSize, childSize);
			children[childIndex] = new Octree(Vecteur3D(center + childOffset), childSize, minCapacity, maxDepth - 1);
		}
		children[childIndex]->insertCollider(value);
	}

	void Octree::checkCollisions(std::vector<RigidbodyContact> &contacts) {
		for (int i = 0; i < values.size() - 1; i++) {
			//Test avec la cellule courante
			for (int j = i + 1; j < values.size(); j++) {
				values[i]->generateContact(values[j], contacts);
			}
			//Test avec les enfants
			for(Octree * child : children) {
				if (child == nullptr) continue;
				child->checkBodyCollision(values[i], contacts);
			}
		}
		for (Octree* child : children) {
			if (child == nullptr) continue;
			child->checkCollisions(contacts);
		}
	}

	void Octree::checkBodyCollision(const PrimitiveCollider* value, std::vector<RigidbodyContact>& contacts) {
		for (int i = 0; i < values.size() - 1; i++) {
			//Test avec la cellule courante
			values[i]->generateContact(value, contacts);
		}
		for (Octree* child : children) {
			if (child == nullptr) continue;
			child->checkBodyCollision(value, contacts);
		}
	}
}