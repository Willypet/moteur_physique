#include "Quaternion.hpp"

#include  <cmath>

namespace Physics {
	Quaternion::Quaternion(float w, float i, float j, float k) : w{w}, i{i}, j{j}, k{k}
	{
	}

	Quaternion::Quaternion() {
		Quaternion(0.f, 0.f, 0.f, 0.f);
	}

	void Quaternion::Normalized()
	{
		float magnitude = std::sqrt(w * w + i * i + j * j + k * k);
		if (magnitude == 0) {
			return;
		}

		w /= magnitude;
		i /= magnitude;
		j /= magnitude;
		k /= magnitude;
	}

	void Quaternion::RotateByVector(const Vecteur3D& vector)
	{
		*this *= Quaternion(0, vector.x, vector.y, vector.z);
	}

	void Quaternion::UpdateByAngularVelocity(const Vecteur3D vector)
	{
		RotateByVector(vector);
		*this *= 0.5f; //Integration Euler semie implicite
	}

	Quaternion Quaternion::operator*=(const Quaternion& other)
	{
		return *this = Quaternion(
			w*other.w - i*other.i - j*other.j - k*other.k,
			w * other.i + i * other.w + j * other.k - k * other.j, 
			w * other.j + j * other.w + k * other.i - i * other.k, 
			w * other.k + k * other.w + i * other.j - j * other.i);
	}

	Quaternion Quaternion::operator*=(const float& f)
	{
		return *this = Quaternion(w * f, i * f, j * f, k * f);
	}

	Quaternion Quaternion::operator+=(const Quaternion& other) {
		return *this = Quaternion(w + other.w, i + other.i, j + other.j, k + other.k);
	}
}