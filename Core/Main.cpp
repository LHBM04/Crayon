#include "Logger.hpp"
#include "Window.hpp"

int main()
{
    CrayonRuntime::Logger::Initialize();

    CrayonRuntime::Window* window = new CrayonRuntime::Window({
        .title = "Crayon Runtime",
        .width = 1280,
        .height = 720,
        .shouldVSync = true,
        .shouldResizable = true,
        .shouldFullscreen = false,
        .shouldDecorated = true
    });
    window->Run();

    CrayonRuntime::Logger::Release();
    return 0;
}