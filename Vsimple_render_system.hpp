#pragma once

#include "Vdevice.hpp"
#include "Vpipeline.hpp"
#include "Vgame_object.hpp"
#include "Vcamera.hpp"

// std
#include <memory>
#include <vector>

namespace Visual {
	class VSimpleRenderSystem {
	public:
		VSimpleRenderSystem(VDevice& device, VkRenderPass renderPass);
		~VSimpleRenderSystem();

		VSimpleRenderSystem(const VSimpleRenderSystem&) = delete;
		VSimpleRenderSystem& operator=(const VSimpleRenderSystem&) = delete;	

		void renderGameObjects(VkCommandBuffer commandeBuffer, std::vector<VGameObject> & gameObjects, const VCamera& camera);

	private:		
		void createPipelineLayout();
		void createPipeline(VkRenderPass renderPass);

		VDevice& v_device;

		std::unique_ptr<VPipeline> v_pipeline;
		VkPipelineLayout pipelineLayout;
	};
}  // namespace V