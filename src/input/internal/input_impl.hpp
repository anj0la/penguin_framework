#pragma once

#include <penguin_framework/input/mouse/mouse_button.hpp>

#include <input/internal/key_to_scan.hpp>

#include <memory>
#include <vector>
#include <pair>
#include <unordered_map>
#include <SDL_events.h>

namespace penguin::internal::input {

	class InputImpl {
	public:
		InputImpl(SDL_Event e);
		~InputImpl();

		SDL_Event event; // should this be a pointer? -> probably not, because we have to deference the pointer when calling SDL_PollEvent


		// General functions 

		static void update(SDL_Event e);
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

		std::pair<float, float> get_abs_mouse_pos();
		std::pair<float, float> get_rel_mouse_pos();

		// Mouse wheel functions

		static bool is_mouse_wheel_down() const;
		static bool is_mouse_wheel_up() const;

		std::pair<float, float> get_mouse_wheel_pos() const;

		static std::unordered_map<keyboard::Scan keycode, bool> current_keys; // current state of the key (use to check persistence pressing)
		static std::unordered_map<keyboard::Scan keycode, bool> pressed_keys; // keys that have just been pressed (resets every update)
		static std::array<keyboard::Scan keycode, bool, NumKeys> released_keys; // keys that have just been released (resets every update)
	};

}
