#pragma once

#include <penguin_api.hpp>
#include <penguin_framework/common/native_types.hpp>
#include <memory>

namespace penguin::internal::input {
    class InputImpl;
}

namespace penguin::input {

    class PENGUIN_API Input {
    public:
        Input(NativeEventPtr e);
        ~Input();

        // Delete copy semantics

        Input(const Input&) = delete;
        Input& operator=(const Input&) = delete;

        // Move semantics

        Input(Input&&) noexcept;
        Input& operator=(Input&&) noexcept;

        // Singleton access

        static Input& get_instance();

        // Keyboard functions


        // Mouse button functions

        
        // Mouse motion functions


        // Mouse wheel functions

    private:
        std::unique_ptr<penguin::internal::input::InputImpl> pimpl_;
    };

}