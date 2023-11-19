#include "Rigidbody.hpp"
#include <math.h>

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

Physics::Rigidbody::Rigidbody(const float _masse, const Vecteur3D& _position, const Quaternion _orientation, Collider _col, const std::string& getGameObjectFilePath) :
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
	transformMatrix.SetOrientationAndPosition(orientation, position);

	Vecteur3D linearAcc = 1 / masse * m_forceAccum;

	Matrix3 orientationMatrix = Matrix3();
	orientationMatrix.SetOrientation(orientation);
	Matrix3 globalInverseInertiaTensor = orientationMatrix.Transpose() * col.GetInverseInertiaTensor() * orientationMatrix;

	Vecteur3D angularAcc = globalInverseInertiaTensor * m_torqueAccum;

	linearVelocity = linearVelocity * pow(linearDamping, duration) + linearAcc * duration;
	angularVelocity = angularVelocity * pow(angularDamping, duration) + angularAcc * duration;

	ClearAccumulator();
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
