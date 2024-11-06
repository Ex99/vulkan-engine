#ifndef _APPLICATION_H
#define _APPLICATION_H

#include "device.h"
#include "graphics_pipeline.h"
#include "window.h"

namespace GeckoEngine
{
    class Application
    {
    public:
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 800;

        void run();

    private:
        Window window{WIDTH, HEIGHT, "Hello Vulkan!"};
        Device device{window};
        GraphicsPipeline graphicsPipeline{
            device,
            "shaders/simple.vert.spv",
            "shaders/simple.frag.spv",
            GraphicsPipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT)};
    };
} // namespace GeckoEngine

#endif // _APPLICATION_H