#include "application.h"

namespace GeckoEngine
{
    void Application::run()
    {
        while (!window.shouldClose())
        {
            glfwPollEvents();
        }
    }
}
