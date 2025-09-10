#pragma once

#include <cstdint>
#include <penguin_framework/input/keyboard/key.hpp>
#include <penguin_framework/input/keyboard/scan.hpp>
#include <penguin_framework/input/keyboard/keymod..hpp>
#include <penguin_framework/input/mouse/mouse_buttons.hpp>
#include <penguin_framework/input/mouse/mouse_wheel.hpp>

namespace penguin::events {

	// Event Types

	enum class EventType : uint32_t {
		Quit,
		Window,
		Input,
		Custom
	};

	// Event Structs

	struct QuitEvent {
		EventType type;
		uint64_t timestamp;
	};

	struct WindowEvent {
		EventType type;
		uint64_t timestamp;
		int32_t param1, param2;
	};

	struct KeyboardEvent {
		EventType type;
		uint64_t timestamp;
		input::keyboard::Scan scan;
		input::keyboard::Key key;
		input::keyboard::KeyMod mod;
		bool down;
		bool repeat;
	};

	struct MouseButtonEvent {
		EventType type;
		uint64_t timestamp;
		input::mouse::MouseButton button;  // mouse button index
		bool down;       
		uint8_t clicks;  // double-click detection
		float x, y;
	};

	struct MouseMotionEvent {
		EventType type;
		uint64_t timestamp;
		float x, y;           // absolute position
		float rel_x, rel_y;   // relative movement
		input::mouse::MouseButtonFlags state;
	};

	struct MouseWheelEvent {
		EventType type;
		uint64_t timestamp;
		float x, y;				// sroll amounts
		float mouse_x, mouse_y; // where the scroll happened
		input::mouse::MouseWheelDirection direction;
	};

	struct CustomEvent {
		EventType type;
		uint64_t timestamp;
		int32_t code;
		int32_t param1, param2;
	};

}