#include <penguin_framework/events/input_event.hpp>
#include <events/internal/input_event_impl.hpp>
#include <penguin_framework/logger/logger.hpp>

namespace penguin::events {

	InputEvent::InputEvent(NativeEventPtr e) : pimpl_(nullptr) {
		// Log attempt to create an event
		PF_LOG_INFO("Attempting to create an event...");

		if (e.ptr) {
			pimpl_ = std::make_unique<penguin::internal::events::InputEventImpl>(*e.as<SDL_Event>());
			PF_LOG_INFO("Success: InputEvent created successfully.");
		}
		else {
			PF_LOG_ERROR("Event_Creation_Failed: The event is NOT an InputEvent.");
		}
	}

	InputEvent::~InputEvent() = default;

	// Validity checking

	bool InputEvent::is_valid() const noexcept {
		if (!pimpl_) {
			return false;
		}

		return pimpl_->has_event();
	}

	InputEvent::operator bool() const noexcept {
		return is_valid();
	}

	EventType InputEvent::type() const {
		if (!is_valid()) {
			PF_LOG_WARNING("type() called on an uninitialized, destroyed or invalid input event.");
			return EventType::Invalid;
		}
		
		EventType res = pimpl_->type;

		if (res == EventType::Invalid) {
			PF_LOG_WARNING("Internal_System_Error: invalid or unsupported input event type detected.");
		}

		return res;
	}

	bool InputEvent::is_keyboard_event() const noexcept {
		return is_valid() &&
			(pimpl_->type == EventType::KeyboardDown ||
				pimpl_->type == EventType::KeyboardUp);
	}

	bool InputEvent::is_mouse_button_event() const noexcept {
		return is_valid() &&
			(pimpl_->type == EventType::MouseButtonDown ||
				pimpl_->type == EventType::MouseButtonUp);
	}

	bool InputEvent::is_mouse_motion_event() const noexcept {
		return is_valid() && pimpl_->type == EventType::MouseMotion;
	}

	bool InputEvent::is_mouse_wheel_event() const noexcept {
		return is_valid() && pimpl_->type == EventType::MouseWheel;
	}

	const KeyboardEvent& InputEvent::as_keyboard() const {
		if (!is_keyboard_event()) {
			PF_LOG_WARNING("Invalid_Operation: InputEvent is not a keyboard event.");
			static const KeyboardEvent dummy{};
			return dummy;
		}
		return std::get<KeyboardEvent>(pimpl_->event);
	}

	const MouseButtonEvent& InputEvent::as_mouse_button() const {
		if (!is_mouse_button_event()) {
			PF_LOG_WARNING("Invalid_Operation: InputEvent is not a mouse button event.");
			static const MouseButtonEvent dummy{};
			return dummy;
		}
		return std::get<MouseButtonEvent>(pimpl_->event);
	}

	const MouseMotionEvent& InputEvent::as_mouse_motion() const {
		if (!is_mouse_motion_event()) {
			PF_LOG_WARNING("Invalid_Operation: InputEvent is not a mouse motion event.");
			static const MouseMotionEvent dummy{};
			return dummy;
		}
		return std::get<MouseMotionEvent>(pimpl_->event);
	}

	const MouseWheelEvent& InputEvent::as_mouse_wheel() const {
		if (!is_mouse_wheel_event()) {
			PF_LOG_WARNING("Invalid_Operation: InputEvent is not a mouse wheel event.");
			static const MouseWheelEvent dummy{};
			return dummy;
		}
		return std::get<MouseWheelEvent>(pimpl_->event);
	}

	bool InputEvent::is_keyboard_down() const noexcept {
		return is_keyboard_event() && pimpl_->type == EventType::KeyboardDown;
	}

	bool InputEvent::is_keyboard_up() const noexcept {
		return is_keyboard_event() && pimpl_->type == EventType::KeyboardUp;
	}

	bool InputEvent::is_key_pressed(input::keyboard::Key key) const {
		return is_keyboard_down() && as_keyboard().key == key;
	}

	bool InputEvent::is_key_released(input::keyboard::Key key) const {
		return is_keyboard_up() && as_keyboard().key == key;
	}

	bool InputEvent::is_mouse_button_down() const noexcept {
		return is_mouse_button_event() && pimpl_->type == EventType::MouseButtonDown;
	}

	bool InputEvent::is_mouse_button_up() const noexcept {
		return is_mouse_button_event() && pimpl_->type == EventType::MouseButtonUp;
	}

	bool InputEvent::is_mouse_pressed(input::mouse::MouseButton btn) const noexcept {
		return is_mouse_button_down() && as_mouse_button().button == btn;
	}

	bool InputEvent::is_mouse_released(input::mouse::MouseButton btn) const noexcept {
		return is_mouse_button_up() && as_mouse_button().button == btn;
	}

	std::pair<float, float> InputEvent::get_abs_mouse_pos() const {
		if (!is_mouse_motion_event()) {
			return std::pair<float, float>(math::neg_inf, math::neg_inf);
		}

		float abs_x = as_mouse_motion().x;
		float abs_y = as_mouse_motion().y;

		return std::pair<float, float>(abs_x, abs_y);
	}

	std::pair<float, float> InputEvent::get_rel_mouse_pos() const {
		if (!is_mouse_motion_event()) {
			return std::pair<float, float>(math::neg_inf, math::neg_inf);
		}

		float rel_x = as_mouse_motion().rel_x;
		float rel_y = as_mouse_motion().rel_y;

		return std::pair<float, float>(rel_x, rel_y);
	}

	bool InputEvent::is_mouse_wheel_down() const {
		if (!is_mouse_motion_event()) {
			return false;
		}

		if (as_mouse_wheel().direction == input::mouse::MouseWheelDirection::Normal) {
			return as_mouse_wheel().integer_y < 0;
		}
		
		return (-1 * as_mouse_wheel().integer_y) < 0;
	}

	bool InputEvent::is_mouse_wheel_up() const {
		if (!is_mouse_motion_event()) {
			return false;
		}

		if (as_mouse_wheel().direction == input::mouse::MouseWheelDirection::Normal) {
			return as_mouse_wheel().integer_y > 0;
		}

		return (-1 * as_mouse_wheel().integer_y) > 0;
	}

	std::pair<float, float> InputEvent::get_mouse_wheel_pos() const {
		if (!is_mouse_wheel_event()) {
			return std::pair<float, float>(math::neg_inf, math::neg_inf);
		}

		float x = as_mouse_wheel().x;
		float y = as_mouse_wheel().y;

		return std::pair<float, float>(x, y);
	}

}
