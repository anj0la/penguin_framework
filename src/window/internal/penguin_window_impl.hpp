#pragma once

#include <penguin_framework/window/penguin_windowflags.hpp>
#include <error/internal/internal_error.hpp>
#include <penguin_framework/math/Vector2i.hpp>
#include <penguin_framework/utils/string.hpp>

#include <SDL3/SDL_video.h>

#include <memory>
#include <string>
#include <stdexcept>


namespace penguin::internal::window {

	class WindowImpl {
	public:
		std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> window;
		std::string title;
		penguin::math::Vector2i size;
		penguin::math::Vector2i min_size;
		penguin::math::Vector2i max_size;

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
		bool open = false;

		// Constructors
		WindowImpl(const char* p_title, penguin::math::Vector2i p_size, penguin::window::WindowFlags p_flags);

		// Move constructor & assignment destructors

		WindowImpl(const WindowImpl&) = delete;
		WindowImpl& operator=(const WindowImpl&) = delete;
		WindowImpl(WindowImpl&&) noexcept = default;
		WindowImpl& operator=(WindowImpl&&) noexcept = default;

		// Functions to change window title / sizes

		bool set_title(const char* new_title);
		bool set_max_size(penguin::math::Vector2i p_max_size);
		bool set_min_size(penguin::math::Vector2i p_min_size);
		bool resize(penguin::math::Vector2i new_size);

		bool show();
		bool hide();
		bool minimize();
		bool minimize_async();
		bool maximize();
		bool maximize_async();
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

	private:
		void set_flags(penguin::window::WindowFlags& flags);
	};
}

