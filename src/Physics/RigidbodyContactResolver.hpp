#pragma once
#include "Rigidbody.hpp"
#include<vector>

namespace Physics {
	class RigidbodyContactResolver {
	public:
		RigidbodyContactResolver();
		RigidbodyContactResolver(unsigned int maxIterations);

		void setMaxIterations(unsigned int newMax);

		void resolveContacts(std::vector<RigidbodyContact> contacts, float duration);

	private:
		unsigned int maxIterations;

		unsigned int currentIteration;
	};
}