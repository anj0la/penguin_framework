#pragma once

#include <penguin_framework/input/mouse/mouse_button.hpp>
#include <penguin_framework/events/input_event.hpp>
#include <penguin_framework/math/vector2.hpp>
#include <penguin_framework/math/vector2i.hpp>

#include <input/internal/key_to_scan.hpp>

#include <memory>
#include <vector>
#include <utility>
#include <unordered_map>

namespace penguin::internal::input {

	class InputImpl {
	public:
		InputImpl() = default;
		~InputImpl() = default;

		// General functions 

		bool update(const penguin::events::InputEvent& e);
		void update_keyboard_states(const penguin::events::KeyboardEvent& e);
		void update_mouse_buttons(const penguin::events::MouseButtonEvent& e);
		void update_mouse_motion(const penguin::events::MouseMotionEvent& e);
		void update_mouse_wheel(const penguin::events::MouseWheelEvent& e);

		void clear();

		// Keyboard functions

		bool is_key_pressed(keyboard::Key key);
		bool is_key_just_pressed(keyboard::Key key);
		bool is_key_just_released(keyboard::Key key);
		bool is_key_pressed(keyboard::Scan keycode);
		bool is_key_just_pressed(keyboard::Scan keycode);
		bool is_key_just_released(keyboard::Scan keycode);
		bool is_any_key_pressed();
		bool is_any_key_just_pressed();
		bool is_any_key_just_released();

		// Mouse button functions

		bool is_mouse_button_pressed(penguin::input::mouse::Button btn);
		bool is_mouse_button_just_pressed(penguin::input::mouse::Button btn);
		bool is_mouse_button_just_released(penguin::input::mouse::Button btn);

		// Mouse motion functions

		penguin::math::Vector2 get_abs_mouse_pos();
		penguin::math::Vector2 get_rel_mouse_pos();

		// Mouse wheel functions

		bool is_mouse_wheel_down();
		bool is_mouse_wheel_up();

		penguin::math::Vector2i get_discrete_mouse_wheel_pos(); // returns scroll_delta (int version)
		penguin::math::Vector2 get_mouse_wheel_pos(); // returns scroll delta in pixels (float version)

	private:
		// Keyboard states

		std::unordered_map<keyboard::Scan, bool> keys_current; // current state of the key (use to check persistence pressing)
		std::unordered_map<keyboard::Scan, bool> keys_pressed; // keys that have just been pressed (resets every update)
		std::unordered_map<keyboard::Scan, bool> keys_released; // keys that have just been released (resets every update)

		// Mouse button states

		std::unordered_map<penguin::input::mouse::Button, bool> buttons_current;
		std::unordered_map<penguin::input::mouse::Button, bool> buttons_pressed;
		std::unordered_map<penguin::input::mouse::Button, bool> buttons_released;

		// Mouse motion states
		
		penguin::math::Vector2 position; // absolute position
		penguin::math::Vector2 relative; // relative position
		penguin::math::Vector2 delta;

		// Mouse wheel states

		penguin::math::Vector2i scroll_delta;
		penguin::math::Vector2 scroll_delta_pixels;

	};

}
