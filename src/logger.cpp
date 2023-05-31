#include "logger.hpp"

#include <iostream>
#include <cstdarg>

namespace logger
{

enum log_level
{
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_MAX
};

void log_output(log_level level, const char *fmt, std::va_list args)
{
    constexpr std::size_t LOG_BUFFER_SIZE = 1024;
    char buffer[LOG_BUFFER_SIZE] = { 0 };
    static const char *log_level_names[LOG_LEVEL_MAX] = { "debug", "info", "warning", "error" };

    std::vsnprintf(buffer, sizeof(buffer), fmt, args);

    if (level == LOG_LEVEL_ERROR)
        std::cerr << "[" << log_level_names[level] << "]: " <<  buffer << "\n";
    else
        std::cout << "[" << log_level_names[level] << "]: " <<  buffer << "\n";
}

void debug(const char *fmt, ...)
{
#ifdef GAME_DEBUG_ENABLED

    std::va_list args;
    va_start(args, fmt);
    log_output(LOG_LEVEL_DEBUG, fmt, args);
    va_end(args);

#endif
}

void info(const char *fmt, ...)
{
    std::va_list args;
    va_start(args, fmt);
    log_output(LOG_LEVEL_INFO, fmt, args);
    va_end(args);
}

void warning(const char *fmt, ...)
{
    std::va_list args;
    va_start(args, fmt);
    log_output(LOG_LEVEL_WARNING, fmt, args);
    va_end(args);
}

void error(const char *fmt, ...)
{
    std::va_list args;
    va_start(args, fmt);
    log_output(LOG_LEVEL_ERROR, fmt, args);
    va_end(args);
}

} // namespace logger
