#include "application.h"

#include <cstdlib>
#include <iostream>
#include <stdexcept>

int main(int argc, const char *argv[])
{
    const std::string modelPath = argc > 1 ? argv[1] : "";

    GeckoEngine::Application app{modelPath};

    try
    {
        app.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}