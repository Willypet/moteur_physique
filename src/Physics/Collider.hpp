#pragma once
#include "Matrix3.hpp"

namespace Physics {
	class Collider {
	protected:
		Matrix3 inverseInertiaTensor;
	public:
		virtual Matrix3 GetInverseInertiaTensor() const { return inverseInertiaTensor; }
	};
}