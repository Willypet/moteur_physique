#pragma once

#include "Rigidbody.hpp"
#include "Matrix34.hpp"

namespace Physics
{
	class PrimitiveCollider
	{
	public:
		Rigidbody* rigidbody;
		Matrix34 offset;
	};
}