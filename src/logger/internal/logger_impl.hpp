#pragma once

#include <penguin_framework/logger/log_level.hpp>

#include <source_location>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <chrono>
#include <mutex>
#include <memory>
#include <filesystem>

namespace penguin::internal::log {

    struct LogEntry {
        std::chrono::system_clock::time_point timestamp;
        penguin::log::LogLevel level;
        std::string message;
        std::string file;
        int line;
        int column;
        std::string function;

        LogEntry(penguin::log::LogLevel p_level, std::string_view p_message, const std::source_location& p_location);
        LogEntry();
    };

	class LoggerImpl {
    public:
        LoggerImpl();
        ~LoggerImpl();

        std::string log_level_to_string(penguin::log::LogLevel level) const;
        std::string format_log_entry(const LogEntry& entry) const;
        void write_log(const LogEntry& entry);

        mutable std::mutex log_mutex;

        std::ofstream log_file;
        std::filesystem::path log_path;

        LogEntry last_error;
        bool has_error;
        penguin::log::LogLevel min_log_level;
	};
}

/* Expected output:
[2025-05-30 12:34:56.789] [INFO] Game started (main.cpp:32:5 in int main())
[2025-05-30 12:34:56.790] [DEBUG] Initializing subsystems (main.cpp:33:5 in int main())
[2025-05-30 12:34:56.791] [INFO] Loading texture: player.png (main.cpp:17:9 in void LoadTexture(const std::string&))
[2025-05-30 12:34:56.792] [INFO] Texture loaded successfully: player.png (main.cpp:25:9 in void LoadTexture(const std::string&))
[2025-05-30 12:34:56.793] [INFO] Loading texture: missing.png (main.cpp:17:9 in void LoadTexture(const std::string&))
[2025-05-30 12:34:56.794] [ERROR] Failed to load texture: file not found (main.cpp:21:9 in void LoadTexture(const std::string&))
[2025-05-30 12:34:56.795] [ERROR] Filename cannot be empty (main.cpp:11:9 in void LoadTexture(const std::string&))
[2025-05-30 12:34:56.795] [ERROR] Window_Creation_Error_Failed: The window was not created.
Last error occurred: Filename cannot be empty
Error details: main.cpp:11 in void LoadTexture(const std::string&)
[2025-05-30 12:34:56.796] [WARN] This will be logged (main.cpp:52:5 in int main())
Total errors logged: 2
*/