#ifndef CRAYON_WINDOW_H
#define CRAYON_WINDOW_H

#include <string>
#include <string_view>

struct SDL_Window;
struct SDL_GLContextState;

namespace CrayonRuntime
{
    struct WindowOptions
    {
        /**
         * @brief 타이틀.
         */
        std::string title;

        /**
         * @brief 너비.
         */
        int width;

        /**
         * @brief 높이.
         */
        int height;

        /**
         * @brief VSync 적용 여부.
         */
        bool shouldVSync;

        // 일단 테스트 용으로만 사용.
        bool shouldResizable = true;
        bool shouldFullscreen = false;
        bool shouldDecorated = true;
    };

    class Window
    {
    public:
        /**
         * @brief 생성자.
         *
         * @param options_ 윈도우 옵션.
         */
        Window(const WindowOptions& options_) noexcept;

        /**
         * @brief 소멸자.
         */
        ~Window() noexcept;

        /**
         * @brief 윈도우를 실행합니다.
         *
         * 이 함수는 이벤트 루프를 시작하고, 윈도우가 닫힐 때까지 대기합니다.
         */
        void Run() noexcept;
    private:
        /**
         * @brief 타이틀.
         */
        std::string mTitle;

        /**
         * @brief 너비.
         */
        int mWidth;

        /**
         * @brief 높이.
         */
        int mHeight;

        /**
         * @brief VSync 적용 여부.
         */
        bool mShouldVSync;

        /**
         * @brief SDL 윈도우 핸들.
         */
        SDL_Window* mWindow;

        /**
         * @brief SDL OpenGL 컨텍스트 핸들.
         */
        SDL_GLContextState* mGLContext;
    };
} // namespace CrayonRuntime

#endif // !GUARD_WINDOW_H