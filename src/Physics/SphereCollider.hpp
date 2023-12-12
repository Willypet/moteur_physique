#pragma once

#include "PrimitiveCollider.hpp"

namespace Physics
{
	class SphereCollider : public PrimitiveCollider	{
	public:
		float radius;
	};
}