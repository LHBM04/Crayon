#include <cstdint>
#include <print>
#include <stdfloat>

#include <GLAD/glad.h>
#include <GL/GL.h>

#include <SDL3/SDL_init.h>
#include <SDL3/SDL_video.h>

int main(int    argc_,
         char** argv_)
{
    {
        SDL_InitFlags flags = SDL_INIT_VIDEO | SDL_INIT_EVENTS;
        if (!(SDL_Init(flags)))
        {
            std::println(stderr, "SDL_Init failed: {}", SDL_GetError());
            return -1;
        }
    }
    SDL_Window* window = SDL_CreateWindow("Hello World",
                                           640, 480,
                                           SDL_WINDOW_OPENGL);

    if (nullptr == window)
    {
        return -1;
    }

    SDL_ShowWindow(window);

    bool isRunning = true;
    while (isRunning)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                isRunning = false;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}