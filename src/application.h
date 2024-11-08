#ifndef _APPLICATION_H
#define _APPLICATION_H

#include "device.h"
#include "graphics_pipeline.h"
#include "swap_chain.h"
#include "window.h"

#include <memory>
#include <vector>

namespace GeckoEngine
{
    class Application
    {
    public:
        static constexpr int WIDTH = 1280;
        static constexpr int HEIGHT = 720;

        Application();
        ~Application();

        Application(const Application &) = delete;
        Application &operator=(const Application &) = delete;

        void run();

    private:
        void createPipelineLayout();
        void createPipeline();
        void createCommandBuffers();
        void drawFrame();

        Window window{WIDTH, HEIGHT, "Gecko Engine"};
        Device device{window};
        SwapChain swapChain{device, window.getExtent()};
        std::unique_ptr<GraphicsPipeline> graphicsPipeline;
        VkPipelineLayout pipelineLayout;
        std::vector<VkCommandBuffer> commandBuffers;
    };
} // namespace GeckoEngine

#endif // _APPLICATION_H