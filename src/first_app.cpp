#include "first_app.hpp"
#include "Visual/Vsimple_render_system.hpp"
#include "Visual/Vcamera.hpp"
#include "keyboard_movement_controller.hpp"

#include "Physics/ParticleGravity.hpp"
#include "Physics/NaiveParticleCollisionGenerator.hpp"

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
#include "Physics/ParticleDrag.hpp"

#define MAX_FRAME_TIME .01f
#define SIMULATION_STEP 0.016f
#define MAX_SIMULATION_ITER 10

namespace Visual {

    FirstApp::FirstApp() {
        shouldClose = false;
    }
    
    FirstApp::~FirstApp() {}
    
    void FirstApp::run() {
        VSimpleRenderSystem simpleRenderSystem{ VDevice, VRenderer.getSwapChainRenderPass() };

        VCamera camera{}; 
        float simulationTime = 0.0f;
        int currentIter = 0;

        auto viewerObject = VGameObject::createGameObject(); // garde en memoire l'etat de la camera. N'a pas de rendu
        KeyboardMovementController cameraController{};

        auto currentTime = std::chrono::high_resolution_clock::now();

        while (!VWindow.shouldClose() && !shouldClose) {
            glfwPollEvents();

            auto newTime = std::chrono::high_resolution_clock::now();
            float frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
            currentTime = newTime;

            simulationTime += frameTime;

            //SIMULATION PHYSIQUE
            currentIter = 0;
            while (simulationTime >= SIMULATION_STEP && currentIter < MAX_SIMULATION_ITER){
                simulationTime -= SIMULATION_STEP;
                currentIter += 1;
                physicsCore.UpdateAll(SIMULATION_STEP, 2);
            }

            //DEPLACEMENT VISUEL
            for (auto particule : particules)
            {   
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

    void FirstApp::inputParticle(int app = 0)
    {
        resetApp();

        switch (app)
        {
        case 1:
            App1();
            break;
        default:
            App0();
            break;
        }
        
        
        
    }

    void FirstApp::resetApp()
    {
        gameObjects.clear();
        particules.clear();
    }

    void FirstApp::App0() {
        Physics::ParticleGravity* gravity1 = new Physics::ParticleGravity(Physics::Vecteur3D(0.5, 0, 0));
        Physics::ParticleGravity* gravity3 = new Physics::ParticleGravity(Physics::Vecteur3D(0.3, 0, 0));
        Physics::ParticleGravity* gravity4 = new Physics::ParticleGravity(Physics::Vecteur3D(-.1, 0, 0));
        Physics::ParticleGravity* gravity5 = new Physics::ParticleGravity(Physics::Vecteur3D(0, -.2, 0));

        //vitesse initale nulle, acceleration constante
        auto particule1 = new Physics::Particule{ .1, 1, Physics::Vecteur3D(0,0,2), Physics::Vecteur3D(0,0,0), Physics::Vecteur3D(0,0,0), "models/cube_rouge.obj" };
        spawnParticule(particule1);
        physicsCore.AddParticle(particule1);
        physicsCore.AddForce(gravity1, particule1);
        //vitesse constante, acceleration nulle
        auto particule2 = new Physics::Particule{ .1, 1, Physics::Vecteur3D(0,-0.5,2), Physics::Vecteur3D(.5,0,0), Physics::Vecteur3D(0,0,0), "models/cube_vert.obj" };
        spawnParticule(particule2);
        physicsCore.AddParticle(particule2);
        //vitesse initiale + acceleration constante dans la meme direction
        auto particule3 = new Physics::Particule{ .1, 1, Physics::Vecteur3D(0,.5,2), Physics::Vecteur3D(.4,0,0), Physics::Vecteur3D(0,0,0), "models/cube_bleu.obj" };
        spawnParticule(particule3);
        physicsCore.AddParticle(particule3);
        physicsCore.AddForce(gravity3, particule1);
        //vitesse initale + acceleration constante opposee
        auto particule4 = new Physics::Particule{ .1, 1, Physics::Vecteur3D(0,1,2), Physics::Vecteur3D(.7,0,0), Physics::Vecteur3D(0,0,0), "models/cube_jaune.obj" };
        spawnParticule(particule4);
        physicsCore.AddParticle(particule4);
        physicsCore.AddForce(gravity4, particule1);
        //montre que les coordonnes sont en 3D
        auto particule5 = new Physics::Particule{ .1, 1, Physics::Vecteur3D(1,-1,5), Physics::Vecteur3D(-.5,.5,-.5), Physics::Vecteur3D(0,0,0), "models/colored_cube.obj" };
        spawnParticule(particule5);
        physicsCore.AddParticle(particule5);
        physicsCore.AddForce(gravity5, particule1);
    }

    void FirstApp::App1() {
        Physics::ParticleGravity* gravity = new Physics::ParticleGravity(Physics::Vecteur3D(0, 1, 0));
        Physics::ParticleDrag* drag = new Physics::ParticleDrag(.1, .5);

        auto particule0 = new Physics::Particule{ 0.2, 3, Physics::Vecteur3D(0,-3,5), Physics::Vecteur3D(0,0,0), Physics::Vecteur3D(0,0,0), "models/sphere_rouge.obj" };
        spawnParticule(particule0);
        physicsCore.AddParticle(particule0);

        auto particule1 = new Physics::Particule{ 0.1, 1, Physics::Vecteur3D(0,0,5), Physics::Vecteur3D(), Physics::Vecteur3D(), "models/sphere_jaune.obj" };
        spawnParticule(particule1);
        physicsCore.AddParticle(particule1);

        auto particule2 = new Physics::Particule{ 0.1, .2, Physics::Vecteur3D(.1,.2,5), Physics::Vecteur3D(), Physics::Vecteur3D(), "models/sphere_vert.obj" };
        spawnParticule(particule2);
        physicsCore.AddParticle(particule2);

        auto particule3 = new Physics::Particule{ 0.1, 1, Physics::Vecteur3D(-.1,.2,5), Physics::Vecteur3D(), Physics::Vecteur3D(), "models/sphere_jaune.obj" };
        spawnParticule(particule3);
        physicsCore.AddParticle(particule3);

        auto particule4 = new Physics::Particule{ 0.1, .2, Physics::Vecteur3D(.2,.4,5), Physics::Vecteur3D(), Physics::Vecteur3D(), "models/sphere_vert.obj" };
        spawnParticule(particule4);
        physicsCore.AddParticle(particule4);

        auto particule5 = new Physics::Particule{ 0.1, .2, Physics::Vecteur3D(0,.4,5), Physics::Vecteur3D(), Physics::Vecteur3D(), "models/sphere_vert.obj" };
        spawnParticule(particule5);
        physicsCore.AddParticle(particule5);

        auto particule6 = new Physics::Particule{ 0.1, 1, Physics::Vecteur3D(-.2,.4,5), Physics::Vecteur3D(), Physics::Vecteur3D(), "models/sphere_jaune.obj" };
        spawnParticule(particule6);
        physicsCore.AddParticle(particule6);

        auto particule7 = new Physics::Particule{ 0.1, .2, Physics::Vecteur3D(.3,.6,5), Physics::Vecteur3D(), Physics::Vecteur3D(), "models/sphere_vert.obj" };
        spawnParticule(particule7);
        physicsCore.AddParticle(particule7);

        auto particule8 = new Physics::Particule{ 0.1, .2, Physics::Vecteur3D(.1,.6,5), Physics::Vecteur3D(), Physics::Vecteur3D(), "models/sphere_vert.obj" };
        spawnParticule(particule8);
        physicsCore.AddParticle(particule8);

        auto particule9 = new Physics::Particule{ 0.1, 1, Physics::Vecteur3D(-.1,.6,5), Physics::Vecteur3D(), Physics::Vecteur3D(), "models/sphere_jaune.obj" };
        spawnParticule(particule9);
        physicsCore.AddParticle(particule9);

        auto particule10 = new Physics::Particule{ 0.1, 1, Physics::Vecteur3D(-.3,.6,5), Physics::Vecteur3D(), Physics::Vecteur3D(), "models/sphere_jaune.obj" };
        spawnParticule(particule10);
        physicsCore.AddParticle(particule10);


        Physics::NaiveParticleCollisionGenerator* collisionGenerator = new Physics::NaiveParticleCollisionGenerator;
        collisionGenerator->particles = std::vector<Physics::Particule*>({ particule0, particule1, particule2, particule3, particule4, particule5, particule6, particule7, particule8, particule9, particule10 });
        physicsCore.AddContactGenerator(collisionGenerator);
        physicsCore.AddForce(gravity, particule0);
        physicsCore.AddForce(drag, std::vector<Physics::Particule*>{particule1, particule2, particule3, particule4, particule5, particule6});

    }

    void FirstApp::loadGameObjects(Physics::Particule* particule) {
        std::shared_ptr<VModel> VModel = VModel::createModelFromFile(VDevice, particule->getGameObjectFilePath());

        auto object = VGameObject::createGameObject();
        object.model = VModel;
        object.transform.translation = glm::vec3{particule->getPosition().x, particule->getPosition().y, particule->getPosition().z};
        object.transform.scale = glm::vec3{ particule->getRadius()};
        particule->idGameObject = object.getId();
        gameObjects.emplace(object.getId(), std::move(object));
    }   

    void FirstApp::spawnParticule(Physics::Particule* particule) {
        //auto particule = new Physics::Particule{1, Physics::Vecteur3D(0,0,2), Physics::Vecteur3D(0,0,0), Physics::Vecteur3D(.5,0,0), gameObjectFilePath};
        particules.push_back(std::move(particule));
        loadGameObjects(particule);
    }
}  // namespace V