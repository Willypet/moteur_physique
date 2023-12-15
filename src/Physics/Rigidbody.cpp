#include "Rigidbody.hpp"
#include "Matrix3.hpp"
#include <math.h>
#include<iostream>

void Physics::Rigidbody::CalculateDerivedData()
{
}

Physics::Rigidbody::Rigidbody(const std::string& gameObjectFilePath) :
	masse{ 1 },
	linearDamping{ 1 },
	angularDamping{1},
	position(Vecteur3D::vecteurNull()),
	orientation{Quaternion()},
	linearVelocity(Vecteur3D::vecteurNull()),
	angularVelocity{ Vecteur3D::vecteurNull() },
	gameObjectFilePath(gameObjectFilePath),
	idGameObject(0)
{
	transformMatrix.SetOrientationAndPosition(orientation, position);
}

Physics::Rigidbody::Rigidbody(const Vecteur3D position, const Quaternion orientation, const std::string& gameObjectFilePath) :
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
	transformMatrix.SetOrientationAndPosition(orientation, position);
}

Physics::Rigidbody::Rigidbody(const float _masse, const Vecteur3D& _position, const Quaternion _orientation, PrimitiveCollider* _col, const std::string& gameObjectFilePath) :
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

void Physics::Rigidbody::Integrate(float duration)
{
	position = position + linearVelocity * duration;
	orientation.UpdateByAngularVelocity(angularVelocity, duration);
	orientation.Normalized();
	transformMatrix.SetOrientationAndPosition(orientation, position);

	Vecteur3D linearAcc = 1 / masse * m_forceAccum;

	Matrix3 orientationMatrix = Matrix3();
	orientationMatrix.SetOrientation(orientation);
	/*DEBUG
	Vecteur3D angles = orientation.toYXZ();
	//std::cout << "posX : " << position.x << " posY : " << position.y << "posZ : " << position.z << std::endl;
	std::cout << "rotX : " << angles.x << " rotY : " << angles.y << " rotZ : " << angles.z << std::endl;
	/*FIN DEBUG*/
	Matrix3 globalInverseInertiaTensor = orientationMatrix.Transpose() * col->getInverseInertiaTensor() * orientationMatrix;

	Vecteur3D angularAcc = globalInverseInertiaTensor * m_torqueAccum;

	linearVelocity = linearVelocity * pow(linearDamping, duration) + linearAcc * duration;
	angularVelocity = angularVelocity * pow(angularDamping, duration) + angularAcc * duration;

	ClearAccumulator();
}


Physics::Vecteur3D Physics::Rigidbody::getLinearVelocity() const {
	return linearVelocity;
}

Physics::Vecteur3D Physics::Rigidbody::getAngularVelocity() const {
	return angularVelocity;
}

Physics::PrimitiveCollider* Physics::Rigidbody::getCollider() const {
	return col;
}

Physics::Matrix34 Physics::Rigidbody::getTransform() const {
	return transformMatrix;
}

float Physics::Rigidbody::getMass() const {
	return masse;
}

Physics::Vecteur3D Physics::Rigidbody::getPosition() const {
	return position;
}

Physics::Quaternion Physics::Rigidbody::getRotation() const {
	return orientation;
}

std::string Physics::Rigidbody::getGameObjectFilePath() const
{
	return gameObjectFilePath;
}

void Physics::Rigidbody::SetRotation(const Physics::Quaternion& newRotation) {
	orientation = newRotation;
}

void Physics::Rigidbody::SetPosition(const Physics::Vecteur3D& newPosition) {
	position = newPosition;
}

void Physics::Rigidbody::SetLinearVelocity(const Physics::Vecteur3D& newVelocity) {
	linearVelocity = newVelocity;
}

void Physics::Rigidbody::SetAngularVelocity(const Physics::Vecteur3D& newVelocity) {
	angularVelocity = newVelocity;
}

void Physics::Rigidbody::AddForce(const Vecteur3D& force)
{
	m_forceAccum += force;
}

void Physics::Rigidbody::AddForceAtPoint(const Vecteur3D& force, const Vecteur3D& worldPoint)
{
	m_forceAccum += force;
	Vecteur3D localPoint = worldPoint - position;
	m_torqueAccum += localPoint.cross(force);
}

void Physics::Rigidbody::AddForceAtBodyPoint(const Vecteur3D& force, const Vecteur3D& localPoint)
{
	m_forceAccum += force;
	m_torqueAccum += localPoint ^ force;
}

void Physics::Rigidbody::ClearAccumulator()
{
	m_forceAccum = Vecteur3D::vecteurNull();
	m_torqueAccum = Vecteur3D::vecteurNull();
}
