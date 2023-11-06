#pragma once

#include "Vecteur3D.hpp"

namespace Physics {
	class Quaternion {
	public:
		Quaternion(float w, float i, float j, float k);
		Quaternion();

		void Normalized();
		void RotateByVector(const Vecteur3D& vector);
		void UpdateByAngularVelocity(const Vecteur3D vector);

		Quaternion operator*=(const Quaternion& other);
		Quaternion operator*=(const float& f);
		Quaternion operator+=(const Quaternion& other);

	private:
		float w, i, j, k;
	};
}