#ifndef _APPLICATION_H
#define _APPLICATION_H

#include "window.h"
#include "graphics_pipeline.h"

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
        GraphicsPipeline graphicsPipeline{"shaders/simple.vert.spv", "shaders/simple.frag.spv"};
    };
}

#endif // _APPLICATION_H