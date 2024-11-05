#include "graphics_pipeline.h"

#include <fstream>
#include <iostream>

namespace GeckoEngine
{
    GraphicsPipeline::GraphicsPipeline(const std::string &vertShaderPath, const std::string &fragShaderPath)
    {
        createGraphicsPipeline(vertShaderPath, fragShaderPath);
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

    void GraphicsPipeline::createGraphicsPipeline(const std::string &vertShaderPath, const std::string &fragShaderPath)
    {
        auto vertCode = readFile(vertShaderPath);
        auto fragCode = readFile(fragShaderPath);

        std::cout << "Vertex Shader Code Size: " << vertCode.size() << '\n';
        std::cout << "Fragment Shader Code Size: " << vertCode.size() << '\n';
    }
} // namespace GeckoEngine
