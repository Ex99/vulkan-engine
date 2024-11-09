#include "window.h"

#include <stdexcept>

namespace GeckoEngine
{
    Window::Window(int w, int h, std::string title) : width{w}, height{h}, title{title}
    {
        init();
    }

    Window::~Window()
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void Window::createWindowSurface(VkInstance instance, VkSurfaceKHR *surface)
    {
        if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create window surface.");
        }
    }

    void Window::framebufferResizeCallback(GLFWwindow *window, int width, int height)
    {
        auto target = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
        target->isResized = true;
        target->width = width;
        target->height = height;
    }

    void Window::init()
    {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

        window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        glfwSetWindowUserPointer(window, this);
        glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
    }
} // namespace GeckoEngine
