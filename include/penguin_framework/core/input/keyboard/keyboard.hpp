//#pragma once
//
//#include <penguin_framework/core/input/keyboard/keyboard_keys.hpp>
//#include <SDL3/SDL_events.h>
//#include <array>
//
//namespace penguin::core::input::keyboard {
//	class Keyboard {
//	public:
//		static void handle_keyboard_event(const SDL_Event& p_event);
//		static bool is_key_pressed(PF_Key key);
//		static bool is_key_just_pressed(PF_Key key);
//		static bool is_key_just_released(PF_Key key);
//		static bool is_any_key_pressed();
//		static bool is_any_key_just_pressed();
//		static bool is_any_key_just_released();
//		static void update();
//
//		// Callback functions (registerd from input probs)
//		
//
//	private:
//		static std::array<bool, NumKeys> current; // current state of the key (use to check persistence pressing)
//		static std::array<bool, NumKeys> pressed; // keys that have just been pressed (resets every update rate)
//		static std::array<bool, NumKeys> released; // keys that have just been released
//	};
//}
