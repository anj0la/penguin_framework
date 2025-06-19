#include <penguin_framework/logger/logger.hpp>
#include <logger/internal/logger_impl.hpp>

namespace penguin::log {
    static std::unique_ptr<Logger> instance;
    static std::mutex instance_mutex;

    Logger::Logger() : pimpl_(std::make_unique<penguin::internal::log::LoggerImpl>()) {}

    Logger::~Logger() = default;

    Logger::Logger(Logger&&) noexcept = default;
    Logger& Logger::operator=(Logger&&) noexcept = default;

    Logger& Logger::get_instance() {
        std::lock_guard<std::mutex> lock(instance_mutex);
        if (!instance) {
            instance = std::unique_ptr<Logger>(new Logger());
        }
        return *instance;
    }

    void Logger::debug(const char* message, const std::source_location& p_location) {
        std::lock_guard<std::mutex> lock(pimpl_->log_mutex);
        pimpl_->write_log(penguin::internal::log::LogEntry(LogLevel::Debug, message, p_location));
    }

    void Logger::info(const char* message, const std::source_location& p_location) {
        std::lock_guard<std::mutex> lock(pimpl_->log_mutex);
        pimpl_->write_log(penguin::internal::log::LogEntry(LogLevel::Info, message, p_location));
    }

    void Logger::warning(const char* message, const std::source_location& p_location) {
        std::lock_guard<std::mutex> lock(pimpl_->log_mutex);
        pimpl_->write_log(penguin::internal::log::LogEntry(LogLevel::Warning, message, p_location));
    }

    void Logger::error(const char* message, const std::source_location& p_location) {
        std::lock_guard<std::mutex> lock(pimpl_->log_mutex);
        penguin::internal::log::LogEntry error_entry(LogLevel::Error, message, p_location);
        pimpl_->write_log(error_entry);

        pimpl_->last_error = error_entry;
        pimpl_->has_error = true;
    }
   
    bool Logger::has_error() const {
        std::lock_guard<std::mutex> lock(pimpl_->log_mutex);
        return pimpl_->has_error;
    }

    const char* Logger::get_last_error_message() const {
        std::lock_guard<std::mutex> lock(pimpl_->log_mutex);
        return pimpl_->has_error ? pimpl_->last_error.message.c_str() : "";
    }

    void Logger::print_last_error() {
        if (pimpl_->has_error) {
            std::string formatted = pimpl_->format_log_entry(pimpl_->last_error);
            std::cout << formatted << std::endl;
        }
    }

    void Logger::clear_last_error() {
        std::lock_guard<std::mutex> lock(pimpl_->log_mutex);
        pimpl_->has_error = false;
    }
}