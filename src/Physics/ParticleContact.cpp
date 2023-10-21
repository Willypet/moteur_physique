#include "ParticleContact.hpp"

namespace Physics {

	void ParticleContact::resolve(float duration) {
		resolveVelocity(duration);
		resolveInterpenetration(duration);
	}

	float ParticleContact::computeVelocity() const {
		Vecteur3D velocity = particles[0]->getVitesse();
		if (particles[1] != nullptr) {
			velocity -= particles[1]->getVitesse();
		}
		return Vecteur3D::dot(velocity, normal);
	}

	void ParticleContact::resolveVelocity(float duration) {
		float separatingVelocity = computeVelocity();

		if (separatingVelocity >= 0) //Contact au repos ou déjà en éloignement
		{
			return;
		}

		float resultingVelocity = -separatingVelocity * restitution;

		Vecteur3D accVelocity = particles[0]->getAcceleration();
		if (particles[1] != nullptr)
		{
			accVelocity -= particles[1]->getAcceleration();
		}
		float accSeparatingVelocity = duration * Vecteur3D::dot(accVelocity, normal);

		if (accSeparatingVelocity < 0)
		{
			resultingVelocity += restitution * accSeparatingVelocity;

			if (resultingVelocity < 0) {
				resultingVelocity = 0;
			}
		}

		float toApply = resultingVelocity - separatingVelocity;

		float sumInverseMass = 1 / particles[0]->getMasse();
		if (particles[1] != nullptr) {
			sumInverseMass += 1 / particles[1]->getMasse();
		}

		if (sumInverseMass <= 0) //Objets de masse infinie (i.e statiques)
		{ 
			return;
		}

		float impulseValueIMass = toApply / sumInverseMass;

		Vecteur3D impulseVector = normal * impulseValueIMass;

		particles[0]->setVitesse(particles[0]->getVitesse() + impulseVector / particles[0]->getMasse());
		if (particles[1] != nullptr) {
			particles[1]->setVitesse(particles[1]->getVitesse() - impulseVector / particles[1]->getMasse());
		}
	}

	void ParticleContact::resolveInterpenetration(float duration) {
		if (penetration <= 0) {
			return;
		}

		float sumInverseMass = 1 / particles[0]->getMasse();
		if (particles[1] != nullptr) {
			sumInverseMass += 1 / particles[1]->getMasse();
		}

		if (sumInverseMass <= 0) //Objets de masse infinie (i.e statiques)
		{
			return;
		}

		Vecteur3D moveIMass = normal * (penetration / sumInverseMass);

		particles[0]->setPosition(particles[0]->getPosition() + moveIMass / particles[0]->getMasse());
		if (particles[1] != nullptr)
		{
			particles[1]->setPosition(particles[1]->getPosition() - moveIMass / particles[1]->getMasse());
		}
	}
}