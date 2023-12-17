#include "Rigidbody.hpp"
#include "Matrix3.hpp"
#include <math.h>
#include<iostream>

namespace Physics {
	void Rigidbody::CalculateDerivedData()
	{
	}

	Rigidbody::Rigidbody(const std::string& gameObjectFilePath) :
		masse{ 1 },
		linearDamping{ 1 },
		angularDamping{ 1 },
		position(Vecteur3D::vecteurNull()),
		orientation{ Quaternion() },
		linearVelocity(Vecteur3D::vecteurNull()),
		angularVelocity{ Vecteur3D::vecteurNull() },
		gameObjectFilePath(gameObjectFilePath),
		idGameObject(0)
	{
		col = nullptr;
		transformMatrix.SetOrientationAndPosition(orientation, position);
	}

	Rigidbody::Rigidbody(const Vecteur3D position, const Quaternion orientation, const std::string& gameObjectFilePath) :
		masse{ 1 },
		linearDamping{ 1 },
		angularDamping{ 1 },
		position(position),
		orientation{ orientation },
		linearVelocity(Vecteur3D::vecteurNull()),
		angularVelocity{ Vecteur3D::vecteurNull() },
		gameObjectFilePath(gameObjectFilePath),
		idGameObject(0)
	{
		col = nullptr;
		transformMatrix.SetOrientationAndPosition(orientation, position);
	}

	Rigidbody::Rigidbody(const float _masse, const Vecteur3D& _position, const Quaternion _orientation, const std::string& gameObjectFilePath) :
		masse{ std::max(_masse, 0.0001f) },
		linearDamping{ 1 },
		angularDamping{ 1 },
		position(_position),
		orientation{ _orientation },
		linearVelocity(Vecteur3D::vecteurNull()),
		angularVelocity{ Vecteur3D::vecteurNull() },
		gameObjectFilePath(gameObjectFilePath),
		idGameObject(0)
	{
		col = nullptr;
		transformMatrix.SetOrientationAndPosition(orientation, position);
	}

	Rigidbody::Rigidbody(const float _masse, const Vecteur3D& _position, const Quaternion _orientation, PrimitiveCollider* _col, const std::string& gameObjectFilePath) :
		masse{ std::max(_masse, 0.0001f) },
		linearDamping{ 1 },
		angularDamping{ 1 },
		position(_position),
		orientation{ _orientation },
		col(_col),
		linearVelocity(Vecteur3D::vecteurNull()),
		angularVelocity{ Vecteur3D::vecteurNull() },
		gameObjectFilePath(gameObjectFilePath),
		idGameObject(0)
	{
		transformMatrix.SetOrientationAndPosition(orientation, position);
	}

	void Rigidbody::Integrate(float duration)
	{
		position = position + linearVelocity * duration;
		orientation.UpdateByAngularVelocity(angularVelocity, duration);
		orientation.Normalized();
		transformMatrix.SetOrientationAndPosition(orientation, position);

		Vecteur3D linearAcc = 1 / masse * m_forceAccum;

		Matrix3 orientationMatrix = Matrix3();
		orientationMatrix.SetOrientation(orientation);
		Matrix3 globalInverseInertiaTensor = orientationMatrix.Transpose() * col->inverseInertiaTensor * orientationMatrix;

		Vecteur3D angularAcc = globalInverseInertiaTensor * m_torqueAccum;

		linearVelocity = linearVelocity * pow(linearDamping, duration) + linearAcc * duration;
		angularVelocity = angularVelocity * pow(angularDamping, duration) + angularAcc * duration;

		ClearAccumulator();
	}


	Vecteur3D Rigidbody::getLinearVelocity() const {
		return linearVelocity;
	}

	Vecteur3D Rigidbody::getAngularVelocity() const {
		return angularVelocity;
	}

	PrimitiveCollider* Rigidbody::getCollider() const {
		return col;
	}

	void Rigidbody::SetCollider(PrimitiveCollider* newCol){
		col = newCol;
	}

	Matrix34 Rigidbody::getTransform() const {
		return transformMatrix;
	}

	float Rigidbody::getMass() const {
		return masse;
	}

	Vecteur3D Rigidbody::getPosition() const {
		return position;
	}

	Quaternion Rigidbody::getRotation() const {
		return orientation;
	}

	std::string Rigidbody::getGameObjectFilePath() const
	{
		return gameObjectFilePath;
	}

	void Rigidbody::SetRotation(const Quaternion& newRotation) {
		orientation = newRotation;
	}

	void Rigidbody::SetPosition(const Vecteur3D& newPosition) {
		position = newPosition;
	}

	void Rigidbody::SetLinearVelocity(const Vecteur3D& newVelocity) {
		linearVelocity = newVelocity;
	}

	void Rigidbody::SetAngularVelocity(const Vecteur3D& newVelocity) {
		angularVelocity = newVelocity;
	}

	void Rigidbody::AddForce(const Vecteur3D& force)
	{
		m_forceAccum += force;
	}

	void Rigidbody::AddForceAtPoint(const Vecteur3D& force, const Vecteur3D& worldPoint)
	{
		m_forceAccum += force;
		Vecteur3D localPoint = worldPoint - position;
		m_torqueAccum += localPoint.cross(force);
	}

	void Rigidbody::AddForceAtBodyPoint(const Vecteur3D& force, const Vecteur3D& localPoint)
	{
		m_forceAccum += force;
		m_torqueAccum += localPoint ^ force;
	}

	void Rigidbody::ClearAccumulator()
	{
		m_forceAccum = Vecteur3D::vecteurNull();
		m_torqueAccum = Vecteur3D::vecteurNull();
	}

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
		Matrix3 globalInverseInertiaTensor1 = orientationMatrix1.Transpose() * bodies[0]->getCollider()->inverseInertiaTensor * orientationMatrix1;
		Vecteur3D sumInertia = (globalInverseInertiaTensor1 * (offset1.cross(normal))).cross(offset1);

		Vecteur3D offset2;
		Matrix3 globalInverseInertiaTensor2;

		if (bodies[1] != nullptr) {
			sumInverseMass += 1 / bodies[1]->getMass();

			offset2 = bodies[1]->getPosition() - contactPoint;
			Matrix3 orientationMatrix2 = Matrix3();
			orientationMatrix1.SetOrientation(bodies[1]->getRotation());
			globalInverseInertiaTensor2 = orientationMatrix2.Transpose() * bodies[1]->getCollider()->inverseInertiaTensor * orientationMatrix2;
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
		Matrix3 globalInverseInertiaTensor1 = orientationMatrix1.Transpose() * bodies[0]->getCollider()->inverseInertiaTensor * orientationMatrix1;
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
			globalInverseInertiaTensor2 = orientationMatrix2.Transpose() * bodies[1]->getCollider()->inverseInertiaTensor * orientationMatrix2;
			angularInertia2 = Vecteur3D::dot((globalInverseInertiaTensor2 * (offset2.cross(normal))).cross(offset2), normal);
			totalInertia += linearInertia2 + angularInertia2;
		}

		float inverseTotalInertia = 1 / totalInertia;
		float linearMove1 = penetration * linearInertia1 * inverseTotalInertia;
		float angularMove1 = penetration * angularInertia1 * inverseTotalInertia;

		bodies[0]->SetPosition(bodies[0]->getPosition() + normal * linearMove1);
		Vecteur3D impulsePerMove;
		Vecteur3D rotationPerMove;
		Vecteur3D rotation;
		Quaternion newRotation;
		if (abs(angularInertia1) >= 1e-3){
			impulsePerMove = globalInverseInertiaTensor1 * (offset1.cross(normal));
			rotationPerMove = impulsePerMove / angularInertia1;
			rotation = rotationPerMove * angularMove1;
			newRotation = bodies[0]->getRotation();
			newRotation.RotateByVector(rotation);
			bodies[0]->SetRotation(newRotation);
		}

		if (bodies[1] != nullptr) {
			float linearMove2 = -penetration * linearInertia2 * inverseTotalInertia;
			float angularMove2 = -penetration * angularInertia2 * inverseTotalInertia;

			bodies[1]->SetPosition(bodies[1]->getPosition() + normal * linearMove2);
			if (abs(angularInertia2) >= 1e-3) {
				impulsePerMove = globalInverseInertiaTensor2 * (offset2.cross(normal));
				rotationPerMove = impulsePerMove / angularInertia2;
				rotation = rotationPerMove * angularMove2;
				newRotation = bodies[1]->getRotation();
				newRotation.RotateByVector(rotation);
				bodies[1]->SetRotation(newRotation);
			}
		}

		//Ne pas refaire ce contact
		penetration = -1;
	}
}