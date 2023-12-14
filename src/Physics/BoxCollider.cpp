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

	Vecteur3D BoxCollider::getHalfSize() const {
		return halfsize;
	}

	void BoxCollider::generateContact(const PrimitiveCollider& other, std::vector<RigidbodyContact>& contacts) const {
		//Boite-Sphere
		try {
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
			//Boite-Plan
			try {
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
				//Boite-Boite
				try {
					const BoxCollider& otherBox = dynamic_cast<const BoxCollider&>(other);

					std::vector<Vecteur3D> axes = calculateAxes(*this, otherBox);

					float minSeparation = std::numeric_limits<float>::max();
					Vecteur3D minSeparationAxis;

					for (const Vecteur3D& axis : axes)
					{
						float projectionA = projectOntoAxis(*this, axis);
						float projectionB = projectOntoAxis(otherBox, axis);

						float overlap = std::min(projectionA, projectionB) - std::max(projectionA, projectionB);

						if (overlap <= 0.0f)
							//Pas de collisions
							contacts.clear();
							return;

						if (overlap < minSeparation)
						{
							minSeparation = overlap;
							minSeparationAxis = axis;

							//Point de contact
							RigidbodyContact contact;
							contact.bodies[0] = rigidbody;
							contact.bodies[1] = otherBox.rigidbody;
							contact.normal = Vecteur3D(axis).normalized();
							contact.restitution = 0.8;
							contact.penetration = -overlap;
							contact.contactPoint = findContactPoint(*this, otherBox, axis);
							contacts.push_back(contact);
						}			
					}

				}
				catch (std::bad_cast) {
					//On ne doit pas arriver ici
					return;
				}
			}
		}
	}

	std::vector<Vecteur3D> calculateAxes(const BoxCollider& boxA, const BoxCollider& boxB)
	{
		std::vector<Vecteur3D> axes;

		axes.push_back(Matrix34(boxA.offset).TransformDirection(Vecteur3D(1, 0, 0)));
		axes.push_back(Matrix34(boxA.offset).TransformDirection(Vecteur3D(0, 1, 0)));
		axes.push_back(Matrix34(boxA.offset).TransformDirection(Vecteur3D(0, 0, 1)));
		axes.push_back(Matrix34(boxB.offset).TransformDirection(Vecteur3D(1, 0, 0)));
		axes.push_back(Matrix34(boxB.offset).TransformDirection(Vecteur3D(0, 1, 0)));
		axes.push_back(Matrix34(boxB.offset).TransformDirection(Vecteur3D(0, 0, 1)));

		axes.push_back(axes[0].cross(axes[3]));
		axes.push_back(axes[0].cross(axes[4]));
		axes.push_back(axes[0].cross(axes[5]));
		axes.push_back(axes[1].cross(axes[3]));
		axes.push_back(axes[1].cross(axes[4]));
		axes.push_back(axes[1].cross(axes[5]));
		axes.push_back(axes[2].cross(axes[3]));
		axes.push_back(axes[2].cross(axes[4]));
		axes.push_back(axes[2].cross(axes[5]));

		return axes;
	}

	float projectOntoAxis(const BoxCollider& box, const Vecteur3D& axis)
	{
		float centerProjection = Vecteur3D::dot(box.offset.TransformPosition(Vecteur3D::vecteurNull()), axis);

		Vecteur3D halfsize = box.getHalfSize();
		float vertexProjection =
			std::abs(Vecteur3D::dot(box.offset.TransformPosition(halfsize), axis)) +
			std::abs(Vecteur3D::dot(box.offset.TransformPosition(-halfsize), axis));

		return vertexProjection + centerProjection;
	}

	Vecteur3D findContactPoint(const BoxCollider& boxA, const BoxCollider& boxB, const Vecteur3D& axis)
	{
		// Projections des coins de la boîte A sur l'axe
		float projectionA_Max = projectOntoAxis(boxA, axis);
		float projectionA_Min = -projectionA_Max;

		// Projections des coins de la boîte B sur l'axe
		float projectionB_Max = projectOntoAxis(boxB, axis);
		float projectionB_Min = -projectionB_Max;

		// Utilisez la moyenne des projections maximales et minimales pour déterminer le point de contact
		float contactPointValue = 0.5 * (projectionA_Max + projectionA_Min + projectionB_Max + projectionB_Min);

		// Convertissez le point de contact de la coordonnée de l'axe à l'espace mondial
		Vecteur3D contactPoint = boxA.offset.TransformPosition(Vecteur3D::vecteurNull()) + axis * contactPointValue;

		return contactPoint;
	}

}