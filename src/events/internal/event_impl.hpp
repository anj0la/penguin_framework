#pragma once

#include <memory>
#include <variant>
#include <penguin_framework/events/event_type.hpp>

#include <SDL3/SDL_events.h>

namespace penguin::internal::events {

	using InputEvent = std::variant<
		KeyboardEvent,
		MouseButtonEvent,
		MouseMotionEvent,
		MouseWheelEvent,
		GamepadEvent>;

	using Event = std::variant<QuitEvent, WindowEvent, InputEvent, CustomEvent>;

	struct EventImpl {
		EventType type;
		Event event;

		EventImpl();
		~EventImpl();		
	};
}