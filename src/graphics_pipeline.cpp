#include "graphics_pipeline.h"

#include <fstream>
#include <iostream>

namespace GeckoEngine
{
    GraphicsPipeline::GraphicsPipeline(
        Device &device,
        const std::string &vertShaderPath,
        const std::string &fragShaderPath,
        const PipelineConfigInfo &configInfo)
        : device(device)
    {
        createGraphicsPipeline(vertShaderPath, fragShaderPath, configInfo);
    }

    PipelineConfigInfo GraphicsPipeline::defaultPipelineConfigInfo(uint32_t width, uint32_t height)
    {
        PipelineConfigInfo configInfo{};

        return configInfo;
    }

    std::vector<char> GraphicsPipeline::readFile(const std::string &path)
    {
        std::ifstream file(path, std::ios::ate | std::ios::binary);

        if (!file.is_open())
        {
            throw std::runtime_error("Failed to open shader file: " + path);
        }

        size_t fileSize = static_cast<size_t>(file.tellg());
        std::vector<char> buffer(fileSize);

        file.seekg(0);
        file.read(buffer.data(), fileSize);

        file.close();

        return buffer;
    }

    void GraphicsPipeline::createGraphicsPipeline(
        const std::string &vertShaderPath,
        const std::string &fragShaderPath,
        const PipelineConfigInfo &configInfo)
    {
        auto vertCode = readFile(vertShaderPath);
        auto fragCode = readFile(fragShaderPath);

        std::cout << "Vertex Shader Code Size: " << vertCode.size() << '\n';
        std::cout << "Fragment Shader Code Size: " << vertCode.size() << '\n';
    }

    void GraphicsPipeline::createShaderModule(const std::vector<char> &code, VkShaderModule *shaderModule)
    {
        VkShaderModuleCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = code.size();
        createInfo.pCode = reinterpret_cast<const uint32_t *>(code.data());

        if (vkCreateShaderModule(device.device(), &createInfo, nullptr, shaderModule) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create shader module.");
        }
    }
} // namespace GeckoEngine
