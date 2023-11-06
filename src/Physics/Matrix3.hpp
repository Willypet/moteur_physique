#pragma once

#include "Vecteur3D.hpp"
#include "Quaternion.hpp"

namespace Physics {
	class Matrix3 {
	public :
		Matrix3();
		Matrix3(float a, float b, float c, float d, float e, float f, float g, float h, float i);

		Matrix3 operator*(const Matrix3& other) const;
		Vecteur3D operator*(const Vecteur3D& vector) const;

		Matrix3 Inverse() const;
		Matrix3 Transpose() const;

		void SetOrientation(const Quaternion& q);

	private :
		float value[3][3];
	};
}