#include "Vrenderer.hpp"

// std
#include <array>
#include <stdexcept>

namespace Visual {


    VRenderer::VRenderer(VWindow& window, VDevice& device) : v_window{window}, v_device{device} {
        recreateSwapChain();
        createCommandBuffers();
    }

    VRenderer::~VRenderer() { freeCommandBuffers(); }  

    void VRenderer::recreateSwapChain() {
        auto extent = v_window.getExtent();
        while (extent.width == 0 || extent.height == 0) {
            extent = v_window.getExtent();
            glfwWaitEvents();
        }
        vkDeviceWaitIdle(v_device.device());

        if (v_swapChain == nullptr) {
            v_swapChain = std::make_unique<VSwapChain>(v_device, extent);
        }
        else {
            std::shared_ptr<VSwapChain> oldSwapChain = std::move(v_swapChain);
            v_swapChain = std::make_unique<VSwapChain>(v_device, extent, oldSwapChain);

            if (!oldSwapChain->compareSwapFormat(*v_swapChain.get())) {
                throw std::runtime_error("Swap chain image (or depth) format has changed");
            }            
        }

    }

    VkCommandBuffer VRenderer::beginFrame()
    {
        assert(!isFrameStarted && "Cannot call begin frame while already in progress");

        auto result = v_swapChain->acquireNextImage(&currentImageIndex);
        if (result == VK_ERROR_OUT_OF_DATE_KHR) {
            recreateSwapChain();
            return nullptr;
        }
        if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
            throw std::runtime_error("failed to acquire swap chain image!");
        }

        isFrameStarted = true;
        auto commandBuffer = getCurrentCommandBuffer();

        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
            throw std::runtime_error("failed to begin recording command buffer!");
        }

        return commandBuffer;
    }

    void VRenderer::endFrame()
    {
        assert(isFrameStarted && "Cannot call endframe while frame is not in progress");
        auto commandBuffer = getCurrentCommandBuffer();

        if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
            throw std::runtime_error("failed to record command buffer!");
        }

        auto result = v_swapChain->submitCommandBuffers(&commandBuffer, &currentImageIndex);
        if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || v_window.wasWindowResized()) {
            v_window.resetWindowResizedFlag();
            recreateSwapChain();
        }
        else if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to present swap chain image!");
        }

        isFrameStarted = false;
        currentFrameIndex = (currentFrameIndex + 1) % VSwapChain::MAX_FRAMES_IN_FLIGHT;
    }

    void VRenderer::beginSwapChainRenderPass(VkCommandBuffer commandBuffer)
    {
        assert(isFrameStarted && "Cannot call beginSwapChainrenderPass while frame is not in progress");
        assert(commandBuffer == getCurrentCommandBuffer() && "Cannot begin render pass on commandbuffer from a different frame");

        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = v_swapChain->getRenderPass();
        renderPassInfo.framebuffer = v_swapChain->getFrameBuffer(currentImageIndex);

        renderPassInfo.renderArea.offset = { 0, 0 };
        renderPassInfo.renderArea.extent = v_swapChain->getSwapChainExtent();

        std::array<VkClearValue, 2> clearValues{};
        clearValues[0].color = { 0.01f, 0.01f, 0.01f, 1.0f }; //nackground color
        clearValues[1].depthStencil = { 1.0f, 0 };
        renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
        renderPassInfo.pClearValues = clearValues.data();

        vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        VkViewport viewport{};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = static_cast<float>(v_swapChain->getSwapChainExtent().width);
        viewport.height = static_cast<float>(v_swapChain->getSwapChainExtent().height);
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;
        VkRect2D scissor{ {0, 0}, v_swapChain->getSwapChainExtent() };
        vkCmdSetViewport(commandBuffer, 0, 1, &viewport);
        vkCmdSetScissor(commandBuffer, 0, 1, &scissor);
    }

    void VRenderer::endSwapChainRenderPass(VkCommandBuffer commandBuffer)
    {
        assert(isFrameStarted && "Cannot call endSwapChainrenderPass while frame is not in progress");
        assert(commandBuffer == getCurrentCommandBuffer() && "Cannot end render pass on commandbuffer from a different frame");

        vkCmdEndRenderPass(commandBuffer);
    }
    

    void VRenderer::createCommandBuffers() {
        commandBuffers.resize(VSwapChain::MAX_FRAMES_IN_FLIGHT);

        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = v_device.getCommandPool();
        allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

        if (vkAllocateCommandBuffers(v_device.device(), &allocInfo, commandBuffers.data()) !=
            VK_SUCCESS) {
            throw std::runtime_error("failed to allocate command buffers!");
        }
    }

    void VRenderer::freeCommandBuffers()
    {
        vkFreeCommandBuffers(
            v_device.device(),
            v_device.getCommandPool(),
            static_cast<float>(commandBuffers.size()),
            commandBuffers.data());
        commandBuffers.clear();
    }
}  // namespace V