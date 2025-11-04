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



}
