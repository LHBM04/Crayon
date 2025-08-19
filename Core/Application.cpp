#include "Application.hpp"

namespace CrayonRuntime
{
    Application::Application()
        : mWindow(std::make_unique<Window>(WindowOptions{
            .title = "Crayon Runtime",
            .width = 1280,
            .height = 720,
            .shouldVSync = true,
            .shouldResizable = true,
            .shouldFullscreen = false,
            .shouldDecorated = true
        }))
    {

    }

    Application::~Application()
    {

    }
} // namespace CrayonRuntime