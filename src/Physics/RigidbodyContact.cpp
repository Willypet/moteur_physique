#include "RigidbodyContact.hpp"

namespace Physics {

	float RigidbodyContact::computeVelocity() const {
		Vecteur3D velocity = bodies[0]->getLinearVelocity() + bodies[0]->getAngularVelocity().cross(bodies[0]->getPosition() - contactPoint);
		if (bodies[1] != nullptr) {
			velocity -= bodies[1]->getLinearVelocity() + bodies[1]->getAngularVelocity().cross(bodies[1]->getPosition() - contactPoint);
		}
		return Vecteur3D::dot(velocity, normal);
	}

	void RigidbodyContact::resolveVelocity(float duration) {
		float separatingVelocity = computeVelocity();

		if (separatingVelocity >= 0) //Contact au repos ou déjà en éloignement
		{
			return;
		}

		float sumInverseMass = 1 / bodies[0]->getMass();

		Vecteur3D offset1 = bodies[0]->getPosition() - contactPoint;
		Matrix3 orientationMatrix1 = Matrix3();
		orientationMatrix1.SetOrientation(bodies[0]->getRotation());
		Matrix3 globalInverseInertiaTensor1 = orientationMatrix1.Transpose() * bodies[0]->getCollider()->getInverseInertiaTensor() * orientationMatrix1;
		Vecteur3D sumInertia = (globalInverseInertiaTensor1 * (offset1.cross(normal))).cross(offset1);

		Vecteur3D offset2;
		Matrix3 globalInverseInertiaTensor2;

		if (bodies[1] != nullptr) {
			sumInverseMass += 1 / bodies[1]->getMass();

			offset2 = bodies[1]->getPosition() - contactPoint;
			Matrix3 orientationMatrix2 = Matrix3();
			orientationMatrix1.SetOrientation(bodies[1]->getRotation());
			globalInverseInertiaTensor2 = orientationMatrix2.Transpose() * bodies[1]->getCollider()->getInverseInertiaTensor() * orientationMatrix2;
			sumInertia += (globalInverseInertiaTensor2 * (offset2.cross(normal))).cross(offset2);
		}

		float impulsion = (1 + restitution) * separatingVelocity / Vecteur3D::dot(sumInverseMass * normal + sumInertia, normal);

		bodies[0]->SetLinearVelocity(bodies[0]->getLinearVelocity() - impulsion * normal / bodies[0]->getMass());
		bodies[0]->SetAngularVelocity(bodies[0]->getAngularVelocity() - (globalInverseInertiaTensor1 * (offset1.cross(normal))).cross(offset1));

		if (bodies[1] != nullptr) {
			bodies[1]->SetLinearVelocity(bodies[1]->getLinearVelocity() + impulsion * normal / bodies[1]->getMass());
			bodies[1]->SetAngularVelocity(bodies[1]->getAngularVelocity() - (globalInverseInertiaTensor2 * (offset2.cross(normal))).cross(offset2));
		}
	}

	void RigidbodyContact::resolveInterpenetration(float duration) {
		if (penetration <= 0) {
			return;
		}

		float sumInverseMass = 1 / bodies[0]->getMass();
		if (bodies[1] != nullptr) {
			sumInverseMass += 1 / bodies[1]->getMass();
		}

		if (sumInverseMass <= 0) //Objets de masse infinie (i.e statiques)
		{
			return;
		}

		float linearInertia1 = 1 / bodies[0]->getMass();
		Vecteur3D offset1 = bodies[0]->getPosition() - contactPoint;
		Matrix3 orientationMatrix1 = Matrix3();
		orientationMatrix1.SetOrientation(bodies[0]->getRotation());
		Matrix3 globalInverseInertiaTensor1 = orientationMatrix1.Transpose() * bodies[0]->getCollider()->getInverseInertiaTensor() * orientationMatrix1;
		float angularInertia1 = Vecteur3D::dot((globalInverseInertiaTensor1 * (offset1.cross(normal))).cross(offset1), normal);

		float linearInertia2;
		Vecteur3D offset2;
		Matrix3 globalInverseInertiaTensor2;
		float angularInertia2;
		float totalInertia = linearInertia1 + angularInertia1;

		if (bodies[1] != nullptr) {
			linearInertia2 = 1 / bodies[1]->getMass();
			offset2 = bodies[1]->getPosition() - contactPoint;
			Matrix3 orientationMatrix2 = Matrix3();
			orientationMatrix1.SetOrientation(bodies[1]->getRotation());
			globalInverseInertiaTensor2 = orientationMatrix2.Transpose() * bodies[1]->getCollider()->getInverseInertiaTensor() * orientationMatrix2;
			angularInertia2 = Vecteur3D::dot((globalInverseInertiaTensor2 * (offset2.cross(normal))).cross(offset2), normal);
			totalInertia += linearInertia2 + angularInertia2;
		}

		float inverseTotalInertia = 1 / totalInertia;
		float linearMove1 = penetration * linearInertia1 * inverseTotalInertia;
		float angularMove1 = penetration * angularInertia1 * inverseTotalInertia;

		bodies[0]->SetPosition(bodies[0]->getPosition() + normal * linearMove1);
		Vecteur3D impulsePerMove = globalInverseInertiaTensor1 * (offset1.cross(normal));
		Vecteur3D rotationPerMove = impulsePerMove / angularInertia1;
		Vecteur3D rotation = rotationPerMove * angularMove1;
		Quaternion newRotation = bodies[0]->getRotation();
		newRotation.RotateByVector(rotation);
		bodies[0]->SetRotation(newRotation);

		if (bodies[1] != nullptr) {
			float linearMove2 = -penetration * linearInertia2 * inverseTotalInertia;
			float angularMove2 = -penetration * angularInertia2 * inverseTotalInertia;

			bodies[1]->SetPosition(bodies[1]->getPosition() + normal * linearMove2);
			impulsePerMove = globalInverseInertiaTensor2 * (offset2.cross(normal));
			rotationPerMove = impulsePerMove / angularInertia2;
			rotation = rotationPerMove * angularMove2;
			newRotation = bodies[1]->getRotation();
			newRotation.RotateByVector(rotation);
			bodies[1]->SetRotation(newRotation);
		}

		//Ne pas refaire ce contact
		penetration = -1;
	}
}