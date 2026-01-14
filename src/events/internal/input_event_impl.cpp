#include <events/internal/input_event_impl.hpp>

namespace penguin::internal::events {

	InputEventImpl::InputEventImpl(const SDL_Event& e) {
		// Keyboard
		switch (e.type) {
			case SDL_EVENT_KEY_DOWN:
				type = penguin::events::EventType::KeyboardDown;
				event = penguin::events::KeyboardEvent{ type, e.key.timestamp, static_cast<penguin::input::keyboard::Scan>(e.key.scancode), 
					static_cast<penguin::input::keyboard::Key>(e.key.key), static_cast<penguin::input::keyboard::KeyMod>(e.key.mod), 
					e.key.down, e.key.repeat };
				break;
			case SDL_EVENT_KEY_UP:
				type = penguin::events::EventType::KeyboardUp;
				event = penguin::events::KeyboardEvent{ type, e.key.timestamp, static_cast<penguin::input::keyboard::Scan>(e.key.scancode),
					static_cast<penguin::input::keyboard::Key>(e.key.key), static_cast<penguin::input::keyboard::KeyMod>(e.key.mod),
					e.key.down, e.key.repeat };				
				break;

		// Mouse Button
			case SDL_EVENT_MOUSE_BUTTON_DOWN:
				type = penguin::events::EventType::MouseButtonDown;
				event = penguin::events::MouseButtonEvent{ type, e.button.timestamp, 
					static_cast<penguin::input::mouse::MouseButton>(e.button.button), e.button.down, e.button.clicks, e.button.x, e.button.y };
				break;
			case SDL_EVENT_MOUSE_BUTTON_UP:
				type = penguin::events::EventType::MouseButtonUp;
				event = penguin::events::MouseButtonEvent{ type, e.button.timestamp,
					static_cast<penguin::input::mouse::MouseButton>(e.button.button), e.button.down, e.button.clicks, e.button.x, e.button.y };
				break;

		// Mouse Motion
			case SDL_EVENT_MOUSE_MOTION:
				type = penguin::events::EventType::MouseMotion;
				event = penguin::events::MouseMotionEvent{ type, e.motion.timestamp, e.motion.x, e.motion.y, e.motion.xrel, e.motion.yrel,
				static_cast<penguin::input::mouse::MouseButtonFlags>(e.motion.state) };
				break;

		// MouseWheel
			case SDL_EVENT_MOUSE_WHEEL:
				type = penguin::events::EventType::MouseMotion;
				event = penguin::events::MouseWheelEvent{ type, e.wheel.timestamp, e.wheel.x, e.wheel.y, e.wheel.mouse_x, e.wheel.mouse_y,
				static_cast<penguin::input::mouse::MouseWheelDirection>(e.wheel.direction) };
				break;
			default:
				type = penguin::events::EventType::Invalid;
				event = std::monostate{}; // invalid event with no state (we avoid throwing an error here as it doesn't make sense to)
										  // however, we will log the error in the API .cpp file
		}
	}
	
	InputEventImpl::~InputEventImpl() = default;

	bool InputEventImpl::has_event() const {
		return !std::holds_alternative<std::monostate>(event); // if it holds an event, holds_alternative should return false
																 // negating it makes it true, otherwise, it should be false
	}
}