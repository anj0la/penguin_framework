#pragma once

#include <penguin_api.hpp>
#include <penguin_framework/events/input_event_type.hpp>
#include <penguin_framework/common/native_types.hpp>
#include <penguin_framework/math/math_types.hpp>
#include <memory>
#include <utility>

namespace penguin::internal::events {
	struct InputEventImpl;
}

namespace penguin::events {

	class PENGUIN_API InputEvent {
	public:
		InputEvent(NativeEventPtr e);
		~InputEvent();

		[[nodiscard]] bool is_valid() const noexcept;
		[[nodiscard]] explicit operator bool() const noexcept;

		EventType type() const;

		// InputEvent e(ptr) -> where ptr is an SDL_Event pointer converted to a void* pointer
		// KeyboardEvent e_k = e.as_keyboard();
		// Then the Keyboard event is similar to the SDL_Event
		// So we need to then create an abstraction that uses this

		[[nodiscard]] bool is_keyboard_event() const noexcept;
		[[nodiscard]] bool is_mouse_button_event() const noexcept;
		[[nodiscard]] bool is_mouse_motion_event() const noexcept;
		[[nodiscard]] bool is_mouse_wheel_event() const noexcept;

		[[nodiscard]] const KeyboardEvent& as_keyboard() const;
		[[nodiscard]] const MouseButtonEvent& as_mouse_button() const;
		[[nodiscard]] const MouseMotionEvent& as_mouse_motion() const;
		[[nodiscard]] const MouseWheelEvent& as_mouse_wheel() const;

		[[nodiscard]] bool is_keyboard_down() const noexcept;
		[[nodiscard]] bool is_keyboard_up() const noexcept;

		// Check event TYPE + specific key
		[[nodiscard]] bool is_key_pressed(input::keyboard::Key key) const;
		[[nodiscard]] bool is_key_released(input::keyboard::Key key) const;

		// Similar for mouse
		[[nodiscard]] bool is_mouse_button_down() const noexcept;
		[[nodiscard]] bool is_mouse_button_up() const noexcept;

		[[nodiscard]] bool is_mouse_pressed(input::mouse::MouseButton btn) const;
		[[nodiscard]] bool is_mouse_released(input::mouse::MouseButton btn) const;

		// Mouse motion
		[[nodiscard]] std::pair<float, float> get_abs_mouse_pos() const;
		[[nodiscard]] std::pair<float, float> get_rel_mouse_pos() const;

		// Mouse wheel
		[[nodiscard]] bool is_mouse_wheel_down() const;
		[[nodiscard]] bool is_mouse_wheel_up() const;

		[[nodiscard]] std::pair<float, float> get_mouse_wheel_pos() const;


	private:
		std::unique_ptr<penguin::internal::events::InputEventImpl> pimpl_;
	};
}