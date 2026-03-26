#pragma once

#include <penguin_api.hpp>
#include <penguin_framework/common/native_types.hpp>
#include <penguin_framework/events/input_event.hpp>
#include <penguin_framework/math/vector2.hpp>
#include <penguin_framework/math/vector2i.hpp>
#include <memory>

namespace penguin::internal::input {
    class InputImpl;
}

namespace penguin::input {

    class PENGUIN_API Input {
    public:
        Input();
        ~Input();

        Input(const Input&) = delete;
        Input& operator=(const Input&) = delete;

		Input(Input&&) noexcept = default;
        Input& operator=(Input&&) noexcept = default;

		[[nodiscard]] static bool is_valid() noexcept;

		// General functions 

		static void update(const penguin::events::InputEvent& e);
		static void clear();

		// Keyboard functions

		static bool is_key_pressed(keyboard::Key key);
		static bool is_key_just_pressed(keyboard::Key key);
		static bool is_key_just_released(keyboard::Key key);
		static bool is_key_pressed(keyboard::Scan keycode);
		static bool is_key_just_pressed(keyboard::Scan keycode);
		static bool is_key_just_released(keyboard::Scan keycode);
		static bool is_any_key_pressed();
		static bool is_any_key_just_pressed();
		static bool is_any_key_just_released();

		// Mouse button functions

		static bool is_mouse_button_pressed(penguin::input::mouse::Button btn);
		static bool is_mouse_button_just_pressed(penguin::input::mouse::Button btn);
		static bool is_mouse_button_just_released(penguin::input::mouse::Button btn);

		// Mouse motion functions

		static penguin::math::Vector2 get_abs_mouse_pos();
		static penguin::math::Vector2 get_rel_mouse_pos();

		// Mouse wheel functions

		static bool is_mouse_wheel_down();
		static bool is_mouse_wheel_up();

		static penguin::math::Vector2i get_discrete_mouse_wheel_pos();
		static penguin::math::Vector2 get_mouse_wheel_pos();

    private:
        static std::unique_ptr<penguin::internal::input::InputImpl> pimpl_;
    };

}