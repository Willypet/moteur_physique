#pragma once

#include "Vmodel.hpp"

//libs 
#include <glm/gtc/matrix_transform.hpp>

//std
#include <memory>

namespace Visual {

	struct TransformComponent {
		glm::vec3 translation{}; //position offset
		glm::vec3 scale{ 1.f, 1.f, 1.f };
		glm::vec3 rotation{.0f, .0f, .0f};

		//matrice correspondant à translate * Ry * Rx * Rz * scale
		//La convention de rotation utilise les angles de taie-bryan avec l'ordre des axes Y(1), X(2) et Z(3)
		// Cette rotation est intrinseque (locale). Pour une rotation extrinseque (globale) il suffit de faire l'inverse : Z(3), X(2), y(1)
		// https://en.wikipedia.org/wiki/Euler_angles#Rotation_matrix
		glm::mat4 mat4();
		glm::mat3 normalMatrix();
	};	

	class VGameObject {
	public:
		using id_t = unsigned int;
		std::shared_ptr<VModel> model{};
		//glm::vec3 color{};
		TransformComponent transform{};

		static VGameObject createGameObject() {
			static id_t currentId = 0;
			return VGameObject{ currentId++ };			
		}
		VGameObject(const VGameObject&) = delete;
		VGameObject &operator=(const VGameObject&) = delete;
		VGameObject(VGameObject&&) = default;
		VGameObject &operator=(VGameObject&&) = default;
		
		const id_t getId() { return id; };		

	private:
		id_t id;

		VGameObject(id_t objId):id{objId}{
		}
	};
}