#include "application.h"

#include "buffer.h"
#include "camera.h"
#include "input.h"
#include "rendering_server.h"

#define GLM_FORCE_RADIANS
#include <glm/gtc/constants.hpp>

#include <chrono>

namespace GeckoEngine
{
    struct GlobalUbo
    {
        glm::mat4 projectionView{1.0f};
        glm::vec3 lightDirection = glm::normalize(glm::vec3{1.0f, -3.0f, -1.0f});
    };

    Application::Application(const std::string &modelPath)
    {
        loadObjects(modelPath);
    }

    Application::~Application()
    {
    }

    void Application::run()
    {
        std::vector<std::unique_ptr<Buffer>> uboBuffers(SwapChain::MAX_FRAMES_IN_FLIGHT);

        for (int i = 0; i < uboBuffers.size(); i++)
        {
            uboBuffers[i] = std::make_unique<Buffer>(
                device,
                sizeof(GlobalUbo),
                1,
                VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
            uboBuffers[i]->map();
        }

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
                int frameIndex = renderer.getFrameIndex();

                FrameInfo frameInfo{frameIndex, frameTime, commandBuffer, camera};

                // Update
                GlobalUbo ubo{};
                ubo.projectionView = camera.getProjection() * camera.getView();
                uboBuffers[frameIndex]->writeToBuffer(&ubo);
                uboBuffers[frameIndex]->flush();

                // Render
                renderer.beginSwapChainRenderPass(commandBuffer);
                renderingServer.renderObjects(frameInfo, objects);
                renderer.endSwapChainRenderPass(commandBuffer);
                renderer.endFrame();
            }
        }

        vkDeviceWaitIdle(device.device());
    }

    std::unique_ptr<Model> createCubeModel(Device &device, glm::vec3 offset)
    {
        Model::Builder builder{};
        builder.vertices = {
            // Left face (white)
            {{-0.5f, -0.5f, -0.5f}, {0.9f, 0.9f, 0.9f}},
            {{-0.5f, 0.5f, 0.5f}, {0.9f, 0.9f, 0.9f}},
            {{-0.5f, -0.5f, 0.5f}, {0.9f, 0.9f, 0.9f}},
            {{-0.5f, 0.5f, -0.5f}, {0.9f, 0.9f, 0.9f}},
            // Right face (yellow)
            {{0.5f, -0.5f, -0.5f}, {0.8f, 0.8f, 0.1f}},
            {{0.5f, 0.5f, 0.5f}, {0.8f, 0.8f, 0.1f}},
            {{0.5f, -0.5f, 0.5f}, {0.8f, 0.8f, 0.1f}},
            {{0.5f, 0.5f, -0.5f}, {0.8f, 0.8f, 0.1f}},
            // Top face (orange)
            {{-0.5f, -0.5f, -0.5f}, {0.9f, 0.6f, 0.1f}},
            {{0.5f, -0.5f, 0.5f}, {0.9f, 0.6f, 0.1f}},
            {{-0.5f, -0.5f, 0.5f}, {0.9f, 0.6f, 0.1f}},
            {{0.5f, -0.5f, -0.5f}, {0.9f, 0.6f, 0.1f}},
            // Bottom face (red)
            {{-0.5f, 0.5f, -0.5f}, {0.8f, 0.1f, 0.1f}},
            {{0.5f, 0.5f, 0.5f}, {0.8f, 0.1f, 0.1f}},
            {{-0.5f, 0.5f, 0.5f}, {0.8f, 0.1f, 0.1f}},
            {{0.5f, 0.5f, -0.5f}, {0.8f, 0.1f, 0.1f}},
            // Nose face (blue)
            {{-0.5f, -0.5f, 0.5f}, {0.1f, 0.1f, 0.8f}},
            {{0.5f, 0.5f, 0.5f}, {0.1f, 0.1f, 0.8f}},
            {{-0.5f, 0.5f, 0.5f}, {0.1f, 0.1f, 0.8f}},
            {{0.5f, -0.5f, 0.5f}, {0.1f, 0.1f, 0.8f}},
            // Tail face (green)
            {{-0.5f, -0.5f, -0.5f}, {0.1f, 0.8f, 0.1f}},
            {{0.5f, 0.5f, -0.5f}, {0.1f, 0.8f, 0.1f}},
            {{-0.5f, 0.5f, -0.5f}, {0.1f, 0.8f, 0.1f}},
            {{0.5f, -0.5f, -0.5f}, {0.1f, 0.8f, 0.1f}},
        };

        for (auto &v : builder.vertices)
        {
            v.position += offset;
        }

        builder.indices = {0, 1, 2, 0, 3, 1, 4, 5, 6, 4, 7, 5, 8, 9, 10, 8, 11, 9, 12, 13, 14, 12, 15, 13, 16, 17, 18, 16, 19, 17, 20, 21, 22, 20, 23, 21};

        return std::make_unique<Model>(device, builder);
    }

    void Application::loadObjects(const std::string &modelPath)
    {
        std::shared_ptr<Model> model;

        if (!modelPath.empty())
        {
            model = Model::createModelFromFile(device, modelPath);
        }
        else
        {
            model = createCubeModel(device, {0.0f, 0.0f, 0.0f});
        }

        auto obj = Object::createObject();
        obj.model = model;
        obj.transform.position = {0.0f, 0.0f, 1.5f};
        obj.transform.scale = {0.5f, 0.5f, 0.5f};

        objects.push_back(std::move(obj));
    }
} // namespace GeckoEngine
