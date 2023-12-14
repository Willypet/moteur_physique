#include "SphereCollider.hpp"
#include "PlaneCollider.hpp"
#include "BoxCollider.hpp"
#include <typeinfo>

namespace Physics {

	BoxCollider::BoxCollider(Rigidbody* body, Vecteur3D halfSize)
	{
		rigidbody = body;
		halfSize = halfSize;
		float mass = rigidbody->getMass();

		Matrix3 inertiaTensor = Matrix3(mass * 4 * (halfSize.y * halfSize.y + halfSize.z * halfSize.z) / 12.0, 0, 0,
			0, mass * 4 * (halfSize.y * halfSize.y + halfSize.x * halfSize.x) / 12.0, 0,
			0, 0, mass * 4 * (halfSize.z * halfSize.z + halfSize.x * halfSize.x) / 12.0);
		inverseInertiaTensor = inertiaTensor.Inverse();
	}

	Matrix3 BoxCollider::getInverseInertiaTensor() const {
		return inverseInertiaTensor;
	}

	Vecteur3D BoxCollider::getHalfSize() {
		return halfsize;
	}

	void BoxCollider::generateContact(const PrimitiveCollider& other, std::vector<RigidbodyContact>& contacts) const {
		try {//Boite-Sphere
			const SphereCollider& otherSphere = dynamic_cast<const SphereCollider&>(other);

			Vecteur3D center = otherSphere.rigidbody->getPosition() + otherSphere.offset.TransformPosition(Vecteur3D(0, 0, 0));
			Vecteur3D boxCenter = rigidbody->getPosition() + offset.TransformPosition(Vecteur3D(0, 0, 0));
			Vecteur3D centerBoxSpace = center - boxCenter;

			if (centerBoxSpace.x > halfsize.x) centerBoxSpace.x = halfsize.x;
			if (centerBoxSpace.x < halfsize.x) centerBoxSpace.x = halfsize.x;

			if (centerBoxSpace.y > halfsize.y) centerBoxSpace.y = halfsize.y;
			if (centerBoxSpace.y < halfsize.y) centerBoxSpace.y = halfsize.y;

			if (centerBoxSpace.z > halfsize.z) centerBoxSpace.z = halfsize.z;
			if (centerBoxSpace.z < halfsize.z) centerBoxSpace.z = halfsize.z;

			//Reconversion en coordonnées monde
			Vecteur3D closestPoint = boxCenter + centerBoxSpace;
			Vecteur3D distance = center - closestPoint;
			if (distance.magnitudeSquared() < otherSphere.radius * otherSphere.radius) {
				Vecteur3D normal = distance.normalized();
				Vecteur3D contactPoint = center - normal * otherSphere.radius;
				RigidbodyContact contact;
				contact.bodies[0] = otherSphere.rigidbody;
				contact.bodies[1] = rigidbody;
				contact.normal = normal;
				contact.restitution = 0.8;
				contact.penetration = otherSphere.radius - distance.magnitude();
				contact.contactPoint = contactPoint;
				contacts.push_back(contact);
			}
		}
		catch (std::bad_cast) {
			try {//Boite-Plan
				const PlaneCollider& otherPlane = dynamic_cast<const PlaneCollider&>(other);
				Vecteur3D boxCenter = rigidbody->getPosition() + offset.TransformPosition(Vecteur3D(0, 0, 0));
				Vecteur3D points[8];
				points[0] = boxCenter + halfsize;
				points[1] = boxCenter + Vecteur3D(halfsize.x, halfsize.y, halfsize.z);
				points[2] = boxCenter + Vecteur3D(halfsize.x, halfsize.y, halfsize.z);
				points[3] = boxCenter + Vecteur3D(halfsize.x, halfsize.y, halfsize.z);
				points[4] = boxCenter + Vecteur3D(halfsize.x, halfsize.y, halfsize.z);
				points[5] = boxCenter + Vecteur3D(halfsize.x, halfsize.y, halfsize.z);
				points[6] = boxCenter + Vecteur3D(halfsize.x, halfsize.y, halfsize.z);
				points[7] = boxCenter + Vecteur3D(halfsize.x, halfsize.y, halfsize.z);
				for (Vecteur3D point : points) {
					float distance = Vecteur3D::dot(point, otherPlane.normal) - otherPlane.offset;
					if (distance <= 0) {
						RigidbodyContact contact;
						contact.bodies[0] = rigidbody;
						contact.bodies[1] = otherPlane.rigidbody;
						contact.normal = otherPlane.normal;
						contact.restitution = 0.8;
						contact.penetration = -distance;
						contact.contactPoint = point;
						contacts.push_back(contact);
					}
				}
			}
			catch (std::bad_cast) {
				try {//Boite-Boite
					const BoxCollider& otherBox = dynamic_cast<const BoxCollider&>(other);
				}
				catch (std::bad_cast) {
					//On ne doit pas arriver ici
					return;
				}
			}
		}
	}
}