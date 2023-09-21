#pragma once

#include "Vdevice.hpp"
#include "Vswap_chain.hpp"
#include "Vwindow.hpp"

// std
#include <cassert>
#include <memory>
#include <vector>

namespace Visual {
	class VRenderer {
	public:
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 600;

		VRenderer(VWindow& window, VDevice& device);
		~VRenderer();

		VRenderer(const VRenderer&) = delete;
		VRenderer& operator=(const VRenderer&) = delete;

		VkRenderPass getSwapChainRenderPass() const { return v_swapChain->getRenderPass(); }
		float getAspectRatio() const { return v_swapChain->extentAspectRatio(); }
		bool isFrameInProgress() const { return isFrameStarted; }
		VkCommandBuffer getCurrentCommandBuffer() const { 
			assert(isFrameStarted && "Cannot get command buffer when frame not in progess");
			return commandBuffers[currentFrameIndex]; 
		}

		int getFrameIndex() const {
			assert(isFrameStarted && "Cannot get frame index when frame not in progess");
			return currentFrameIndex;
		}

		VkCommandBuffer beginFrame();
		void endFrame();
		void beginSwapChainRenderPass(VkCommandBuffer commandBuffer);
		void endSwapChainRenderPass(VkCommandBuffer commandBuffer);

	private:		
		void createCommandBuffers();
		void freeCommandBuffers();
		void recreateSwapChain();

		VWindow& v_window;
		VDevice& v_device;
		std::unique_ptr <VSwapChain> v_swapChain;
		std::vector<VkCommandBuffer> commandBuffers;

		uint32_t currentImageIndex;
		int currentFrameIndex{ 0 };
		bool isFrameStarted{ false };
	};
}  // namespace V