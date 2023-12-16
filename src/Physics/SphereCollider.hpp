#pragma once

#include "Rigidbody.hpp"

namespace Physics
{
	class SphereCollider : public PrimitiveCollider	{
	public:
		float radius;
		SphereCollider(Rigidbody* body, float radius);
		void generateContact(const PrimitiveCollider* other, std::vector<RigidbodyContact>& contacts) const override;
	};
}