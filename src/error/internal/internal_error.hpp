#pragma once

#include <stdexcept>
#include <utility>

namespace penguin::internal::error {

    enum class ErrorCode {
        Unknown = -1,
        Success = 0,
        SDL_Init_Failed,
        SDL_Subsystem_Init_Failed,
        SDL_Function_Failed,         // For generic SDL calls 
        Window_Creation_Failed,
        Window_Function_Failed,
        Renderer_Creation_Failed,
        Texture_Creation_Failed,
        Sprite_Creation_Failed,
        Asset_Manager_Creation_Failed,
        Texture_Loader_Creation_Failed,
        Resource_Load_Failed,
        Invalid_Input,
        Invalid_Parameter          // For invalid paths, etc.
    };

    inline const char* error_code_to_string(ErrorCode error) {
        switch (error) {
            case ErrorCode::Unknown:
                return "Unknown";
            case ErrorCode::Success:
                return "Success";
            case ErrorCode::SDL_Init_Failed:
                return "SDL_Init_Failed";
            case ErrorCode::SDL_Subsystem_Init_Failed:
                return "SDL_Subsystem_Init_Failed";
            case ErrorCode::SDL_Function_Failed:
                return "SDL_Function_Failed";
            case ErrorCode::Window_Creation_Failed:
                return "Window_Creation_Failed";
            case ErrorCode::Window_Function_Failed:
                return "Window_Function_Failed";
            case ErrorCode::Renderer_Creation_Failed:
                return "Renderer_Creation_Failed";
            case ErrorCode::Texture_Creation_Failed:
                return "Texture_Creation_Failed";
            case Sprite_Creation_Failed:
                return "Sprite_Creation_Failed";
            case ErrorCode::Asset_Manager_Creation_Failed:
                return "Asset_Manager_Creation_Failed";
            case ErrorCode::Texture_Loader_Creation_Failed:
                return "Texture_Loader_Creation_Failed";
            case ErrorCode::Resource_Load_Failed:
                return "Resource_Load_Failed";
            case ErrorCode::Invalid_Input:
                return "Invalid_Input";
            case ErrorCode::Invalid_Parameter:
                return "Invalid_Parameter";
            }
        return "Unknown";
    }

    class InternalError final : public std::runtime_error {

    public:
        InternalError(const char* message, ErrorCode error = ErrorCode::Unknown)
            : std::runtime_error(message), error_code_(error) {}
        ~InternalError() noexcept override = default;

        [[nodiscard]] ErrorCode get_error() const noexcept { return error_code_; }

        inline static void throw_if(bool condition, const char* message, ErrorCode error) {
            if (condition) throw InternalError{ message, error };
        }
    private:
        ErrorCode error_code_;
    };
}

