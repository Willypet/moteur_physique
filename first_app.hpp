#pragma once

#include "Vdevice.hpp"
#include "Vwindow.hpp"
#include "Vgame_object.hpp"
#include "Vrenderer.hpp"

#include "Particule.hpp"
#include "Vecteur3D.hpp"

// std
#include <memory>
#include <vector>
#include <string>

namespace Visual {
	class FirstApp {
	public:
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 600;
		
		FirstApp();
		~FirstApp();
		
		FirstApp(const FirstApp &) = delete;
		FirstApp &operator=(const FirstApp &) = delete;
		
		void run();
		
	private:	 
		void loadGameObjects(Physics::Particule* particule);
		void spawnParticule(const std::string& gameObjectFilePath);
		
		VWindow VWindow{WIDTH, HEIGHT, "Moteur Physique"};
		VDevice VDevice{VWindow};
		VRenderer VRenderer{ VWindow, VDevice };
		
		std::vector<VGameObject> gameObjects;
	};
}  // namespace V