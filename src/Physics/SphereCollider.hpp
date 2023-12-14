#pragma once

#include "PrimitiveCollider.hpp"

namespace Physics
{
	class SphereCollider : public PrimitiveCollider	{
	public:
		float radius;
		SphereCollider(Rigidbody* body, float radius);
		Vecteur3D getHalfSize() const override;
		void generateContact(const PrimitiveCollider& other, std::vector<RigidbodyContact>& contacts) const override;
		Matrix3 getInverseInertiaTensor() const override;
	};
}