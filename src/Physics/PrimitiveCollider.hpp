#pragma once

#include "Rigidbody.hpp"
#include "RigidbodyContact.hpp"
#include "Matrix34.hpp"
#include <vector>

namespace Physics
{
	class PrimitiveCollider
	{
	public:
		Rigidbody* rigidbody;
		Matrix34 offset;
		virtual Vecteur3D getHalfSize() = 0;
		virtual void generateContact(const PrimitiveCollider& other, std::vector<RigidbodyContact>& contacts) const = 0;
	};
}