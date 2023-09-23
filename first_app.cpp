#include "first_app.hpp"
#include "Vsimple_render_system.hpp"
#include "Vcamera.hpp"
#include "keyboard_movement_controller.hpp"

// libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

// std
#include <cassert>
#include <array>
#include <stdexcept>
#include <chrono>

#define MAX_FRAME_TIME .01f

namespace Visual {

    FirstApp::FirstApp() {
      loadGameObjects();     
    }
    
    FirstApp::~FirstApp() {}
    
    void FirstApp::run() {
        VSimpleRenderSystem simpleRenderSystem{ VDevice, VRenderer.getSwapChainRenderPass() };

        VCamera camera{}; 

        auto viewerObject = VGameObject::createGameObject(); // garde en memoire l'etat de la camera. N'a pas de rendu
        KeyboardMovementController cameraController{};

        auto currentTime = std::chrono::high_resolution_clock::now();

        while (!VWindow.shouldClose()) {
            glfwPollEvents();

            auto newTime = std::chrono::high_resolution_clock::now();
            float frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
            currentTime = newTime;

            frameTime = glm::min(frameTime, MAX_FRAME_TIME);

            //DEPLACEMENT OBJETS

            cameraController.moveInPlaneXZ(VWindow.getGLFWwindow(), frameTime, viewerObject);                      
            camera.setViewYXZ(viewerObject.transform.translation, viewerObject.transform.rotation);

            float aspect = VRenderer.getAspectRatio();
            camera.setPerspectiveProjection(glm::radians(50.f), aspect, .1f, 10.f); // vue perspective

            if (auto commandBuffer = VRenderer.beginFrame()) {

                //beging offscreen shadow pass
                //render shadow casting objects
                //end offsreen shadow pass

                VRenderer.beginSwapChainRenderPass(commandBuffer);
                simpleRenderSystem.renderGameObjects(commandBuffer, gameObjects, camera);
                VRenderer.endSwapChainRenderPass(commandBuffer);
                VRenderer.endFrame();
            }
        }
        
        vkDeviceWaitIdle(VDevice.device());
    }    

    void FirstApp::loadGameObjects() {
        std::shared_ptr<VModel> VModel = VModel::createModelFromFile(VDevice, "models/colored_cube.obj");

        auto smoothVase = VGameObject::createGameObject();
        smoothVase.model = VModel;
        smoothVase.transform.translation = { .5f, .5f, 2.5f };
        smoothVase.transform.scale = glm::vec3{ .5f, .5f, .5f };
        gameObjects.push_back(std::move(smoothVase));
    }   
}  // namespace V