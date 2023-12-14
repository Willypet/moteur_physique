#include "SphereCollider.hpp"
#include "PlaneCollider.hpp"
#include "BoxCollider.hpp"
#include <typeinfo>

namespace Physics
{

	SphereCollider::SphereCollider(Rigidbody* body, float radius) {
		rigidbody = body;
		this->radius = radius;
		float mass = rigidbody->getMass();

		Matrix3 inertiaTensor = Matrix3(mass * 2 * radius * radius / 5.0, 0, 0,
			0, mass * 2 * radius * radius / 5.0, 0,
			0, 0, mass * 2 * radius * radius / 5.0);
		inverseInertiaTensor = inertiaTensor.Inverse();
	}

	Matrix3 SphereCollider::getInverseInertiaTensor() const {
		return inverseInertiaTensor;
	}

	Vecteur3D SphereCollider::getHalfSize() {
		return Vecteur3D(radius, radius, radius);
	}

	void SphereCollider::generateContact(const PrimitiveCollider& other, std::vector<RigidbodyContact>& contacts) const {
		try { //Contact Sphere-Sphere
			const SphereCollider& otherSphere = dynamic_cast<const SphereCollider&>(other);
			Vecteur3D distance = (rigidbody->getPosition() + offset.TransformPosition(Vecteur3D(0, 0, 0)))
				- (otherSphere.rigidbody->getPosition() + otherSphere.offset.TransformPosition(Vecteur3D(0, 0, 0)));
			if (distance.magnitudeSquared()
				<= otherSphere.radius * otherSphere.radius + radius * radius) {
				Vecteur3D normal = distance.normalized();
				float penetration = otherSphere.radius + radius - distance.magnitude();
				Vecteur3D contactPoint = rigidbody->getPosition() + offset.TransformPosition(Vecteur3D(0, 0, 0)) - normal * radius;
				RigidbodyContact contact;
				contact.bodies[0] = rigidbody;
				contact.bodies[1] = otherSphere.rigidbody;
				contact.normal = normal;
				contact.restitution = 0.8;
				contact.penetration = penetration;
				contact.contactPoint = contactPoint;
				contacts.push_back(contact);
			}
		}
		catch (std::bad_cast) {
			try { //Sphere-Plan
				const PlaneCollider& otherPlane = dynamic_cast<const PlaneCollider&>(other);
				Vecteur3D center = rigidbody->getPosition() + offset.TransformPosition(Vecteur3D(0, 0, 0));
				float distance = Vecteur3D::dot(center, otherPlane.normal) - otherPlane.offset - radius;
				if (distance <= 0) {
					Vecteur3D contactPoint = center - otherPlane.normal * radius;
					RigidbodyContact contact;
					contact.bodies[0] = rigidbody;
					contact.bodies[1] = otherPlane.rigidbody;
					contact.normal = otherPlane.normal;
					contact.restitution = 0.8;
					contact.penetration = -distance;
					contact.contactPoint = contactPoint;
					contacts.push_back(contact);
				}
			}
			catch (std::bad_cast) {
				try { //Sphere-Boite
					const BoxCollider& otherBox = dynamic_cast<const BoxCollider&>(other);

					Vecteur3D center = rigidbody->getPosition() + offset.TransformPosition(Vecteur3D(0, 0, 0));
					Vecteur3D boxCenter = otherBox.rigidbody->getPosition() + otherBox.offset.TransformPosition(Vecteur3D(0, 0, 0));
					Vecteur3D centerBoxSpace = center - boxCenter;

					if (centerBoxSpace.x > otherBox.halfsize.x) centerBoxSpace.x = otherBox.halfsize.x;
					if (centerBoxSpace.x < -otherBox.halfsize.x) centerBoxSpace.x = -otherBox.halfsize.x;

					if (centerBoxSpace.y > otherBox.halfsize.y) centerBoxSpace.y = otherBox.halfsize.y;
					if (centerBoxSpace.y < -otherBox.halfsize.y) centerBoxSpace.y = -otherBox.halfsize.y;

					if (centerBoxSpace.z > otherBox.halfsize.z) centerBoxSpace.z = otherBox.halfsize.z;
					if (centerBoxSpace.z < -otherBox.halfsize.z) centerBoxSpace.z = -otherBox.halfsize.z;
					
					//Reconversion en coordonn�es monde
					Vecteur3D closestPoint = boxCenter + centerBoxSpace;
					Vecteur3D distance = center - closestPoint;
					if (distance.magnitudeSquared() < radius * radius) {
						Vecteur3D normal = distance.normalized();
						Vecteur3D contactPoint = center - normal * radius;
						RigidbodyContact contact;
						contact.bodies[0] = rigidbody;
						contact.bodies[1] = otherBox.rigidbody;
						contact.normal = normal;
						contact.restitution = 0.8;
						contact.penetration = radius - distance.magnitude();
						contact.contactPoint = contactPoint;
						contacts.push_back(contact);
					}
				}
				catch (std::bad_cast) {
					//On ne devrait pas �tre l�
					return;
				}
			}
			return;
		}
	}
}