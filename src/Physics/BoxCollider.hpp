#pragma once

#include "PrimitiveCollider.hpp"

namespace Physics
{
	class BoxCollider : public PrimitiveCollider {
	public:
		Vecteur3D halfsize;
	};
}