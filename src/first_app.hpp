#pragma once

#include "Visual/Vdevice.hpp"
#include "Visual/Vwindow.hpp"
#include "Visual/Vgame_object.hpp"
#include "Visual/Vrenderer.hpp"

#include "Physics/Particule.hpp"
#include "Physics/Vecteur3D.hpp"
#include "Physics/PhysicsCore.hpp"

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
		void inputParticle();
		
	private:	
		FirstApp();
		~FirstApp();

		FirstApp(const FirstApp&) = delete;
		FirstApp& operator=(const FirstApp&) = delete;

		bool shouldClose;

		void loadGameObjects(Physics::Particule* particule);
		void spawnParticule(Physics::Particule* particule);
		
		VWindow VWindow{WIDTH, HEIGHT, "Moteur Physique"};
		VDevice VDevice{VWindow};
		VRenderer VRenderer{ VWindow, VDevice };
		std::vector<Physics::Particule*> particules;
		std::map<int, VGameObject> gameObjects;
		Physics::PhysicsCore physicsCore;
	};
}  // namespace V