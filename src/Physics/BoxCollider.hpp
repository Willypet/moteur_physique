#pragma once

#include "PrimitiveCollider.hpp"

namespace Physics
{
	class BoxCollider : public PrimitiveCollider {
	public:
		Vecteur3D halfsize;
		Vecteur3D getHalfSize() override;
		BoxCollider(Rigidbody* body, Vecteur3D halfsize);
		void generateContact(const PrimitiveCollider& other, std::vector<RigidbodyContact>& contacts) const override;
		Matrix3 getInverseInertiaTensor() const override;
	};
}