#include "Box.hpp"

namespace Physics {
	Box::Box(float mass, Vecteur3D center, Vecteur3D halfExtents) :
		center(center),
	halfExtents(halfExtents)
	{
		Matrix3 inertiaTensor = Matrix3(mass * (halfExtents.y * halfExtents.y + halfExtents.z * halfExtents.z) / 12.0, 0, 0,
			0, mass * (halfExtents.y * halfExtents.y + halfExtents.x * halfExtents.x) / 12.0, 0,
			0, 0, mass * (halfExtents.z * halfExtents.z + halfExtents.x * halfExtents.x) / 12.0);
		inverseInertiaTensor = inertiaTensor.Inverse();
	}

	Matrix3 Box::GetInverseInertiaTensor() const {
		return inverseInertiaTensor;
	}
}