#pragma once

#include "Vecteur3D.hpp"
#include "Quaternion.hpp"

namespace Physics {
	class Matrix34 {

	public:
		Matrix34();
		Matrix34(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l);

		Matrix34 operator*(const Matrix34& other);
		Vecteur3D operator*(const Vecteur3D& other);

		Matrix34 Inverse();
		void SetOrientationAndPosition(const Quaternion& q, const Vecteur3D& v);
		Vecteur3D TransformPosition(const Vecteur3D v) const;
		Vecteur3D TransformDirection(const Vecteur3D& v);
	
	private:
		float value[3][4];
	};
}