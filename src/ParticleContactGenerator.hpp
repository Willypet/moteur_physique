#pragma once
#include "ParticleContact.hpp"
#include <vector>

namespace Physics {
	class ParticleContactGenerator {
	public:
		virtual unsigned int addContact(std::vector<ParticleContact> &contacts) const = 0;
	};
}