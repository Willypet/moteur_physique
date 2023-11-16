#include "Matrix34.hpp"

namespace Physics {

	Matrix34::Matrix34()
	{
		Matrix34(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	}

	Matrix34::Matrix34(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l)
	{
		value[0][0] = a;
		value[0][1] = b;
		value[0][2] = c;
		value[0][3] = d;
		value[1][0] = e;
		value[1][1] = f;
		value[1][2] = g;
		value[1][3] = h;
		value[2][0] = i;
		value[2][1] = j;
		value[2][2] = k;
		value[0][3] = l;
	}

	Matrix34 Physics::Matrix34::operator*(const Matrix34& other)
	{
		return Matrix34(
			value[0][0] * other.value[0][0] + value[0][1] * other.value[1][0] + value[0][2] * other.value[2][0],
			value[0][0] * other.value[0][1] + value[0][1] * other.value[1][1] + value[0][2] * other.value[2][1],
			value[0][0] * other.value[0][2] + value[0][1] * other.value[1][2] + value[0][2] * other.value[2][2],
			value[0][0] * other.value[0][3] + value[0][1] * other.value[1][3] + value[0][2] * other.value[2][3] + value[0][3],

			value[1][0] * other.value[0][0] + value[1][1] * other.value[1][0] + value[1][2] * other.value[2][0],
			value[1][0] * other.value[0][1] + value[1][1] * other.value[1][1] + value[1][2] * other.value[2][1],
			value[1][0] * other.value[0][2] + value[1][1] * other.value[1][2] + value[1][2] * other.value[2][2],
			value[1][0] * other.value[0][3] + value[1][1] * other.value[1][3] + value[1][2] * other.value[2][3] + value[1][3],

			value[2][0] * other.value[0][0] + value[2][1] * other.value[1][0] + value[2][2] * other.value[2][0],
			value[2][0] * other.value[0][1] + value[2][1] * other.value[1][1] + value[2][2] * other.value[2][1],
			value[2][0] * other.value[0][2] + value[2][1] * other.value[1][2] + value[2][2] * other.value[2][2],
			value[2][0] * other.value[0][3] + value[2][1] * other.value[1][3] + value[2][2] * other.value[2][3] + value[2][3]);
	}
	
	Vecteur3D Physics::Matrix34::operator*(const Vecteur3D& vector)
	{
		return Vecteur3D(
			value[0][0] * vector.x + value[0][1] * vector.y + value[0][2] * vector.z + value[0][3],
			value[1][0] * vector.x + value[1][1] * vector.y + value[1][2] * vector.z + value[1][3],
			value[2][0] * vector.x + value[2][1] * vector.y + value[2][2] * vector.z + value[2][3]);
	}
	
	Matrix34 Physics::Matrix34::Inverse()
	{
		float det = value[0][0] * (value[1][1] * value[2][2] - value[1][2] * value[2][1])
			- value[0][1] * (value[1][0] * value[2][2] - value[1][2] * value[2][0])
			+ value[0][2] * (value[1][0] * value[2][1] - value[1][1] * value[2][0]);

		if (det == 0.0f) {
			return Matrix34(0.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 0.0f);
		}

		float invDet = 1.0f / det;

		return Matrix34(
			(value[1][1] * value[2][2] - value[1][2] * value[2][1]) * invDet,
			(value[0][2] * value[2][1] - value[0][1] * value[2][2]) * invDet,
			(value[0][1] * value[1][2] - value[0][2] * value[1][1]) * invDet,
			- value[0][3],

			(value[1][2] * value[2][0] - value[1][0] * value[2][2]) * invDet,
			(value[0][0] * value[2][2] - value[0][2] * value[2][0]) * invDet,
			(value[0][2] * value[1][0] - value[0][0] * value[1][2]) * invDet,
			-value[1][3],

			(value[1][0] * value[2][1] - value[1][1] * value[2][0]) * invDet,
			(value[0][1] * value[2][0] - value[0][0] * value[2][1]) * invDet,
			(value[0][0] * value[1][1] - value[0][1] * value[1][0]) * invDet,
			-value[2][3]
		);
	}
	
	void Physics::Matrix34::SetOrientationAndPosition(const Quaternion& q, const Vecteur3D& v)
	{
		value[0][0] = 1 - (2 * q.j * q.j + 2 * q.k * q.k);
		value[0][1] = 2 * q.i * q.j + 2 * q.k * q.w;
		value[0][2] = 2 * q.i * q.k - 2 * q.j * q.w;
		value[0][3] = v.x;
		value[1][0] = 2 * q.i * q.j - 2 * q.k * q.w;
		value[1][1] = 1 - (2 * q.i * q.i + 2 * q.k * q.k);
		value[1][2] = 2 * q.j * q.k + 2 * q.i * q.w;
		value[1][3] = v.y;
		value[2][0] = 2 * q.i * q.k + 2 * q.j * q.w;
		value[2][1] = 2 * q.j * q.k - 2 * q.i * q.w;
		value[2][2] = 1 - (2 * q.i * q.i + 2 * q.j * q.j);
		value[2][3] = v.z;
	}
	
	Vecteur3D Physics::Matrix34::TransformPosition(const Vecteur3D v)
	{
		return Vecteur3D(value[0][3] + v.x, value[1][3] + v.y, value[2][3] + v.z);
	}
	
	Vecteur3D Physics::Matrix34::TransformDirection(const Vecteur3D& v)
	{
		return Vecteur3D(
			value[0][0] * v.x + value[0][1] * v.y + value[0][2] * v.z,
			value[1][0] * v.x + value[1][1] * v.y + value[1][2] * v.z,
			value[2][0] * v.x + value[2][1] * v.y + value[2][2] * v.z
		);
	}
}