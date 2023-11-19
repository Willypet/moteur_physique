#pragma once

#include "Visual/Vdevice.hpp"
#include "Visual/Vwindow.hpp"
#include "Visual/Vgame_object.hpp"
#include "Visual/Vrenderer.hpp"

#include "Physics/Particule.hpp"
#include "Physics/Vecteur3D.hpp"
#include "Physics/Rigidbody.hpp"
#include "Physics/PhysicsCore.hpp"
#include "Physics/RigidPhysicsCore.hpp"

// std
#include <memory>
#include <map>
#include <vector>
#include <string>

namespace Visual {
	class FirstApp {
	public:
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 600;
		
		static FirstApp& getInstance() {
			static FirstApp instance; // Instance unique de la classe
			return instance;
		}

		void close() {shouldClose = true;}
		
		void run();
		void inputParticle(int app);
		
	private:	
		FirstApp();
		~FirstApp();

		FirstApp(const FirstApp&) = delete;
		FirstApp& operator=(const FirstApp&) = delete;

		bool shouldClose;

		void loadGameObjects(Physics::Particule* particule);
		void loadGameObjects(Physics::Rigidbody* body);
		void spawnParticule(Physics::Particule* particule);
		void spawnBody(Physics::Rigidbody* body);
		
		void resetApp();
		void App0();
		void App1();
		void App2();
		void App3();
		void App4();
		void App5();
		void App6();
		void App7();
		
		VWindow VWindow{WIDTH, HEIGHT, "Moteur Physique"};
		VDevice VDevice{VWindow};
		VRenderer VRenderer{ VWindow, VDevice };
		std::vector<Physics::Particule*> particules;
		std::vector<Physics::Rigidbody*> bodies;
		std::map<int, VGameObject> gameObjects;
		Physics::PhysicsCore physicsCore;
		Physics::RigidPhysicsCore rigidPhysicsCore;
	};
}  // namespace V