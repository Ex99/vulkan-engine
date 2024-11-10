#ifndef _APPLICATION_H
#define _APPLICATION_H

#include "device.h"
#include "graphics_pipeline.h"
#include "object.h"
#include "renderer.h"
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
        void loadObjects();
        void createPipelineLayout();
        void createPipeline();
        void renderObjects(VkCommandBuffer commandBuffer);

        Window window{WIDTH, HEIGHT, "Gecko Engine"};
        Device device{window};
        Renderer renderer{window, device};

        std::unique_ptr<GraphicsPipeline> graphicsPipeline;
        VkPipelineLayout pipelineLayout;
        std::vector<Object> objects;
    };
} // namespace GeckoEngine

#endif // _APPLICATION_H