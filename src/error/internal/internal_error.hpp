#pragma once

#include <stdexcept>
#include <utility>

namespace penguin::internal::error {

    enum class ErrorCode {
        // General
        Unknown_Error = -1,         // Generic catch-all if no other code fits
        Success = 0,

        // System specific
        System_Init_Failed,
        Subsystem_Init_Failed,
        Internal_System_Error,      // Specific system calls to SDL failed. Should only be used if the underlying SDL call fails.

        // Object Creation / Initialization
        Window_Creation_Failed,
        Renderer_Creation_Failed,
        Texture_Creation_Failed,
        Sprite_Creation_Failed,
        Font_Creation_Failed,
        Text_Creation_Failed,
        //Audio_Device_Open_Failed,
        Asset_Manager_Init_Failed,
        Texture_Loader_Init_Failed,
        Text_Context_Init_Failed,
        Font_Loader_Init_Failed,

        // Resource Handling
        File_Not_Found,             // The path was valid, but the file isn't there
        Resource_Load_Failed,       // Broader category for when loading fails (could be bad format, read error etc.)   

        // Parameter / Input Validation
        Null_Argument,              // A required pointer/reference argument was null/nullptr
        Argument_Out_Of_Range,      // A numerical argument was outside its valid bounds (e.g., negative size, invalid index)
        Invalid_Parameter,          // An argument is invalid for reasons other than null or out-of-range (e.g., empty string for a required name, invalid enum value)

        // Object State / Operation Validity
        Object_Not_Initialized,     // Operation on an object that hasn't been properly set up
        Object_Already_Initialized, // Attempt to initialize an already initialized object
        Object_Destroyed,           // Operation on an object that has been destroyed/released
        Invalid_Operation,          // The operation is not valid in the current context/state
    };
    

    inline const char* error_code_to_string(ErrorCode error) {
        switch (error) {
            case ErrorCode::Unknown_Error:
                return "Unknown_Error";
            case ErrorCode::Success:
                return "Success";

            case ErrorCode::System_Init_Failed:
                return "System_Init_Failed";
            case ErrorCode::Subsystem_Init_Failed:
                return "Subsystem_Init_Failed";

            case ErrorCode::Window_Creation_Failed:
                return "Window_Creation_Failed";
            case ErrorCode::Renderer_Creation_Failed:
                return "Renderer_Creation_Failed";
            case ErrorCode::Texture_Creation_Failed:
                return "Texture_Creation_Failed";
            case ErrorCode::Sprite_Creation_Failed:
                return "Sprite_Creation_Failed";
            case ErrorCode::Font_Creation_Failed:
                return "Font_Creation_Failed";
            case ErrorCode::Text_Creation_Failed:
                return "Text_Creation_Failed";
            case ErrorCode::Asset_Manager_Init_Failed:
                return "Asset_Manager_Creation_Failed";
            case ErrorCode::Texture_Loader_Init_Failed:
                return "Texture_Loader_Creation_Failed";
            case ErrorCode::Font_Loader_Init_Failed:
                return "Font_Loader_Init_Failed";
            case ErrorCode::Text_Context_Init_Failed:
                return "Text_Context_Init_Failed";

            case ErrorCode::File_Not_Found:
                return "Resource_Load_Failed";
            case ErrorCode::Resource_Load_Failed:
                return "Resource_Load_Failed";

            case ErrorCode::Null_Argument:
                return "Invalid_Input";
            case ErrorCode::Argument_Out_Of_Range:
                return "Argument_Out_Of_Range";
            case ErrorCode::Invalid_Parameter:
                return "Invalid_Parameter";

            case ErrorCode::Object_Not_Initialized:
                return "Object_Not_Initialized";
            case ErrorCode::Object_Already_Initialized:
                return "Object_Already_Initialized";
            case ErrorCode::Object_Destroyed:
                return "Object_Destroyed";
            case ErrorCode::Invalid_Operation:
                return "Invalid_Operation";
            }

            
        return "Unknown_Error";
    }

    class InternalError final : public std::runtime_error {

    public:
        InternalError(const char* message, ErrorCode error = ErrorCode::Unknown_Error)
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

