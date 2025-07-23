#pragma once

#include <penguin_api.hpp>

#include <penguin_framework/logger/log_level.hpp>
#include <memory>
#include <source_location>


namespace penguin::internal::log {
    class LoggerImpl;
}

namespace penguin::log {

    class PENGUIN_API Logger {
    public:
        Logger();
        ~Logger();

        // Delete copy semantics

        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;

        // Move semantics
   
        Logger(Logger&&) noexcept;
        Logger& operator=(Logger&&) noexcept;

        // Singleton access

        static Logger& get_instance();

        // Logging functions

        void debug(const char* message, const std::source_location& p_location = std::source_location::current());
        void info(const char* message, const std::source_location& p_location = std::source_location::current());
        void warning(const char* message, const std::source_location& p_location = std::source_location::current());
        void error(const char* message, const std::source_location& p_location = std::source_location::current());

        // Last error functionality

        bool has_error() const;
        const char* get_last_error_message() const;
        void print_last_error();
        void clear_last_error();

    private:
        std::unique_ptr<penguin::internal::log::LoggerImpl> pimpl_;
    };

}

#define PF_LOG_DEBUG(msg) penguin::log::Logger::get_instance().debug(msg)
#define PF_LOG_INFO(msg) penguin::log::Logger::get_instance().info(msg)
#define PF_LOG_WARNING(msg) penguin::log::Logger::get_instance().warning(msg)
#define PF_LOG_ERROR(msg) penguin::log::Logger::get_instance().error(msg)