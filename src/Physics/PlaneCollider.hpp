#pragma once

#include "Rigidbody.hpp"

namespace Physics
{
	class PlaneCollider : public PrimitiveCollider {
	public:
		Vecteur3D normal;
		float offset;
		Vecteur3D getHalfSize() const override;
		void generateContact(const PrimitiveCollider* other, std::vector<RigidbodyContact>& contacts) const override;
	};
}