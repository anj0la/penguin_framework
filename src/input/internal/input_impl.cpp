#include <input/internal/input_impl.hpp>

namespace penguin::internal::input {

	// General functions 

	bool InputImpl::update(const penguin::events::InputEvent& e) {
		switch (e.type()) {
			case penguin::events::EventType::KeyboardDown: update_keyboard_states(e.as_keyboard()); break;
			case penguin::events::EventType::KeyboardUp: update_keyboard_states(e.as_keyboard()); break;
			case penguin::events::EventType::MouseButtonDown: update_mouse_buttons(e.as_mouse_button()); break;
			case penguin::events::EventType::MouseButtonUp: update_mouse_buttons(e.as_mouse_button()); break;
			case penguin::events::EventType::MouseMotion: update_mouse_motion(e.as_mouse_motion()); break;
			case penguin::events::EventType::MouseWheel: update_mouse_wheel(e.as_mouse_wheel()); break;
			default: // event type is invalid
				return false; // indicates that input singleton could not be updated
		}

		return true;
	}

	void InputImpl::update_keyboard_states(const penguin::events::KeyboardEvent& e) {
		if (e.down) {
			if (!e.repeat) keys_pressed[e.scan] = true;		// just pressed this frame
			keys_current[e.scan] = true;					// currently held down
		}

		if (!e.down) { // key is up (released)
			keys_released[e.scan] = true;					// just released this frame
			keys_current[e.scan] = false;					// no longer held down
		}
	}

	void InputImpl::update_mouse_buttons(const penguin::events::MouseButtonEvent& e) {
		if (e.down) {

			if (e.clicks == 1) buttons_pressed[e.btn] = true; // pressed the button just once
			buttons_current[e.btn] = true;					  // currently held down
		}

		if (!e.down) { // button is up (released)
			buttons_released[e.btn] = true;					  // just released this frame
			buttons_current[e.btn] = false;					  // no longer held down
		}
	}

	void InputImpl::update_mouse_motion(const penguin::events::MouseMotionEvent& e) {
		position = penguin::math::Vector2(e.x, e.y);
		relative = penguin::math::Vector2(e.rel_x, e.rel_y);
	}

	void InputImpl::update_mouse_wheel(const penguin::events::MouseWheelEvent& e) {
		scroll_delta = penguin::math::Vector2i(e.integer_x, e.integer_y);
		scroll_delta_pixels = penguin::math::Vector2(e.x, e.y);
	}

	void InputImpl::clear() { // should be called after every update call in the game loop
		keys_pressed.clear();
		keys_released.clear();
		buttons_pressed.clear();
		buttons_released.clear();
	}

	// Keyboard functions

	bool InputImpl::is_key_pressed(keyboard::Key key) { // if the key has been pressed, then keys_current will be true
		keyboard::Scan scan = keyboard::key_to_scan.at(key);
		return keys_current[scan];
	}

	bool InputImpl::is_key_just_pressed(keyboard::Key key) { // use keys_pressed here to check
		keyboard::Scan scan = keyboard::key_to_scan.at(key);
		return keys_pressed[scan];
	}

	bool InputImpl::is_key_just_released(keyboard::Key key) {
		keyboard::Scan scan = keyboard::key_to_scan.at(key);
		return keys_released[scan];
	}

	bool InputImpl::is_key_pressed(keyboard::Scan keycode) {
		return keys_current[keycode];
	}

	bool InputImpl::is_key_just_pressed(keyboard::Scan keycode) {
		return keys_pressed[keycode];
	}

	bool InputImpl::is_key_just_released(keyboard::Scan keycode) {
		return keys_released[keycode];
	}

	bool InputImpl::is_any_key_pressed() { 
		for (const auto& pair : keyboard::key_to_scan) {
			if (keys_current[pair.second]) { // pair.second = a Scan value, and we check if that physical key has been pressed
				return true;
			}
		}
		return false;
	}

	bool InputImpl::is_any_key_just_pressed() {
		for (const auto& pair : keyboard::key_to_scan) {
			if (keys_pressed[pair.second]) {
				return true;
			}
		}
		return false;
	}

	bool InputImpl::is_any_key_just_released() {
		for (const auto& pair : keyboard::key_to_scan) {
			if (keys_released[pair.second]) {
				return true;
			}
		}
		return false;
	}
	
	// Mouse button functions
	
	bool InputImpl::is_mouse_button_pressed(penguin::input::mouse::Button btn) {
		return buttons_current[btn];
	}

	bool InputImpl::is_mouse_button_just_pressed(penguin::input::mouse::Button btn) {
		return buttons_pressed[btn];
	}

	bool InputImpl::is_mouse_button_just_released(penguin::input::mouse::Button btn) {
		return buttons_released[btn];
	}

	// Mouse motion functions

	penguin::math::Vector2 InputImpl::get_abs_mouse_pos() {
		return position;
	}

	penguin::math::Vector2 InputImpl::get_rel_mouse_pos() {
		return relative;
	}

	// Mouse wheel functions

	bool InputImpl::is_mouse_wheel_down() {
		return scroll_delta.y < 0 || scroll_delta_pixels.y < 0.0;
	}

	bool InputImpl::is_mouse_wheel_up() {
		return scroll_delta.y > 0 || scroll_delta_pixels.y > 0;
	}

	penguin::math::Vector2i InputImpl::get_discrete_mouse_wheel_pos() {
		return scroll_delta;
	}

	penguin::math::Vector2 InputImpl::get_mouse_wheel_pos() {
		return scroll_delta_pixels;
	}
}