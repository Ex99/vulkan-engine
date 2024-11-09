#ifndef _WINDOW_H
#define _WINDOW_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

namespace GeckoEngine
{
    class Window
    {
    public:
        Window(int w, int h, std::string name);
        ~Window();

        Window(const Window &) = delete;
        Window &operator=(const Window &) = delete;

        bool shouldClose() { return glfwWindowShouldClose(window); }
        VkExtent2D getExtent() { return {static_cast<uint32_t>(width), static_cast<uint32_t>(height)}; }
        bool wasResized() { return isResized; }
        void resetResizedFlag() { isResized = false; }

        void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface);

    private:
        static void framebufferResizeCallback(GLFWwindow *window, int width, int height);
        void init();

        int width;
        int height;
        bool isResized = false;

        std::string title;
        GLFWwindow *window;
    };
} // namespace GeckoEngine

#endif // _WINDOW_H