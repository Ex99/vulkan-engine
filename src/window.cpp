#include "window.h"

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

    void Window::init()
    {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    }
}
