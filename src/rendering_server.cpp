#include "rendering_server.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include <stdexcept>

namespace GeckoEngine
{
    struct SimplePushConstantData
    {
        glm::mat4 transform{1.0f};
        glm::mat4 normalMatrix{1.0f};
    };

    RenderingServer::RenderingServer(Device &device, VkRenderPass renderPass) : device{device}
    {
        createPipelineLayout();
        createPipeline(renderPass);
    }

    RenderingServer::~RenderingServer()
    {
        vkDestroyPipelineLayout(device.device(), pipelineLayout, nullptr);
    }

    void RenderingServer::renderObjects(FrameInfo &frameInfo, std::vector<Object> &objects)
    {
        graphicsPipeline->bind(frameInfo.commandBuffer);

        auto projectionView = frameInfo.camera.getProjection() * frameInfo.camera.getView();

        for (auto &obj : objects)
        {
            SimplePushConstantData push{};
            push.transform = projectionView * obj.transform.mat4();
            push.normalMatrix = obj.transform.normalMatrix();

            vkCmdPushConstants(
                frameInfo.commandBuffer,
                pipelineLayout,
                VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
                0,
                sizeof(SimplePushConstantData),
                &push);

            obj.model->bind(frameInfo.commandBuffer);
            obj.model->draw(frameInfo.commandBuffer);
        }
    }

    void RenderingServer::createPipelineLayout()
    {
        VkPushConstantRange pushConstantRange{};
        pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
        pushConstantRange.offset = 0;
        pushConstantRange.size = sizeof(SimplePushConstantData);

        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = 0;
        pipelineLayoutInfo.pSetLayouts = nullptr;
        pipelineLayoutInfo.pushConstantRangeCount = 1;
        pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;

        if (vkCreatePipelineLayout(device.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create pipeline layout.");
        }
    }

    void RenderingServer::createPipeline(VkRenderPass renderPass)
    {
        assert(pipelineLayout != nullptr && "Cannot create pipeline before pipeline layout.");

        PipelineConfigInfo pipelineConfig{};
        GraphicsPipeline::defaultPipelineConfigInfo(pipelineConfig);
        pipelineConfig.renderPass = renderPass;
        pipelineConfig.pipelineLayout = pipelineLayout;

        graphicsPipeline = std::make_unique<GraphicsPipeline>(
            device,
            "shaders/simple.vert.spv",
            "shaders/simple.frag.spv",
            pipelineConfig);
    }
}