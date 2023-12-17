#include "SphereCollider.hpp"
#include "PlaneCollider.hpp"
#include "BoxCollider.hpp"

#include <typeinfo>

namespace Physics {

	BoxCollider::BoxCollider(Vecteur3D halfSize)
	{
		rigidbody = nullptr;
		halfSize = halfSize;
		offset.SetOrientationAndPosition(Quaternion::identity(), Vecteur3D(0, 0, 0));
	}

	BoxCollider::BoxCollider(Rigidbody* body, Vecteur3D halfSize)
	{
		rigidbody = body;
		halfSize = halfSize;
		offset.SetOrientationAndPosition(Quaternion::identity(), Vecteur3D(0, 0, 0));
		float mass = rigidbody->getMass();

		Matrix3 inertiaTensor = Matrix3(mass * 4 * (halfSize.y * halfSize.y + halfSize.z * halfSize.z) / 12.0, 0, 0,
			0, mass * 4 * (halfSize.y * halfSize.y + halfSize.x * halfSize.x) / 12.0, 0,
			0, 0, mass * 4 * (halfSize.z * halfSize.z + halfSize.x * halfSize.x) / 12.0);
		inverseInertiaTensor = inertiaTensor.Inverse();
	}

	std::vector<Vecteur3D> calculateAxes(const BoxCollider& boxA, const BoxCollider& boxB)
	{
		std::vector<Vecteur3D> axes;

		axes.push_back(Matrix34(boxA.offset).TransformDirection(Vecteur3D(1, 0, 0)).normalized());
		axes.push_back(Matrix34(boxA.offset).TransformDirection(Vecteur3D(0, 1, 0)).normalized());
		axes.push_back(Matrix34(boxA.offset).TransformDirection(Vecteur3D(0, 0, 1)).normalized());
		axes.push_back(Matrix34(boxB.offset).TransformDirection(Vecteur3D(1, 0, 0)).normalized());
		axes.push_back(Matrix34(boxB.offset).TransformDirection(Vecteur3D(0, 1, 0)).normalized());
		axes.push_back(Matrix34(boxB.offset).TransformDirection(Vecteur3D(0, 0, 1)).normalized());

		Vecteur3D cross;
		for (int i = 0; i < 3; i++) {
			for (int j = 3; j < 6; j++) {
				cross = axes[i].cross(axes[j]);
				if (cross.magnitudeSquared() >= 1e-6) {
					axes.push_back(cross.normalized());
				}
			}
		}
		return axes;
	}

	struct projection {
		float min;
		float max;
	};
	
	struct projection projectOntoAxis(const BoxCollider& box, const Vecteur3D& axis)
	{
		struct projection res;
		Vecteur3D halfsize = box.halfsize;
		float vertexProjectionMax = Vecteur3D::dot(box.offset.TransformPosition(box.rigidbody->getPosition() + box.offset.TransformDirection(halfsize)), axis);
		float vertexProjectionMin = Vecteur3D::dot(box.offset.TransformPosition(box.rigidbody->getPosition() - box.offset.TransformDirection(halfsize)), axis);

		if (vertexProjectionMax > vertexProjectionMin) {
			res.max = vertexProjectionMax;
			res.min = vertexProjectionMin;
		}
		else {
			res.min = vertexProjectionMax;
			res.max = vertexProjectionMin;
		}
		return res;
	}

	Vecteur3D findContactPoint(const BoxCollider& box, const Vecteur3D& axis)
	{
		Vecteur3D axes[3];
		axes[0] = Matrix34(box.offset).TransformDirection(Vecteur3D(1, 0, 0)).normalized();
		axes[1] = Matrix34(box.offset).TransformDirection(Vecteur3D(0, 1, 0)).normalized();
		axes[2] = Matrix34(box.offset).TransformDirection(Vecteur3D(0, 0, 1)).normalized();

		int indexMax = 0;
		float maxDotProduct = 0.f;
		for (int i = 0; i < 3; i++) {
			if (abs(Vecteur3D::dot(axes[i], axis)) >= maxDotProduct) {
				indexMax = i;
				maxDotProduct = abs(Vecteur3D::dot(axes[i], axis));
			}
		}
		float scale;
		switch (indexMax)
		{
		case 0:
			scale = box.halfsize.x;
			break;
		case 1:
			scale = box.halfsize.y;
			break;
		case 2:
			scale = box.halfsize.z;
			break;
		default:
			break;
		}

		return box.rigidbody->getPosition() + axis * scale / Vecteur3D::dot(axes[indexMax], axis);
	}


	void BoxCollider::generateContact(const PrimitiveCollider* other, std::vector<RigidbodyContact>& contacts) const {
		//Boite-Sphere
		const SphereCollider* otherSphere = dynamic_cast<const SphereCollider*>(other);
		if (otherSphere != nullptr){
			Vecteur3D center = otherSphere->rigidbody->getPosition() + otherSphere->offset.TransformPosition(Vecteur3D(0, 0, 0));
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
			if (distance.magnitudeSquared() < otherSphere->radius * otherSphere->radius) {
				Vecteur3D normal = distance.normalized();
				Vecteur3D contactPoint = center - normal * otherSphere->radius;
				RigidbodyContact contact;
				contact.bodies[0] = otherSphere->rigidbody;
				contact.bodies[1] = rigidbody;
				contact.normal = normal;
				contact.restitution = 0.8;
				contact.penetration = otherSphere->radius - distance.magnitude();
				contact.contactPoint = contactPoint;
				contacts.push_back(contact);
			}
		}
		else {
			//Boite-Plan
			const PlaneCollider* otherPlane = dynamic_cast<const PlaneCollider*>(other);
			if (otherPlane != nullptr) {
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
					float distance = Vecteur3D::dot(point, otherPlane->normal) - otherPlane->offset;
					if (distance <= 0) {
						RigidbodyContact contact;
						contact.bodies[0] = rigidbody;
						contact.bodies[1] = otherPlane->rigidbody;
						contact.normal = otherPlane->normal;
						contact.restitution = 0.8;
						contact.penetration = -distance;
						contact.contactPoint = point;
						contacts.push_back(contact);
					}
				}
			}
			else {
				//Boite-Boite
				const BoxCollider* otherBox = dynamic_cast<const BoxCollider*>(other);
				if (otherBox != nullptr) {
					std::vector<Vecteur3D> axes = calculateAxes(*this, *otherBox);

					float minSeparation = std::numeric_limits<float>::max();
					Vecteur3D minSeparationAxis;

					for (const Vecteur3D& axis : axes)
					{
						struct projection projectionA = projectOntoAxis(*this, axis);
						struct projection projectionB = projectOntoAxis(*otherBox, axis);

						float overlap = std::max(projectionA.max - projectionB.min, projectionB.max - projectionA.min);

						if (overlap <= 0.0f)
							//Pas de collisions
							return;

						if (overlap < minSeparation)
						{
							minSeparation = overlap;
							minSeparationAxis = axis;
						}
					}
					//Point de contact
					RigidbodyContact contact;
					contact.bodies[0] = rigidbody;
					contact.bodies[1] = otherBox->rigidbody;
					contact.normal = Vecteur3D(minSeparationAxis).normalized();
					contact.restitution = 0.8;
					contact.penetration = minSeparation;
					contact.contactPoint = findContactPoint(*this, minSeparationAxis);
					contacts.push_back(contact);
				}
			}
		}
	}
}