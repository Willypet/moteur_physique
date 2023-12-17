#include "Matrix3.hpp"
#include <iostream>

namespace Physics {
	Matrix3::Matrix3()
	{
		Matrix3(0, 0, 0, 0, 0, 0, 0, 0, 0);
	}

	Matrix3::Matrix3(float a, float b, float c, float d, float e, float f, float g, float h, float i)
	{
		value[0][0] = a;
		value[0][1] = b;
		value[0][2] = c;
		value[1][0] = d;
		value[1][1] = e;
		value[1][2] = f;
		value[2][0] = g;
		value[2][1] = h;
		value[2][2] = i;
	}

	Matrix3 Matrix3::operator*(const Matrix3& other) const
	{
		return Matrix3(
			value[0][0] * other.value[0][0] + value[0][1] * other.value[1][0] + value[0][2] * other.value[2][0],
			value[0][0] * other.value[0][1] + value[0][1] * other.value[1][1] + value[0][2] * other.value[2][1],
			value[0][0] * other.value[0][2] + value[0][1] * other.value[1][2] + value[0][2] * other.value[2][2],

			value[1][0] * other.value[0][0] + value[1][1] * other.value[1][0] + value[1][2] * other.value[2][0],
			value[1][0] * other.value[0][1] + value[1][1] * other.value[1][1] + value[1][2] * other.value[2][1],
			value[1][0] * other.value[0][2] + value[1][1] * other.value[1][2] + value[1][2] * other.value[2][2],

			value[2][0] * other.value[0][0] + value[2][1] * other.value[1][0] + value[2][2] * other.value[2][0],
			value[2][0] * other.value[0][1] + value[2][1] * other.value[1][1] + value[2][2] * other.value[2][1],
			value[2][0] * other.value[0][2] + value[2][1] * other.value[1][2] + value[2][2] * other.value[2][2]);
	}

	Vecteur3D Matrix3::operator*(const Vecteur3D& vector) const
	{
		return Vecteur3D(
			value[0][0] * vector.x + value[0][1] * vector.y + value[0][2] * vector.z,
			value[1][0] * vector.x + value[1][1] * vector.y + value[1][2] * vector.z,
			value[2][0] * vector.x + value[2][1] * vector.y + value[2][2] * vector.z);
	}

	Matrix3 Matrix3::Inverse() const
	{
		float det = value[0][0] * (value[1][1] * value[2][2] - value[1][2] * value[2][1])
			- value[0][1] * (value[1][0] * value[2][2] - value[1][2] * value[2][0])
			+ value[0][2] * (value[1][0] * value[2][1] - value[1][1] * value[2][0]);

		if (det == 0.0f) {
			return Matrix3(0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f);
		}

		float invDet = 1.0f / det;

		return Matrix3(
			(value[1][1] * value[2][2] - value[1][2] * value[2][1]) * invDet,
			(value[0][2] * value[2][1] - value[0][1] * value[2][2]) * invDet,
			(value[0][1] * value[1][2] - value[0][2] * value[1][1]) * invDet,

			(value[1][2] * value[2][0] - value[1][0] * value[2][2]) * invDet,
			(value[0][0] * value[2][2] - value[0][2] * value[2][0]) * invDet,
			(value[0][2] * value[1][0] - value[0][0] * value[1][2]) * invDet,

			(value[1][0] * value[2][1] - value[1][1] * value[2][0]) * invDet,
			(value[0][1] * value[2][0] - value[0][0] * value[2][1]) * invDet,
			(value[0][0] * value[1][1] - value[0][1] * value[1][0]) * invDet
		);
	}

	Matrix3 Matrix3::Transpose() const
	{
		return Matrix3(
			value[0][0],
			value[1][0], 
			value[2][0], 
			value[0][1], 
			value[1][1], 
			value[2][1], 
			value[0][2], 
			value[1][2], 
			value[2][2]);
	}

	void Matrix3::SetOrientation(const Quaternion& q)
	{
		
		value[0][0] = 1 - (2 * q.j * q.j + 2 * q.k * q.k);
		value[0][1] = 2 * q.i * q.j + 2 * q.k * q.w;
		value[0][2] = 2 * q.i * q.k - 2 * q.j * q.w;
		value[1][0] = 2 * q.i * q.j - 2 * q.k * q.w;
		value[1][1] = 1 - (2 * q.i * q.i + 2 * q.k * q.k);
		value[1][2] = 2 * q.j * q.k + 2 * q.i * q.w;
		value[2][0] = 2 * q.i * q.k + 2 * q.j * q.w;
		value[2][1] = 2 * q.j * q.k - 2 * q.i * q.w;
		value[2][2] = 1 - (2 * q.i * q.i + 2 * q.j * q.j);
		
	}

	void Matrix3::print() {
		std::cout << value[0][0] << ", " << value[0][1] << ", " << value[0][2] << std::endl;
		std::cout << value[1][0] << ", " << value[1][1] << ", " << value[1][2] << std::endl;
		std::cout << value[2][0] << ", " << value[2][1] << ", " << value[2][2] << std::endl;
	}
}