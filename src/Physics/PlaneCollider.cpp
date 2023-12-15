#include "SphereCollider.hpp"
#include "PlaneCollider.hpp"
#include "BoxCollider.hpp"
#include <typeinfo>

namespace Physics {

	Vecteur3D PlaneCollider::getHalfSize() const {
		return Vecteur3D(1000000, 1000000, 1000000);
	}

	void PlaneCollider::generateContact(const PrimitiveCollider* other, std::vector<RigidbodyContact>& contacts) const {
		//Sphere-Plan
		const SphereCollider* otherSphere = dynamic_cast<const SphereCollider*>(other);
		if (otherSphere != nullptr){
			Vecteur3D center = otherSphere->rigidbody->getPosition() + otherSphere->offset.TransformPosition(Vecteur3D(0, 0, 0));
			float distance = Vecteur3D::dot(center, normal) - offset - otherSphere->radius;
			if (distance <= 0) {
				Vecteur3D contactPoint = center - normal * otherSphere->radius;
				RigidbodyContact contact;
				contact.bodies[0] = otherSphere->rigidbody;
				contact.bodies[1] = rigidbody;
				contact.normal = normal;
				contact.restitution = 0.8;
				contact.penetration = -distance;
				contact.contactPoint = contactPoint;
				contacts.push_back(contact);
			}
		}
		else{
			//Boite-Plan
			const BoxCollider* otherBox = dynamic_cast<const BoxCollider*>(other);
			if (otherBox != nullptr){
				Vecteur3D boxCenter = otherBox->rigidbody->getPosition() + otherBox->offset.TransformPosition(Vecteur3D(0, 0, 0));
				Vecteur3D points[8];
				points[0] = boxCenter + otherBox->halfsize;
				points[1] = boxCenter + Vecteur3D(-otherBox->halfsize.x, otherBox->halfsize.y, otherBox->halfsize.z);
				points[2] = boxCenter + Vecteur3D(otherBox->halfsize.x, -otherBox->halfsize.y, otherBox->halfsize.z);
				points[3] = boxCenter + Vecteur3D(-otherBox->halfsize.x, -otherBox->halfsize.y, otherBox->halfsize.z);
				points[4] = boxCenter + Vecteur3D(otherBox->halfsize.x, otherBox->halfsize.y, -otherBox->halfsize.z);
				points[5] = boxCenter + Vecteur3D(-otherBox->halfsize.x, otherBox->halfsize.y, -otherBox->halfsize.z);
				points[6] = boxCenter + Vecteur3D(otherBox->halfsize.x, -otherBox->halfsize.y, -otherBox->halfsize.z);
				points[7] = boxCenter + Vecteur3D(-otherBox->halfsize.x, -otherBox->halfsize.y, -otherBox->halfsize.z);
				for (Vecteur3D point : points) {
					float distance = Vecteur3D::dot(point, normal) - offset;
					if (distance <= 0) {
						RigidbodyContact contact;
						contact.bodies[0] = otherBox->rigidbody;
						contact.bodies[1] = rigidbody;
						contact.normal = normal;
						contact.restitution = 0.8;
						contact.penetration = -distance;
						contact.contactPoint = point;
						contacts.push_back(contact);
					}
				}
			}
		}
	}
}