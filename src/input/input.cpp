#include <penguin_framework/input/input.hpp>
#include <input/internal/input_impl.hpp>
#include <penguin_framework/logger/logger.hpp>

namespace penguin::input {

	std::unique_ptr<penguin::internal::input::InputImpl> Input::pimpl_ = nullptr; 

	Input::Input() {
		// Log attempt to create the input system
		PF_LOG_INFO("Attempting to create the input system...");

		pimpl_ = std::make_unique<penguin::internal::input::InputImpl>();

		if (pimpl_) {
			PF_LOG_INFO("Success: Input created successfully.");
		}
		else { // otherwise, we don't have a valid input system (still nullptr)
			PF_LOG_ERROR("Input_System_Creation_Failed: The input system could not be created because of an INVALID InputEvent."); // TODO: Create better system for adding error codes
		}
	}

	Input::~Input() = default;

	// Validity checking

	bool Input::is_valid() noexcept {
		if (!pimpl_) {
			return false;
		}

		return true;
	}

	// General functions

	void Input::update(const penguin::events::InputEvent& e) {
		if (!is_valid()) {
			PF_LOG_WARNING("update() called on an uninitialized, destroyed or invalid input system.");
		}

		bool res = pimpl_->update(e);

		if (!res) {
			PF_LOG_WARNING("Internal_System_Error: invalid or unsupported input event type detected.");
		}
	}

	void Input::clear() {
		if (!is_valid()) {
			PF_LOG_WARNING("clear() called on an uninitialized, destroyed or invalid input system.");
		}

		pimpl_-> clear();
	}

	// Keyboard functions

	bool Input::is_key_pressed(keyboard::Key key) {
		if (!is_valid()) {
			PF_LOG_WARNING("is_key_pressed() called on an uninitialized, destroyed or invalid input system.");
		}

		return pimpl_->is_key_pressed(key);
	}

	bool Input::is_key_just_pressed(keyboard::Key key) {
		if (!is_valid()) {
			PF_LOG_WARNING("is_key_just_pressed() called on an uninitialized, destroyed or invalid input system.");
		}

		return pimpl_->is_key_just_pressed(key);
	}

	bool Input::is_key_just_released(keyboard::Key key) {
		if (!is_valid()) {
			PF_LOG_WARNING("is_key_just_released() called on an uninitialized, destroyed or invalid input system.");
		}

		return pimpl_->is_key_just_released(key);
	}

	bool Input::is_key_pressed(keyboard::Scan keycode) {
		if (!is_valid()) {
			PF_LOG_WARNING("is_key_pressed() called on an uninitialized, destroyed or invalid input system.");
		}

		return pimpl_->is_key_pressed(keycode);
	}

	bool Input::is_key_just_pressed(keyboard::Scan keycode) {
		if (!is_valid()) {
			PF_LOG_WARNING("is_key_just_pressed() called on an uninitialized, destroyed or invalid input system.");
		}

		return pimpl_->is_key_just_pressed(keycode);
	}

	bool Input::is_key_just_released(keyboard::Scan keycode) {
		if (!is_valid()) {
			PF_LOG_WARNING("is_key_just_released() called on an uninitialized, destroyed or invalid input system.");
		}

		return pimpl_->is_key_just_released(keycode);
	}

	bool Input::is_any_key_pressed() {
		if (!is_valid()) {
			PF_LOG_WARNING("is_any_key_pressed() called on an uninitialized, destroyed or invalid input system.");
		}

		return pimpl_->is_any_key_pressed();
	}

	bool Input::is_any_key_just_pressed() {
		if (!is_valid()) {
			PF_LOG_WARNING("is_any_key_just_pressed() called on an uninitialized, destroyed or invalid input system.");
		}

		return pimpl_->is_any_key_just_pressed();
	}

	bool Input::is_any_key_just_released() {
		if (!is_valid()) {
			PF_LOG_WARNING("is_any_key_just_released() called on an uninitialized, destroyed or invalid input system.");
		}

		return pimpl_->is_any_key_just_released();
	}

	// Mouse button functions

	bool Input::is_mouse_button_pressed(mouse::Button btn) {
		if (!is_valid()) {
			PF_LOG_WARNING("is_mouse_button_pressed() called on an uninitialized, destroyed or invalid input system.");
		}

		return pimpl_->is_mouse_button_pressed(btn);
	}

	bool Input::is_mouse_button_just_pressed(mouse::Button btn) {
		if (!is_valid()) {
			PF_LOG_WARNING("is_mouse_button_just_pressed() called on an uninitialized, destroyed or invalid input system.");
		}

		return pimpl_->is_mouse_button_just_pressed(btn);
	}

	bool Input::is_mouse_button_just_released(mouse::Button btn) {
		if (!is_valid()) {
			PF_LOG_WARNING("is_mouse_button_just_released() called on an uninitialized, destroyed or invalid input system.");
		}

		return pimpl_->is_mouse_button_just_released(btn);
	}

	// Mouse motion functions

	penguin::math::Vector2 Input::get_abs_mouse_pos() {
		if (!is_valid()) {
			PF_LOG_WARNING("get_abs_mouse_pos() called on an uninitialized, destroyed or invalid input system.");
		}

		return pimpl_->get_abs_mouse_pos();
	}

	penguin::math::Vector2 Input::get_rel_mouse_pos() {
		if (!is_valid()) {
			PF_LOG_WARNING("get_rel_mouse_pos() called on an uninitialized, destroyed or invalid input system.");
		}

		return pimpl_->get_rel_mouse_pos();
	}

	// Mouse wheel functions

	bool Input::is_mouse_wheel_down() {
		if (!is_valid()) {
			PF_LOG_WARNING("is_mouse_wheel_down() called on an uninitialized, destroyed or invalid input system.");
		}

		return pimpl_->is_mouse_wheel_down();
	}
	
	bool Input::is_mouse_wheel_up() {
		if (!is_valid()) {
			PF_LOG_WARNING("is_mouse_wheel_up() called on an uninitialized, destroyed or invalid input system.");
		}

		return pimpl_->is_mouse_wheel_up();
	}

	penguin::math::Vector2i Input::get_discrete_mouse_wheel_pos() { // TODO: this name is too long, make it shorter
		if (!is_valid()) {
			PF_LOG_WARNING("get_discrete_mouse_wheel_pos() called on an uninitialized, destroyed or invalid input system.");
		}

		return pimpl_->get_discrete_mouse_wheel_pos();
	}

	penguin::math::Vector2 Input::get_mouse_wheel_pos() {
		if (!is_valid()) {
			PF_LOG_WARNING("get_mouse_wheel_pos() called on an uninitialized, destroyed or invalid input system.");
		}

		return pimpl_->get_mouse_wheel_pos();
	}
}
