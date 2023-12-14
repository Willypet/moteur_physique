#pragma once

#include "PrimitiveCollider.hpp"

namespace Physics
{
	class BoxCollider : public PrimitiveCollider {
	public:
		Vecteur3D halfsize;
		Vecteur3D getHalfSize() override;
		void generateContact(const PrimitiveCollider& other, std::vector<RigidbodyContact>& contacts) const override;
	};
}