#include "application.h"

#include "rendering_server.h"

#define GLM_FORCE_RADIANS
#include <glm/gtc/constants.hpp>

namespace GeckoEngine
{
    Application::Application()
    {
        loadObjects();
    }

    Application::~Application()
    {
    }

    void Application::run()
    {
        RenderingServer renderingServer{device, renderer.getSwapChainRenderPass()};

        while (!window.shouldClose())
        {
            glfwPollEvents();

            if (auto commandBuffer = renderer.beginFrame())
            {
                renderer.beginSwapChainRenderPass(commandBuffer);
                renderingServer.renderObjects(commandBuffer, objects);
                renderer.endSwapChainRenderPass(commandBuffer);
                renderer.endFrame();
            }
        }

        vkDeviceWaitIdle(device.device());
    }

    void Application::loadObjects()
    {
        std::vector<Model::Vertex> vertices{
            {{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
            {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
            {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
        };
        auto model = std::make_shared<Model>(device, vertices);

        auto triangle = Object::createObject();
        triangle.model = model;
        triangle.color = {0.1f, 0.8f, 0.1f};
        triangle.transform2D.translation.x = 0.2f;
        triangle.transform2D.scale = {2.0f, 0.5f};
        triangle.transform2D.rotation = 0.25f * glm::two_pi<float>();

        objects.push_back(std::move(triangle));
    }
} // namespace GeckoEngine
