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

    private:
        void init();

        const int width;
        const int height;

        std::string title;
        GLFWwindow *window;
    };
}

#endif // _WINDOW_H