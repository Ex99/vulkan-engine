#ifndef _RENDERER_H
#define _RENDERER_H

#include "device.h"
#include "swap_chain.h"
#include "window.h"

#include <cassert>
#include <memory>
#include <vector>

namespace GeckoEngine
{
    class Renderer
    {
    public:
        Renderer(Window &window, Device &device);
        ~Renderer();

        Renderer(const Renderer &) = delete;
        Renderer &operator=(const Renderer &) = delete;

        VkRenderPass getSwapChainRenderPass() const { return swapChain->getRenderPass(); };
        bool isFrameInProgress() const { return isFrameStarted; };

        VkCommandBuffer getCurrentCommandBuffer() const
        {
            assert(isFrameStarted && "Cannot get command buffer when frame is not in progress.");
            return commandBuffers[currentImageIndex];
        }

        VkCommandBuffer beginFrame();
        void endFrame();
        void beginSwapChainRenderPass(VkCommandBuffer commandBuffer);
        void endSwapChainRenderPass(VkCommandBuffer commandBuffer);

    private:
        void createCommandBuffers();
        void freeCommandBuffers();
        void drawFrame();
        void recreateSwapChain();

        Window &window;
        Device &device;
        std::unique_ptr<SwapChain> swapChain;
        std::vector<VkCommandBuffer> commandBuffers;

        uint32_t currentImageIndex;
        bool isFrameStarted{false};
    };
} // namespace GeckoEngine

#endif // _RENDERER_H