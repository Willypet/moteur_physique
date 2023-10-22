#include "ParticleLink.hpp"

namespace Physics {
	float ParticleLink::getLength() const{
		return (particles[0]->getPosition() - particles[1]->getPosition()).magnitude();
	}
}