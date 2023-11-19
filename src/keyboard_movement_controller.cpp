#include "keyboard_movement_controller.hpp"

//Libs
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // Pour glm::lookAt
#include <glm/gtc/quaternion.hpp> // Pour glm::quat


namespace Visual {

	void KeyboardMovementController::moveInPlaneXZ(GLFWwindow* window, float dt, VGameObject& gameObject)
	{
		// Rotation
		glm::vec3 rotate{ 0.f };
		if (glfwGetKey(window, keys.lookRight) == GLFW_PRESS) rotate.y += 1.f;
		if (glfwGetKey(window, keys.lookLeft) == GLFW_PRESS) rotate.y -= 1.f;
		if (glfwGetKey(window, keys.lookUp) == GLFW_PRESS) rotate.x += 1.f;
		if (glfwGetKey(window, keys.lookDown) == GLFW_PRESS) rotate.x -= 1.f;

		if (glm::dot(rotate, rotate) > std::numeric_limits<float>::epsilon()) {
			gameObject.transform.rotation += lookSpeed * dt * glm::normalize(rotate);
		}

		gameObject.transform.rotation.x = glm::clamp(gameObject.transform.rotation.x, -1.5f, 1.5f);
		gameObject.transform.rotation.y = glm::mod(gameObject.transform.rotation.y, glm::two_pi<float>());


		// Translation
		float yaw = gameObject.transform.rotation.y;
		const glm::vec3 forwardDir{ sin(yaw), 0.f, cos(yaw) };
		const glm::vec3 rightDir{ forwardDir.z, 0.f, -forwardDir.x };
		const glm::vec3 upDir{ 0.f, -1.f, 0.f };

		glm::vec3 moveDir{ 0.f };
		if (glfwGetKey(window, keys.moveForward) == GLFW_PRESS) moveDir += forwardDir;
		if (glfwGetKey(window, keys.moveBackward) == GLFW_PRESS) moveDir -= forwardDir;
		if (glfwGetKey(window, keys.moveRight) == GLFW_PRESS) moveDir += rightDir;
		if (glfwGetKey(window, keys.moveLeft) == GLFW_PRESS) moveDir -= rightDir;
		if (glfwGetKey(window, keys.moveUp) == GLFW_PRESS) moveDir += upDir;
		if (glfwGetKey(window, keys.moveDown) == GLFW_PRESS) moveDir -= upDir;

		if (glm::dot(moveDir, moveDir) > std::numeric_limits<float>::epsilon()) {
			gameObject.transform.translation += moveSpeed * dt * glm::normalize(moveDir);
		}

		//Spawn
		if (glfwGetKey(window, keys.spawn0) == GLFW_PRESS) {
			if (!isSpawnKeyPressed) {

				FirstApp::getInstance().inputParticle(0);
				isSpawnKeyPressed = true;
			}
		}
		else if (glfwGetKey(window, keys.spawn1) == GLFW_PRESS) {
			if (!isSpawnKeyPressed) {

				FirstApp::getInstance().inputParticle(1);
				isSpawnKeyPressed = true;
			}
		}
		else if (glfwGetKey(window, keys.spawn2) == GLFW_PRESS) {
			if (!isSpawnKeyPressed) {

				FirstApp::getInstance().inputParticle(2);
				isSpawnKeyPressed = true;
			}
		}
		else if (glfwGetKey(window, keys.spawn3) == GLFW_PRESS) {
			if (!isSpawnKeyPressed) {

				FirstApp::getInstance().inputParticle(3);
				isSpawnKeyPressed = true;
			}
		}
		else if (glfwGetKey(window, keys.spawn4) == GLFW_PRESS) {
			if (!isSpawnKeyPressed) {

				FirstApp::getInstance().inputParticle(4);
				isSpawnKeyPressed = true;
			}
		}
		else if (glfwGetKey(window, keys.spawn5) == GLFW_PRESS) {
			if (!isSpawnKeyPressed) {

				FirstApp::getInstance().inputParticle(5);
				isSpawnKeyPressed = true;
			}
		}
		else if (glfwGetKey(window, keys.spawn6) == GLFW_PRESS) {
			if (!isSpawnKeyPressed) {

				FirstApp::getInstance().inputParticle(6);
				isSpawnKeyPressed = true;
			}
		}
		else {
			isSpawnKeyPressed = false;
		}

		// Quitter
		if (glfwGetKey(window, keys.close) == GLFW_PRESS) {
			FirstApp::getInstance().close();
		}
	}	
}