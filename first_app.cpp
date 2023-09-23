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
        shouldClose = false;
    }
    
    FirstApp::~FirstApp() {}
    
    void FirstApp::run() {
        VSimpleRenderSystem simpleRenderSystem{ VDevice, VRenderer.getSwapChainRenderPass() };

        VCamera camera{}; 

        auto viewerObject = VGameObject::createGameObject(); // garde en memoire l'etat de la camera. N'a pas de rendu
        KeyboardMovementController cameraController{};

        auto currentTime = std::chrono::high_resolution_clock::now();

        while (!VWindow.shouldClose() && !shouldClose) {
            glfwPollEvents();

            auto newTime = std::chrono::high_resolution_clock::now();
            float frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
            currentTime = newTime;

            frameTime = glm::min(frameTime, MAX_FRAME_TIME);

            //DEPLACEMENT OBJETS
            for (auto particule : particules)
            {
                particule->update(frameTime);
                
                auto gameObjectIterator = gameObjects.find(particule->idGameObject);
                if (gameObjectIterator != gameObjects.end()) {
                    VGameObject& gameObject = gameObjectIterator->second; 
                    gameObject.transform.translation = glm::vec3{particule->getPosition().x, particule->getPosition().y, particule->getPosition().z };
                }
            }

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

    void FirstApp::inputParticle()
    {
        //vitesse initalie nulle, acceleration constante
        auto particule1 = new Physics::Particule{ 1, Physics::Vecteur3D(0,0,2), Physics::Vecteur3D(0,0,0), Physics::Vecteur3D(.5,0,0), "models/cube_rouge.obj" };
        spawnParticule(particule1);
        //vitesse constante, acceleration nulle
        auto particule2 = new Physics::Particule{ 1, Physics::Vecteur3D(0,-0.5,2), Physics::Vecteur3D(.5,0,0), Physics::Vecteur3D(0,0,0), "models/cube_vert.obj" };
        spawnParticule(particule2);
        //vitesse initiale + acceleration constante dans la meme direction
        auto particule3 = new Physics::Particule{ 1, Physics::Vecteur3D(0,.5,2), Physics::Vecteur3D(.4,0,0), Physics::Vecteur3D(.3,0,0), "models/cube_bleu.obj" };
        spawnParticule(particule3);
        //vitesse initale + acceleration constante opposee
        auto particule4 = new Physics::Particule{ 1, Physics::Vecteur3D(0,1,2), Physics::Vecteur3D(.7,0,0), Physics::Vecteur3D(-.1,0,0), "models/cube_jaune.obj" };
        spawnParticule(particule4);
        //montre que les coordonnes sont en 3D
        auto particule5 = new Physics::Particule{ 1, Physics::Vecteur3D(1,-1,5), Physics::Vecteur3D(-.5,.5,-.5), Physics::Vecteur3D(0,-.2,0), "models/colored_cube.obj" };
        spawnParticule(particule5);
    }

    void FirstApp::loadGameObjects(Physics::Particule* particule) {
        std::shared_ptr<VModel> VModel = VModel::createModelFromFile(VDevice, particule->getGameObjectFilePath());

        auto object = VGameObject::createGameObject();
        object.model = VModel;
        object.transform.translation = glm::vec3{particule->getPosition().x, particule->getPosition().y, particule->getPosition().z};
        object.transform.scale = glm::vec3{ .1f, .1f, .1f };
        particule->idGameObject = object.getId();
        gameObjects.emplace(object.getId(), std::move(object));
    }   

    void FirstApp::spawnParticule(Physics::Particule* particule) {
        //auto particule = new Physics::Particule{1, Physics::Vecteur3D(0,0,2), Physics::Vecteur3D(0,0,0), Physics::Vecteur3D(.5,0,0), gameObjectFilePath};
        particules.push_back(std::move(particule));
        loadGameObjects(particule);
    }
}  // namespace V