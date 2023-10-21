#pragma once

#include "Vdevice.hpp"

// libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

// std
#include <memory>
#include <vector>

namespace Visual {
    class VModel {
    public:
        struct Vertex {
            glm::vec3 position{};
            glm::vec3 color{};
            glm::vec3 normal{};
            glm::vec2 uv{};
        
          static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
          static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();

          bool operator==(const Vertex& other) const {
              return position == other.position && color == other.color && uv == other.uv;
          }
        };
        

        struct Builder {
            std::vector<Vertex> vertices{};
            std::vector<uint32_t> indices{};

            void loadModel(const std::string& filePath);
        };
        

        VModel(VDevice &device, const VModel::Builder& builder);
        ~VModel();
        
        VModel(const VModel &) = delete;
        VModel &operator=(const VModel &) = delete;
        
        static std::unique_ptr<VModel> createModelFromFile(VDevice& device, const std::string& filePath);
        void bind(VkCommandBuffer commandBuffer);
        void draw(VkCommandBuffer commandBuffer);
        
    private:        
        VDevice& v_device;
        
        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;
        uint32_t vertexCount;

        bool hasIndexBuffer = false;
        VkBuffer indexBuffer;
        VkDeviceMemory indexBufferMemory;
        uint32_t indexCount;

        void createVertexBuffers(const std::vector<Vertex>& vertices);
        void createIndexBuffer(const std::vector<uint32_t>& indices);

    };
}  // namespace V
