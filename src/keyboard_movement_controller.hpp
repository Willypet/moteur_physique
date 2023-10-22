#pragma once

#include "Visual/Vgame_object.hpp"
#include "Visual/Vwindow.hpp"
#include "first_app.hpp"

namespace Visual {
	class KeyboardMovementController {
	public :
		struct KeyMappings {            
            int moveLeft = GLFW_KEY_A;
            int moveRight = GLFW_KEY_D;
            int moveForward = GLFW_KEY_W;
            int moveBackward = GLFW_KEY_S;
            int moveUp = GLFW_KEY_SPACE;
            int moveDown = GLFW_KEY_LEFT_SHIFT;
            int lookLeft = GLFW_KEY_LEFT;
            int lookRight = GLFW_KEY_RIGHT;
            int lookUp = GLFW_KEY_UP;
            int lookDown = GLFW_KEY_DOWN;
            int spawn0 = GLFW_KEY_0;
            int spawn1 = GLFW_KEY_1;
            int spawn2 = GLFW_KEY_2;
            int spawn3 = GLFW_KEY_3;
            int spawn4 = GLFW_KEY_4;
            int spawn5 = GLFW_KEY_5;
            int close = GLFW_KEY_ESCAPE;
		};

        KeyMappings keys{};
        float moveSpeed{ 3.f };
        float lookSpeed{ 1.5f };
        float maxDistanceToTarget{.2f};
        float minDistanceToTarget{ 9.9f };
        bool isSpawnKeyPressed = false;

        void moveInPlaneXZ(GLFWwindow* window, float dt, VGameObject& gameObject);
    	};
}