#include "Window.hpp"

#include <chrono>

#include <sdl3/sdl_video.h>
#include <sdl3/sdl_init.h>
#include <sdl3/sdl_time.h>

#include "Logger.hpp"

namespace CrayonRuntime
{
    Window::Window(const WindowOptions& options_) noexcept
        : mTitle(options_.title)
        , mWidth(options_.width)
        , mHeight(options_.height)
    {
        SDL_InitFlags initFlags = SDL_INIT_VIDEO | SDL_INIT_EVENTS;
        if (!SDL_Init(initFlags))
        {
            Logger::Critical("SDL API를 초기화할 수 없었습니다! : '{}'", SDL_GetError());
            return;
        }

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

        SDL_WindowFlags windowFlags = SDL_WINDOW_OPENGL;
        if (!options_.shouldDecorated)
            windowFlags |= SDL_WINDOW_BORDERLESS;
        if (options_.shouldFullscreen)
            windowFlags |= SDL_WINDOW_FULLSCREEN;
        if (options_.shouldResizable)
            windowFlags |= SDL_WINDOW_RESIZABLE;

        mWindow = SDL_CreateWindow(options_.title.c_str(),
                                    options_.width,
                                    options_.height,
                                    windowFlags);

        if (nullptr == mWindow)
        {
            Logger::Critical("SDL_Window를 생성할 수 없었습니다! : '{}'", SDL_GetError());
            return;
        }


        mGLContext = SDL_GL_CreateContext(mWindow);
        if (nullptr == mGLContext)
        {
            Logger::Critical("SDL_GLContext를 생성할 수 없었습니다! : '{}'", SDL_GetError());
            return;
        }

        if (!SDL_GL_SetSwapInterval(static_cast<int>(options_.shouldVSync)))
        {
            Logger::Error("윈도우 핸들을 생성할 수 없었습니다! : '{}'", SDL_GetError());
        }

        SDL_ShowWindow(mWindow);
    }

    Window::~Window() noexcept
    {
        SDL_GL_DestroyContext(mGLContext);
        SDL_DestroyWindow(mWindow);
        SDL_Quit();
    }

    void Window::Run() noexcept
    {
        SDL_Time prevTime = 0;
        SDL_GetCurrentTime(&prevTime);

        constexpr float fixedUpdateTime = 1.0f / 60.0f; // 60 FPS 기준
                  float fixedDeltaTime  = 0.0f;         // 고정된 델타 타임

        while (true)
        {
            static bool isFocused = true; // 윈도우가 포커스를 잃었는지 여부
            if (!isFocused)
            {
                continue;
            }

            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_EVENT_QUIT)
                {
                    Logger::Info("OnQuit");
                    return; // 윈도우가 닫히면 루프를 종료합니다.
                }
                if (event.type == SDL_EVENT_WINDOW_RESIZED)
                {
                    mWidth  = event.window.data1;
                    mHeight = event.window.data2;
                    Logger::Info("OnResize: {}x{}", mWidth, mHeight);
                }
                else if (event.type == SDL_EVENT_WINDOW_MOVED)
                {
                    Logger::Info("OnMove: {}, {}", event.window.data1,
                                                               event.window.data2);
                }
                else if (event.type == SDL_EVENT_KEY_DOWN)
                {
                    Logger::Info("OnKeyDown: {}", event.key.key);
                }
                else if (event.type == SDL_EVENT_KEY_UP)
                {
                    Logger::Info("OnKeyUp: {}", event.key.key);
                }
                else if (event.type == SDL_EVENT_WINDOW_FOCUS_LOST)
                {
                    Logger::Info("OnFocusLost: {}", event.window.data1);
                }
                else if (event.type == SDL_EVENT_WINDOW_FOCUS_GAINED)
                {
                    Logger::Info("OnFocusGained: {}", event.window.data1);
                    isFocused = true; // 윈도우가 포커스를 얻었을 때
                }
                else if (event.type == SDL_EVENT_WINDOW_MINIMIZED)
                {
                    Logger::Info("OnMinimized: {}", event.window.data1);
                    isFocused = false; // 윈도우가 최소화되면 포커스를 잃음
                }
                else if (event.type == SDL_EVENT_WINDOW_RESTORED)
                {
                    Logger::Info("OnRestored: {}", event.window.data1);
                    isFocused = true; // 윈도우가 복원되면 포커스를 얻음
                }
            }

            SDL_Time currentTime = 0;
            SDL_GetCurrentTime(&currentTime);
            float deltaTime = (currentTime - prevTime) / 1000.0f;

            //Logger::Info("OnUpdate: {:.2f}.sec", deltaTime);

            prevTime = currentTime;

            fixedDeltaTime += deltaTime;
            if (fixedDeltaTime >= fixedUpdateTime)
            {
                fixedDeltaTime -= fixedUpdateTime;
                // 여기에 고정 업데이트 로직을 추가합니다.
                //Logger::Info("OnFixedUpdate: {:.2f}.sec", fixedUpdateTime);
            }

            //Logger::Info("OnRender: {:.2f}.sec", deltaTime);
            SDL_GL_SwapWindow(mWindow);
        }
    }
} // namespace NomadRuntime