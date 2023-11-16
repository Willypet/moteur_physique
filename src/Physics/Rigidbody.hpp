#pragma once

#include "Vecteur3D.hpp"
#include "Quaternion.hpp"
#include "Matrix34.hpp"

#include <string>

namespace Physics {
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

		Vecteur3D m_forceAccum;
		Vecteur3D m_torqueAccum;

		std::string gameObjectFilePath;

		void CalculateDerivedData();

	public:
		Rigidbody(const std::string& gameObjectFilePath);
		Rigidbody(const Vecteur3D position, const Quaternion orientation, const std::string& gameObjectFilePath);
		Rigidbody(const float masse, const Vecteur3D& position, const Quaternion orientation, const std::string& getGameObjectFilePath);

		int idGameObject;

		void Integrate(float duration);

		void AddForce(const Vecteur3D& force);
		void AddForceAtPoint(const Vecteur3D& force, const Vecteur3D& worldPoint);
		void AddForceAtBodyPoint(const Vecteur3D& force, const Vecteur3D& localdPoint);
		void ClearAccumulator();
	};
}