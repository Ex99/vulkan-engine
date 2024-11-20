#ifndef FRAME_INFO_H
#define FRAME_INFO_H

#include <vulkan/vulkan.h>

#include "camera.h"

namespace GeckoEngine
{
    struct FrameInfo
    {
        int frameIndex;
        float frameTime;
        VkCommandBuffer commandBuffer;
        Camera3D &camera;
    };
} // namespace GeckoEngine

#endif // FRAME_INFO_H