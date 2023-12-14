#include "SphereCollider.hpp"
#include <typeinfo>

namespace Physics
{
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
				return;
			}
		}
		catch (std::bad_cast) {
			return;
		}
	}
}