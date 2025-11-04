#pragma once

#include <memory>
#include <variant>
#include <penguin_framework/events/input_event_type.hpp>

#include <SDL3/SDL_events.h>

namespace penguin::internal::events {

	using InputEvent = std::variant<
		std::monostate,
		penguin::events::KeyboardEvent,
		penguin::events::MouseButtonEvent,
		penguin::events::MouseMotionEvent,
		penguin::events::MouseWheelEvent>;

	struct InputEventImpl {
		penguin::events::EventType type;
		InputEvent event;

		InputEventImpl(const SDL_Event& e);
		~InputEventImpl();

		bool has_event() const;
	};
}