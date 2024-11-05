#ifndef _GRAPHICS_PIPELINE_H
#define _GRAPHICS_PIPELINE_H

#include <string>
#include <vector>

namespace GeckoEngine
{
    class GraphicsPipeline
    {
    public:
        GraphicsPipeline(const std::string &vertShaderPath, const std::string &fragShaderPath);

    private:
        static std::vector<char> readFile(const std::string &path);

        void createGraphicsPipeline(const std::string &vertShaderPath, const std::string &fragShaderPath);
    };
} // namespace GeckoEngine

#endif // _RENDER_PIPELINE_H