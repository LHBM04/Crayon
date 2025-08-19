#include "Logger.hpp"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace CrayonRuntime
{
    std::shared_ptr<spdlog::logger> Logger::sLogger = nullptr;

    void Logger::Initialize() noexcept
    {
        std::vector<spdlog::sink_ptr> logSink;
        logSink.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
        logSink.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("Crayon.log", true));

        logSink.at(0)->set_pattern("%^[%T] %n: %v%$");
        logSink.at(1)->set_pattern("[%T] [%1] %n: %v");

        sLogger = std::make_shared<spdlog::logger>("Crayon", logSink.begin(), logSink.end());
        spdlog::register_logger(sLogger);

        sLogger->set_level(spdlog::level::trace);
        sLogger->flush_on(spdlog::level::trace);
    }

    void Logger::Release() noexcept
    {
        sLogger.reset();
        spdlog::shutdown();
    }
} // namespace CrayonRuntime