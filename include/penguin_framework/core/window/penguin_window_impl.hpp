#pragma once

#include <penguin_framework/core/window/penguin_windowflags.hpp>
#include <penguin_framework/utils/exception.hpp>
#include <penguin_framework/core/math/vector2i.hpp>
#include <penguin_framework/utils/string.hpp>

#include <SDL3/SDL_video.h>
#include <memory>

namespace penguin::core::window {

	struct Window::WindowImpl {
		// Window variables
		std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> window;
		String title;
		Vector2i size;
		Vector2i min_size;
		Vector2i max_size;

		// Flags
		bool resizable;
		bool hidden;
		bool minimized;
		bool maximized;
		bool bordered;
		bool fullscreen;
		bool mouse_grabbed;
		bool always_on_top;
		bool focused;
		bool open = true;

		// Constructors
		WindowImpl(const char* p_title, Vector2i p_size, WindowFlags p_flags);

		// Move constructor & assignment destructors

		WindowImpl(const WindowImpl&) = delete;
		WindowImpl& operator=(const WindowImpl&) = delete;
		WindowImpl(WindowImpl&&) noexcept = default;
		WindowImpl& operator=(WindowImpl&&) noexcept = default;

		// Functions to change window title / sizes

		bool set_title(const char* new_title);
		bool set_max_size(Vector2i p_max_size);
		bool set_min_size(Vector2i p_min_size);
		bool resize(Vector2i new_size);

		bool show();
		bool hide();
		bool minimize();
		bool maximize();
		bool restore(); // used to restore a minimized / maximized window. Has no effect on a fullscreen window.
		bool restore_async();

		// Functions to toggle window states

		bool enable_resizing();
		bool disable_resizing();

		bool enable_borders();
		bool disable_borders();

		bool enter_fullscreen();
		bool exit_fullscreen();

		bool grab_mouse();
		bool release_mouse();

		bool add_always_on_top();
		bool remove_always_on_top();

		bool gain_focus();
		bool lose_foucs();

		void set_flags(WindowFlags& flags);
	};
}

