#include "Rigidbody.hpp"

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

Physics::Rigidbody::Rigidbody(const float _masse, const Vecteur3D& _position, const Quaternion _orientation, const std::string& getGameObjectFilePath) :
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
	transformMatrix.SetOrientationAndPosition(orientation, position);
}

void Physics::Rigidbody::Integrate(float duration)
{
	position = position + linearVelocity * duration;
	orientation.UpdateByAngularVelocity(angularVelocity, duration);
	transformMatrix.SetOrientationAndPosition(orientation, position);

	Vecteur3D linearAcc = 1 / masse * m_forceAccum;
	Vecteur3D angularAcc = m_torqueAccum; // TODO multiplier par I^-1

	linearVelocity = linearVelocity + linearAcc * duration; //TODO multiplier linearVelocity par damp^t
	angularVelocity = angularVelocity + angularAcc * duration; //TODO multiplier angularVelocity par damp^t

	ClearAccumulator();
}

void Physics::Rigidbody::AddForce(const Vecteur3D& force)
{
	m_forceAccum += force;
}

void Physics::Rigidbody::AddForceAtPoint(const Vecteur3D& force, const Vecteur3D& worldPoint)
{
	//TODO
}

void Physics::Rigidbody::AddForceAtBodyPoint(const Vecteur3D& force, const Vecteur3D& localdPoint)
{
	//TODO
}

void Physics::Rigidbody::ClearAccumulator()
{
	m_forceAccum = Vecteur3D::vecteurNull();
	m_torqueAccum = Vecteur3D::vecteurNull();
}
