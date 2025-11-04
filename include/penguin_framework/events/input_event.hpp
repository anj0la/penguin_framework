#pragma once

#include <penguin_api.hpp>
#include <penguin_framework/events/input_event_type.hpp>
#include <penguin_framework/common/native_types.hpp>
#include <memory>

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
		[[nodiscard]] bool is_key(input::keyboard::Key key) const;  

		[[nodiscard]] bool is_mouse_button_down() const noexcept;
		[[nodiscard]] bool is_mouse_button_up() const noexcept;
		[[nodiscard]] bool is_mouse_button(input::mouse::MouseButton btn) const;

	private:
		std::unique_ptr<penguin::internal::events::InputEventImpl> pimpl_;
	};
}