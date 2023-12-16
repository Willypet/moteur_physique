#pragma once

#include "Rigidbody.hpp"

namespace Physics
{
	class BoxCollider : public PrimitiveCollider {
	public:
		BoxCollider(Vecteur3D halfsize);
		BoxCollider(Rigidbody* body, Vecteur3D halfsize);
		void generateContact(const PrimitiveCollider* other, std::vector<RigidbodyContact>& contacts) const override;
	};
}