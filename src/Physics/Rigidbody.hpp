#pragma once

#include "Vecteur3D.hpp"
#include "Quaternion.hpp"
#include "Matrix34.hpp"
#include "Matrix3.hpp"

#include <vector>
#include <string>

namespace Physics {

	//RIGIDBODY
	class PrimitiveCollider;
	class Rigidbody {
	private:
		float masse;
		float linearDamping;
		float angularDamping;

		Vecteur3D position;
		Vecteur3D linearVelocity;
		Quaternion orientation;
		Vecteur3D angularVelocity;
		Matrix34 transformMatrix;
		PrimitiveCollider* col;

		Vecteur3D m_forceAccum;
		Vecteur3D m_torqueAccum;

		std::string gameObjectFilePath;

		void CalculateDerivedData();

	public:
		Rigidbody(const std::string& gameObjectFilePath);
		Rigidbody(const Vecteur3D position, const Quaternion orientation, const std::string& gameObjectFilePath);
		Rigidbody(const float masse, const Vecteur3D& position, const Quaternion orientation, PrimitiveCollider* col, const std::string& getGameObjectFilePath);

		int idGameObject;

		void Integrate(float duration);

		Matrix34 getTransform() const;
		float getMass() const;
		Vecteur3D getPosition() const;
		Quaternion getRotation() const;
		Vecteur3D getLinearVelocity() const;
		Vecteur3D getAngularVelocity() const;
		PrimitiveCollider* getCollider() const;
		void SetRotation(const Quaternion& newRotation);
		void SetPosition(const Vecteur3D& newPosition);
		void SetLinearVelocity(const Vecteur3D& newVelocity);
		void SetAngularVelocity(const Vecteur3D& newVelocity);
		std::string getGameObjectFilePath() const;
		void AddForce(const Vecteur3D& force);
		void AddForceAtPoint(const Vecteur3D& force, const Vecteur3D& worldPoint);
		void AddForceAtBodyPoint(const Vecteur3D& force, const Vecteur3D& localPoint);
		void ClearAccumulator();
	};

	//CONTACTS
	class RigidbodyContact {
	public:
		Rigidbody* bodies[2];

		//Coefficient d'elasticité entre 0 et 1
		float restitution;

		//Interpenetration du contact
		float penetration;

		Vecteur3D contactPoint;

		Vecteur3D normal;

		float computeVelocity() const;

		void resolveVelocity(float duration);

		void resolveInterpenetration(float duration);
	};

	//COL
	class PrimitiveCollider
	{
	public:
		Rigidbody* rigidbody;
		Matrix34 offset;
		Matrix3 inverseInertiaTensor;
		Vecteur3D halfsize;

		virtual void generateContact(const PrimitiveCollider* other, std::vector<RigidbodyContact>& contacts) const = 0;
	};
}