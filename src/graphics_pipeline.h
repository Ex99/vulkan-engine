#ifndef _GRAPHICS_PIPELINE_H
#define _GRAPHICS_PIPELINE_H

#include "device.h"

#include <string>
#include <vector>

namespace GeckoEngine
{
    struct PipelineConfigInfo
    {
    };

    class GraphicsPipeline
    {
    public:
        GraphicsPipeline(
            Device &device,
            const std::string &vertShaderPath,
            const std::string &fragShaderPath,
            const PipelineConfigInfo &configInfo);
        ~GraphicsPipeline() {}

        GraphicsPipeline(const GraphicsPipeline &) = delete;
        void operator=(const GraphicsPipeline &) = delete;

        static PipelineConfigInfo defaultPipelineConfigInfo(uint32_t width, uint32_t height);

    private:
        static std::vector<char> readFile(const std::string &path);

        void createGraphicsPipeline(
            const std::string &vertShaderPath,
            const std::string &fragShaderPath,
            const PipelineConfigInfo &configInfo);

        void createShaderModule(const std::vector<char> &code, VkShaderModule *shaderModule);

        Device &device;
        VkPipeline graphicsPipeline;
        VkShaderModule vertShaderModule;
        VkShaderModule fragShaderModule;
    };
} // namespace GeckoEngine

#endif // _RENDER_PIPELINE_H