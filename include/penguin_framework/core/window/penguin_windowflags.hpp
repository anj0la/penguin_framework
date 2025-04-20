#pragma once

#include <cstdint>
#include <SDL3/SDL_video.h>

namespace penguin::core::window {

	enum class WindowFlags : uint64_t {
		None = 0,
		Fullscreen = SDL_WINDOW_FULLSCREEN,
		Resizable = SDL_WINDOW_RESIZABLE,
		Hidden = SDL_WINDOW_HIDDEN,
		Borderless = SDL_WINDOW_BORDERLESS,
		Minimized = SDL_WINDOW_MINIMIZED,
		Maximized = SDL_WINDOW_MAXIMIZED,
		MouseGrabbed = SDL_WINDOW_MOUSE_GRABBED,
		InputFocus = SDL_WINDOW_INPUT_FOCUS,
		MouseFocus = SDL_WINDOW_MOUSE_FOCUS,
		MouseRelativeMode = SDL_WINDOW_MOUSE_RELATIVE_MODE,
		AlwaysOnTop = SDL_WINDOW_ALWAYS_ON_TOP,
		Transparent = SDL_WINDOW_TRANSPARENT,
		NotFocusable = SDL_WINDOW_NOT_FOCUSABLE
	};

	enum class PF_WindowVSyncFlags : int {
		VSync_Adaptive = -1,
		VSync_Disabled
	};

	// Enable bitwise operations for WindowFlags

	constexpr WindowFlags operator|(WindowFlags lhs, WindowFlags rhs) {
		return static_cast<WindowFlags>(
			static_cast<uint64_t>(lhs) | static_cast<uint64_t>(rhs)
			);
	}

	constexpr WindowFlags operator&(WindowFlags lhs, WindowFlags rhs) {
		return static_cast<WindowFlags>(
			static_cast<uint64_t>(lhs) & static_cast<uint64_t>(rhs)
			);
	}

	constexpr WindowFlags operator~(WindowFlags flag) {
		return static_cast<WindowFlags>(~static_cast<uint64_t>(flag));
	}

	constexpr bool has_flag(WindowFlags flags, WindowFlags test) {
		return (flags & test) != WindowFlags::None;
	}

	inline SDL_WindowFlags to_sdl_flags(WindowFlags flags) {
		return static_cast<SDL_WindowFlags>(static_cast<uint64_t>(flags));
	}
}