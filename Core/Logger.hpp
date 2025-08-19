#ifndef CRAYON_LOGGER_HPP
#define CRAYON_LOGGER_HPP

#include <memory>

#include <spdlog/spdlog.h>

namespace CrayonRuntime
{
    class Logger
    {
    public:
        /**
         * @brief 로거를 초기화합니다.
         */
        static void Initialize() noexcept;

        /**
         * @brief 로거를 종료합니다.
         */
        static void Release() noexcept;

        /**
         * @brief 정보 메시지를 출력합니다.
         *
         * @tparam TArguments 메시지에 포함될 인자들.
         *
         * @param message_ 출력할 메시지.
         * @param arguments_ 메시지에 포함될 인자들.
         */
        template<typename... TArguments>
        static void Info(fmt::format_string<TArguments...> message_,
                         TArguments&&...                   arguments_) noexcept;

        /**
         * @brief 추적 메시지를 출력합니다.
         *
         * @tparam TArguments 메시지에 포함될 인자들.
         *
         * @param message_ 출력할 메시지.
         * @param arguments_ 메시지에 포함될 인자들.
         */
        template<typename... TArguments>
        static void Trace(fmt::format_string<TArguments...> message_,
                          TArguments&&...                   arguments_) noexcept;

        /**
         * @brief 경고 메시지를 출력합니다.
         *
         * @tparam TArguments 메시지에 포함될 인자들.
         *
         * @param message_ 출력할 메시지.
         * @param arguments_ 메시지에 포함될 인자들.
         */
        template<typename... TArguments>
        static void Warn(fmt::format_string<TArguments...> message_,
                         TArguments&&...                   arguments_) noexcept;

        /**
         * @brief 에러 메시지를 출력합니다.
         *
         * @tparam TArguments 메시지에 포함될 인자들.
         *
         * @param message_ 출력할 메시지.
         * @param arguments_ 메시지에 포함될 인자들.
         */
        template<typename... TArguments>
        static void Error(fmt::format_string<TArguments...> message_,
                          TArguments&&...                   arguments_) noexcept;

        /**
         * @brief 치명적 에러 메시지를 출력합니다.
         *
         * @tparam TArguments 메시지에 포함될 인자들.
         *
         * @param message_ 출력할 메시지.
         * @param arguments_ 메시지에 포함될 인자들.
         */
        template<typename... TArguments>
        static void Critical(fmt::format_string<TArguments...> message_,
                             TArguments&&...                   arguments_) noexcept;
    private:
        /**
         * @brief 로거.
         */
        static std::shared_ptr<spdlog::logger> sLogger;
    };

    template<typename... TArguments>
    void Logger::Info(fmt::format_string<TArguments...> message_,
                      TArguments&&...                   arguments_) noexcept
    {
        sLogger->info(message_, std::forward<TArguments>(arguments_)...);
    }

    template<typename... TArguments>
    void Logger::Trace(fmt::format_string<TArguments...> message_,
                      TArguments&&...                   arguments_) noexcept
    {
        sLogger->trace(message_, std::forward<TArguments>(arguments_)...);
    }

    template<typename... TArguments>
    void Logger::Warn(fmt::format_string<TArguments...> message_,
                      TArguments&&...                   arguments_) noexcept
    {
        sLogger->warn(message_, std::forward<TArguments>(arguments_)...);
    }

    template<typename... TArguments>
    void Logger::Error(fmt::format_string<TArguments...> message_,
                       TArguments&&...                   arguments_) noexcept
    {
        sLogger->error(message_, std::forward<TArguments>(arguments_)...);
    }

    template<typename... TArguments>
    void Logger::Critical(fmt::format_string<TArguments...> message_,
                          TArguments&&...                   arguments_) noexcept
    {
        sLogger->critical(message_, std::forward<TArguments>(arguments_)...);
    }
} // namespace CrayonRuntime

#if defined(CRAYON_DEBUG)
    #define LOG_INFO(...)  CrayonRuntime::Logger::Info(__VA_ARGS__)
    #define LOG_TRACE(...) CrayonRuntime::Logger::Trace(__VA_ARGS__)
#else
    #define LOG_INFO(...)  void(0)
    #define LOG_TRACE(...) void(0)
#endif
#define LOG_WARN(...) CrayonRuntime::Logger::Warn(__VA_ARGS__)
#define LOG_ERROR(...) CrayonRuntime::Logger::Error(__VA_ARGS__)
#define LOG_CRITICAL(...) CrayonRuntime::Logger::Critical(__VA_ARGS__)

#endif // !CRAYON_LOGGER_HPP