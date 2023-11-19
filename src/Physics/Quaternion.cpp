#include "Quaternion.hpp"

#include  <cmath>
#include <numbers>

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

	void Quaternion::UpdateByAngularVelocity(const Vecteur3D vector, const float duration = 0.1f )
	{
		Quaternion q = *this;
		q.RotateByVector(vector * duration / 2);
		*this += q;
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

	Quaternion Quaternion::identity() {
		return Quaternion(1, 0, 0, 0);
	}

	Vecteur3D Quaternion::toYXZ() {
		Normalized();
		float yaw = atan2(2 * (w * k + i * j), 1 - 2 * (j * j + k * k));
		float pitch = asin(2 * (w * j - k * i));
		float roll = atan2(2 * (w * i + j * k), 1 - 2 * (i * i + j * j));
		return Vecteur3D(yaw, pitch, roll);
	}
}