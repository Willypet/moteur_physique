#pragma once

#include "PrimitiveCollider.hpp"

namespace Physics
{
	class SphereCollider : public PrimitiveCollider	{
	public:
		float radius;
		Vecteur3D getHalfSize() override;
		void generateContact(const PrimitiveCollider& other, std::vector<RigidbodyContact>& contacts) const override;
	};
}