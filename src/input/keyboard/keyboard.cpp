//#include <penguin_framework/core/input/keyboard/keyboard.hpp>
//
//using penguin::core::input::keyboard::Keyboard;
//using penguin::core::input::keyboard::NumKeys;
//
//void Keyboard::handle_keyboard_event(const SDL_Event& p_event) {
//	PF_Key key = static_cast<PF_Key>(p_event.key.key);
//
//	size_t i = key_to_index(key);
//	if (i == InvalidKeyIndex) return;
//
//	if (p_event.type == SDL_EVENT_KEY_DOWN) {
//
//		if (!p_event.key.repeat) pressed[i] = true;
//		current[i] = true;
//	}
//	else if (p_event.type == SDL_EVENT_KEY_UP) {
//		released[i] = true;
//		current[i] = false;
//	}
//}
//
//bool Keyboard::is_key_pressed(PF_Key key) {
//	size_t i = key_to_index(key);
//	return i != InvalidKeyIndex && current[i];
//}
//
//bool Keyboard::is_key_just_pressed(PF_Key key) {
//	size_t i = key_to_index(key);
//	return i != InvalidKeyIndex && pressed[i];
//}
//
//bool Keyboard::is_key_just_released(PF_Key key) {
//	size_t i = key_to_index(key);
//	return i != InvalidKeyIndex && released[i];
//}
//
//bool Keyboard::is_any_key_pressed() {
//	for (size_t i = 0; i < NumKeys; ++i) {
//		if (current[i]) return true;
//	}
//
//	return InvalidKeyIndex;
//}
//
//bool Keyboard::is_any_key_just_pressed() {
//	for (size_t i = 0; i < NumKeys; ++i) {
//		if (pressed[i]) return true;
//	}
//
//	return InvalidKeyIndex;
//}
//
//bool Keyboard::is_any_key_just_released() {
//	for (size_t i = 0; i < NumKeys; ++i) {
//		if (released[i]) return true;
//	}
//
//	return InvalidKeyIndex;
//}
//
//void Keyboard::update() {
//	pressed.fill(false);
//	released.fill(false);
//}