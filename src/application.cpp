#include "application.h"

#include "camera.h"
#include "input.h"
#include "rendering_server.h"

#define GLM_FORCE_RADIANS
#include <glm/gtc/constants.hpp>

#include <chrono>

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

        Camera3D camera{};

        auto viewerObject = Object::createObject();
        KeyboardController cameraController{};

        auto currentTime = std::chrono::high_resolution_clock::now();

        while (!window.shouldClose())
        {
            glfwPollEvents();

            auto newTime = std::chrono::high_resolution_clock::now();
            float frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
            currentTime = newTime;

            cameraController.moveInPlaneXZ(window.getGLFWwindow(), frameTime, viewerObject);
            camera.setViewXYZ(viewerObject.transform.position, viewerObject.transform.rotation);

            float aspectRatio = renderer.getAspectRatio();
            camera.setPerspectiveProjection(glm::radians(50.0f), aspectRatio, 0.1f, 10.0f);

            if (auto commandBuffer = renderer.beginFrame())
            {
                renderer.beginSwapChainRenderPass(commandBuffer);
                renderingServer.renderObjects(commandBuffer, objects, camera);
                renderer.endSwapChainRenderPass(commandBuffer);
                renderer.endFrame();
            }
        }

        vkDeviceWaitIdle(device.device());
    }

    std::unique_ptr<Model> createCubeModel(Device &device, glm::vec3 offset)
    {
        std::vector<Model::Vertex> vertices{
            // Left face (white)
            {{-0.5f, -0.5f, -0.5f}, {0.9f, 0.9f, 0.9f}},
            {{-0.5f, 0.5f, 0.5f}, {0.9f, 0.9f, 0.9f}},
            {{-0.5f, -0.5f, 0.5f}, {0.9f, 0.9f, 0.9f}},
            {{-0.5f, -0.5f, -0.5f}, {0.9f, 0.9f, 0.9f}},
            {{-0.5f, 0.5f, -0.5f}, {0.9f, 0.9f, 0.9f}},
            {{-0.5f, 0.5f, 0.5f}, {0.9f, 0.9f, 0.9f}},

            // Right face (yellow)
            {{0.5f, -0.5f, -0.5f}, {0.8f, 0.8f, 0.1f}},
            {{0.5f, 0.5f, 0.5f}, {0.8f, 0.8f, 0.1f}},
            {{0.5f, -0.5f, 0.5f}, {0.8f, 0.8f, 0.1f}},
            {{0.5f, -0.5f, -0.5f}, {0.8f, 0.8f, 0.1f}},
            {{0.5f, 0.5f, -0.5f}, {0.8f, 0.8f, 0.1f}},
            {{0.5f, 0.5f, 0.5f}, {0.8f, 0.8f, 0.1f}},

            // Top face (orange)
            {{-0.5f, -0.5f, -0.5f}, {0.9f, 0.6f, 0.1f}},
            {{0.5f, -0.5f, 0.5f}, {0.9f, 0.6f, 0.1f}},
            {{-0.5f, -0.5f, 0.5f}, {0.9f, 0.6f, 0.1f}},
            {{-0.5f, -0.5f, -0.5f}, {0.9f, 0.6f, 0.1f}},
            {{0.5f, -0.5f, -0.5f}, {0.9f, 0.6f, 0.1f}},
            {{0.5f, -0.5f, 0.5f}, {0.9f, 0.6f, 0.1f}},

            // Bottom face (red)
            {{-0.5f, 0.5f, -0.5f}, {0.8f, 0.1f, 0.1f}},
            {{0.5f, 0.5f, 0.5f}, {0.8f, 0.1f, 0.1f}},
            {{-0.5f, 0.5f, 0.5f}, {0.8f, 0.1f, 0.1f}},
            {{-0.5f, 0.5f, -0.5f}, {0.8f, 0.1f, 0.1f}},
            {{0.5f, 0.5f, -0.5f}, {0.8f, 0.1f, 0.1f}},
            {{0.5f, 0.5f, 0.5f}, {0.8f, 0.1f, 0.1f}},

            // Nose face (blue)
            {{-0.5f, -0.5f, 0.5f}, {0.1f, 0.1f, 0.8f}},
            {{0.5f, 0.5f, 0.5f}, {0.1f, 0.1f, 0.8f}},
            {{-0.5f, 0.5f, 0.5f}, {0.1f, 0.1f, 0.8f}},
            {{-0.5f, -0.5f, 0.5f}, {0.1f, 0.1f, 0.8f}},
            {{0.5f, -0.5f, 0.5f}, {0.1f, 0.1f, 0.8f}},
            {{0.5f, 0.5f, 0.5f}, {0.1f, 0.1f, 0.8f}},

            // Tail face (green)
            {{-0.5f, -0.5f, -0.5f}, {0.1f, 0.8f, 0.1f}},
            {{0.5f, 0.5f, -0.5f}, {0.1f, 0.8f, 0.1f}},
            {{-0.5f, 0.5f, -0.5f}, {0.1f, 0.8f, 0.1f}},
            {{-0.5f, -0.5f, -0.5f}, {0.1f, 0.8f, 0.1f}},
            {{0.5f, -0.5f, -0.5f}, {0.1f, 0.8f, 0.1f}},
            {{0.5f, 0.5f, -0.5f}, {0.1f, 0.8f, 0.1f}},
        };

        for (auto &v : vertices)
        {
            v.position += offset;
        }

        return std::make_unique<Model>(device, vertices);
    }

    void Application::loadObjects()
    {
        std::shared_ptr<Model> model = createCubeModel(device, {0.0f, 0.0f, 0.0f});

        auto cube = Object::createObject();
        cube.model = model;
        cube.transform.position = {0.0f, 0.0f, 1.5f};
        cube.transform.scale = {0.5f, 0.5f, 0.5f};

        objects.push_back(std::move(cube));
    }
} // namespace GeckoEngine
