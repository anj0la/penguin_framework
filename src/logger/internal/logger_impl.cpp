#include <logger/internal/logger_impl.hpp>

namespace penguin::internal::log {

	// Initalizing LogEntry struct

    LogEntry::LogEntry(penguin::log::LogLevel p_level, std::string_view p_message, const std::source_location& p_location)
        : timestamp(std::chrono::system_clock::now()), 
        level(p_level), 
        message(p_message), 
        file(std::filesystem::path(p_location.file_name()).filename().string()), 
        line(p_location.line()),
        column(p_location.column()),
        function(p_location.function_name()) {}

    LogEntry::LogEntry() 
        : timestamp(std::chrono::system_clock::now()),
        level(penguin::log::LogLevel::Error),
        message(""),
        file(""),
        line(0),
        column(0),
        function("") { }

    // Initializing LoggerImpl

    LoggerImpl::LoggerImpl()
        : has_error(false),
        min_log_level(penguin::log::LogLevel::Debug) {

        // Creating logs folder and default log file

        std::filesystem::create_directories("logs");
        log_path = std::filesystem::path("logs") / "penguin.log";
        log_file.open(log_path, std::ios::app);

    }

    LoggerImpl::~LoggerImpl() {
        log_file.close();
    }

    std::string LoggerImpl::log_level_to_string(penguin::log::LogLevel level) const {
        switch (level) {
            case penguin::log::LogLevel::Debug: 
                return "DEBUG";
            case penguin::log::LogLevel::Info: 
                return "INFO";
            case penguin::log::LogLevel::Warning: 
                return "WARN";
            case penguin::log::LogLevel::Error: 
                return "ERROR";
            default: 
                return "UNKNOWN";
        }
    }

    std::string LoggerImpl::format_log_entry(const LogEntry& entry) const {
        auto time_t = std::chrono::system_clock::to_time_t(entry.timestamp);
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            entry.timestamp.time_since_epoch()) % 1000;

        std::ostringstream oss;
        oss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");

        std::string formatted = "[" + oss.str() + "." +
            std::to_string(ms.count()) + "] [" +
            log_level_to_string(entry.level) + "] " + entry.message;

        if (!entry.file.empty()) {
            formatted += " (" + entry.file + ":" + std::to_string(entry.line) +
                ":" + std::to_string(entry.column) + " in " + entry.function + ")";
        }

        return formatted;
    }

    void LoggerImpl::write_log(const LogEntry& entry) {
        if (entry.level < min_log_level) return;

        std::string formatted = format_log_entry(entry);

        if (entry.level == penguin::log::LogLevel::Warning || entry.level == penguin::log::LogLevel::Error) {
            std::cerr << formatted << std::endl;
        }
        else {
            std::cout << formatted << std::endl;
        }
        
        log_file << formatted << std::endl;
        log_file.flush();
    }
}