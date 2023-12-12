#pragma once

#include "PrimitiveCollider.hpp"

namespace Physics
{
	class PlaneCollider : public PrimitiveCollider {
	public:
		Vecteur3D normal;
		float offset;
	};
}