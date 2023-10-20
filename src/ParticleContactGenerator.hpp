#pragma once
#include "ParticleContact.hpp"
#include <vector>

namespace Physics {
	class ParticleContactGenerator {
	public:
		virtual void addContact(std::vector<ParticleContact> &contacts) const = 0;
	};
}