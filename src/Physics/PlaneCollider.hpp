#pragma once

#include "Rigidbody.hpp"

namespace Physics
{
	class PlaneCollider : public PrimitiveCollider {
	public:
		Vecteur3D normal;
		float offset;

		PlaneCollider(Vecteur3D normal, float offset, Rigidbody* body);
		void generateContact(const PrimitiveCollider* other, std::vector<RigidbodyContact>& contacts) const override;
	};
}