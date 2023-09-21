#pragma once

#include "Vdevice.hpp"
#include "Vwindow.hpp"
#include "Vgame_object.hpp"
#include "Vrenderer.hpp"

// std
#include <memory>
#include <vector>

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
  void loadGameObjects();
  
  VWindow VWindow{WIDTH, HEIGHT, "Hello Vulkan!"};
  VDevice VDevice{VWindow};
  VRenderer VRenderer{ VWindow, VDevice };

  std::vector<VGameObject> gameObjects;
};
}  // namespace V