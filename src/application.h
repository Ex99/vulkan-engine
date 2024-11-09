#ifndef _APPLICATION_H
#define _APPLICATION_H

#include "device.h"
#include "graphics_pipeline.h"
#include "model.h"
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
        void loadModels();
        void createPipelineLayout();
        void createPipeline();
        void createCommandBuffers();
        void freeCommandBuffers();
        void drawFrame();
        void recreateSwapChain();
        void recordCommandBuffer(int imageIndex);

        Window window{WIDTH, HEIGHT, "Gecko Engine"};
        Device device{window};
        std::unique_ptr<SwapChain> swapChain;
        std::unique_ptr<GraphicsPipeline> graphicsPipeline;
        VkPipelineLayout pipelineLayout;
        std::vector<VkCommandBuffer> commandBuffers;
        std::unique_ptr<Model> model;
    };
} // namespace GeckoEngine

#endif // _APPLICATION_H