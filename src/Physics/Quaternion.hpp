#pragma once

#include "Vecteur3D.hpp"

namespace Physics {
	class Quaternion {
	public:
		Quaternion(float w, float i, float j, float k);
		Quaternion();

		void Normalized();
		void RotateByVector(const Vecteur3D& vector);
		void UpdateByAngularVelocity(const Vecteur3D vector, const float duration = 0.1f);

		Quaternion operator*=(const Quaternion& other);
		Quaternion operator*=(const float& f);
		Quaternion operator+=(const Quaternion& other);

		float w, i, j, k;		
	};
}