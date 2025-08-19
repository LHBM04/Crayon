#ifndef CR_APPLICATION_H
#define CR_APPLICATION_H

#include <functional>
#include <memory>

#include "Platform.hpp"
#include "Window.hpp"

namespace CrayonRuntime
{
    class Application
    {
    public:
        /**
         * @brief 생성자.
         */
        Application();

        /**
         * @brief 소멸자.
         */
        ~Application();
    private:
        /**
         * @brief 윈도우 객체.
         */
        std::unique_ptr<Window> mWindow;
    };
} // namespace CrayonRuntime

#endif // CR_APPLICATION_H