#include "Vsimple_render_system.hpp"

// libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

// std
#include <cassert>
#include <array>
#include <stdexcept>

namespace Visual {

    struct SimplePushConstraintData {
        glm::mat4 transfom{ 1.f };
        glm::mat4 normallMatrix{ 1.f };
    };

    VSimpleRenderSystem::VSimpleRenderSystem(VDevice& device, VkRenderPass renderPass) :v_device{ device } {
        createPipelineLayout();
        createPipeline(renderPass);
    }

    VSimpleRenderSystem::~VSimpleRenderSystem() { vkDestroyPipelineLayout(v_device.device(), pipelineLayout, nullptr); }

    void VSimpleRenderSystem::createPipelineLayout() {

        VkPushConstantRange pushConstantRange{};
        pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
        pushConstantRange.offset = 0;
        pushConstantRange.size = sizeof(SimplePushConstraintData);

        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = 0;
        pipelineLayoutInfo.pSetLayouts = nullptr;
        pipelineLayoutInfo.pushConstantRangeCount = 1;
        pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;
        if (vkCreatePipelineLayout(v_device.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) !=
            VK_SUCCESS) {
            throw std::runtime_error("failed to create pipeline layout!");
        }
    }

    void VSimpleRenderSystem::createPipeline(VkRenderPass renderPass) {
        assert(pipelineLayout != nullptr && "Cannot create pipeline before pipeline layout");


        PipelineConfigInfo pipelineConfig{};
        VPipeline::defaultPipelineConfigInfo(pipelineConfig);
        pipelineConfig.renderPass = renderPass;
        pipelineConfig.pipelineLayout = pipelineLayout;
        v_pipeline = std::make_unique<VPipeline>(
            v_device,
            "shaders/simple_shader.vert.spv",
            "shaders/simple_shader.frag.spv",
            pipelineConfig);
    }

    void VSimpleRenderSystem::renderGameObjects(VkCommandBuffer commandBuffer, std::vector<VGameObject>& gameObjects, const VCamera& camera) {
        
        v_pipeline->bind(commandBuffer);

        auto projectionView = camera.getProjection() * camera.getView();

        for (auto& obj : gameObjects) {
            //update
            
            // render          
            SimplePushConstraintData push{};
            auto modelMatrix = obj.transform.mat4();
            push.transfom = projectionView * modelMatrix;
            push.normallMatrix = obj.transform.normalMatrix();

            vkCmdPushConstants(
                commandBuffer,
                pipelineLayout,
                VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
                0,
                sizeof(SimplePushConstraintData),
                &push);

            obj.model->bind(commandBuffer);
            obj.model->draw(commandBuffer);
        }
    }
}  // namespace V