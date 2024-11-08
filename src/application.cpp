#include "application.h"

#include <stdexcept>

namespace GeckoEngine
{
    Application::Application()
    {
        createPipelineLayout();
        createPipeline();
        createCommandBuffers();
    }

    Application::~Application()
    {
        vkDestroyPipelineLayout(device.device(), pipelineLayout, nullptr);
    }

    void Application::run()
    {
        while (!window.shouldClose())
        {
            glfwPollEvents();
        }
    }

    void Application::createPipelineLayout()
    {
        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = 0;
        pipelineLayoutInfo.pSetLayouts = nullptr;
        pipelineLayoutInfo.pushConstantRangeCount = 0;
        pipelineLayoutInfo.pPushConstantRanges = nullptr;
        if (vkCreatePipelineLayout(device.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create pipeline layout.");
        }
    }

    void Application::createPipeline()
    {
        auto pipelineConfig = GraphicsPipeline::defaultPipelineConfigInfo(swapChain.width(), swapChain.height());
        pipelineConfig.renderPass = swapChain.getRenderPass();
        pipelineConfig.pipelineLayout = pipelineLayout;
        graphicsPipeline = std::make_unique<GraphicsPipeline>(
            device,
            "shaders/simple.vert.spv",
            "shaders/simple.frag.spv",
            pipelineConfig);
    }

    void Application::createCommandBuffers()
    {
    }

    void Application::drawFrame()
    {
    }
} // namespace GeckoEngine
