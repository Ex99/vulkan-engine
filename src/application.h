#ifndef _APPLICATION_H
#define _APPLICATION_H

#include "device.h"
#include "object.h"
#include "renderer.h"
#include "window.h"

#include <memory>
#include <vector>

namespace GeckoEngine
{
    class Application
    {
    public:
        static constexpr int WIDTH = 1280;
        static constexpr int HEIGHT = 720;

        Application();
        ~Application();

        Application(const Application &) = delete;
        Application &operator=(const Application &) = delete;

        void run();

    private:
        void loadObjects();

        Window window{WIDTH, HEIGHT, "Gecko Engine"};
        Device device{window};
        Renderer renderer{window, device};

        std::vector<Object> objects;
    };
} // namespace GeckoEngine

#endif // _APPLICATION_H