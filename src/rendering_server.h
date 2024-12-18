#ifndef RENDERING_SERVER_H
#define RENDERING_SERVER_H

#include "camera.h"
#include "device.h"
#include "frame_info.h"
#include "graphics_pipeline.h"
#include "object.h"

#include <memory>

namespace GeckoEngine
{
    class RenderingServer
    {
    public:
        RenderingServer(Device &device, VkRenderPass renderPass);
        ~RenderingServer();

        RenderingServer(const RenderingServer &) = delete;
        RenderingServer &operator=(const RenderingServer &) = delete;

        void renderObjects(FrameInfo &frameInfo, std::vector<Object> &objects);

    private:
        void createPipelineLayout();
        void createPipeline(VkRenderPass renderPass);

        Device &device;

        std::unique_ptr<GraphicsPipeline> graphicsPipeline;
        VkPipelineLayout pipelineLayout;
    };
} // namespace GeckoEngine

#endif // RENDERING_SERVER_H