#include <window/internal/penguin_window_impl.hpp>

namespace penguin::internal::window {

	WindowImpl::WindowImpl(const char* p_title, penguin::math::Vector2i p_size, penguin::window::WindowFlags p_flags)
		: window(SDL_CreateWindow(p_title, p_size.x, p_size.y, static_cast<SDL_WindowFlags>(p_flags)), &SDL_DestroyWindow), title(p_title) {

		penguin::internal::error::InternalError::throw_if(
			!window,
			"Failed to create the window.",
			penguin::internal::error::ErrorCode::Window_Creation_Failed
		);

		title = p_title;
		size = p_size;
		min_size = p_size;
		max_size = p_size;

		set_flags(p_flags);

		open = true; // The window is valid and is now in an "open" state
	}

	bool WindowImpl::set_title(const char* new_title) {
		title = new_title;
		return SDL_SetWindowTitle(window.get(), title.c_str());
	}

	bool WindowImpl::set_max_size(penguin::math::Vector2i p_max_size) {
		if (p_max_size.x <= 0 || p_max_size.y <= 0) return false; // the vector's x and y coordinates must be a positive integer
		max_size = p_max_size;
		return SDL_SetWindowMaximumSize(window.get(), max_size.x, max_size.y);
	}
	bool WindowImpl::set_min_size(penguin::math::Vector2i p_min_size) {
		if (p_min_size.x <= 0 || p_min_size.y <= 0) return false; // the vector's x and y coordinates must be a positive integer
		min_size = p_min_size;
		return SDL_SetWindowMinimumSize(window.get(), min_size.x, min_size.y);
	}
	bool WindowImpl::resize(penguin::math::Vector2i new_size) {
		if (new_size.x <= 0 || new_size.y <= 0) return false; // the vector's x and y coordinates must be greater than 0
		size = new_size;
		return SDL_SetWindowSize(window.get(), size.x, size.y);
	}

	bool WindowImpl::show() {
		if (hidden) {
			hidden = false;
			return SDL_ShowWindow(window.get());
		}
		return true; // indicates that no error occured (hidden is already false, indicating the window is already visible)
	}

	bool WindowImpl::hide() {
		if (!hidden) {
			hidden = true;
			return SDL_HideWindow(window.get());
		}
		return true; // indicates that no error occured (hidden is already true, indicating the window is already invisible)
	}

	bool WindowImpl::minimize() {
		if (resizable && !minimized) {
			minimized = true;
			maximized = false; // Ensures the window isn't also marked as "maximized"
			return SDL_MinimizeWindow(window.get()) && SDL_SyncWindow(window.get());
		}
		return true; // if the window is already minimized OR not resizable, we still mark as true as it ran without error
	}

	bool WindowImpl::minimize_async() {
		if (resizable && !minimized) {
			minimized = true;
			maximized = false; // Ensures the window isn't also marked as "maximized"
			return SDL_MinimizeWindow(window.get());
		}
		return true; // if the window is already minimized OR not resizable, we still mark as true as it ran without error
	}

	bool WindowImpl::maximize() {
		if (resizable && !maximized) {
			maximized = true;
			minimized = false; // Ensures the window isn't also marked as "minimized"

			return SDL_MaximizeWindow(window.get()) && SDL_SyncWindow(window.get());
		}
		return true; // if the window is already minimized OR not resizable, we still mark as true as it ran without error
	}

	bool WindowImpl::maximize_async() {
		if (resizable && !maximized) {
			maximized = true;
			minimized = false; // Ensures the window isn't also marked as "minimized"

			return SDL_MaximizeWindow(window.get());
		}
		return true; // if the window is already minimized OR not resizable, we still mark as true as it ran without error
	}

	bool WindowImpl::restore() {
		if (resizable) {
			maximized = false; // both flags should be false
			minimized = false;

			return SDL_RestoreWindow(window.get()) && SDL_SyncWindow(window.get());
		}
		return true; // no error occurs if not resizable

	}
	bool WindowImpl::restore_async() {
		if (resizable) {
			maximized = false; // both flags should be false
			minimized = false;

			return SDL_RestoreWindow(window.get());
		}
		return true; // no error occurs if not resizable
	}

	// Functions to toggle window states

	bool WindowImpl::enable_resizing() {
		resizable = true;
		return SDL_SetWindowResizable(window.get(), resizable);
	}

	bool WindowImpl::disable_resizing() {
		resizable = false;
		return SDL_SetWindowResizable(window.get(), resizable);
	}

	bool WindowImpl::enable_borders() {
		bordered = true;
		return SDL_SetWindowBordered(window.get(), bordered);
	}

	bool WindowImpl::disable_borders() {
		bordered = false;
		return SDL_SetWindowBordered(window.get(), bordered);
	}

	bool WindowImpl::enter_fullscreen() {
		fullscreen = true;
		return SDL_SetWindowFullscreen(window.get(), fullscreen);
	}

	bool WindowImpl::exit_fullscreen() {
		fullscreen = false;
		return SDL_SetWindowFullscreen(window.get(), fullscreen);
	}

	bool WindowImpl::grab_mouse() {
		mouse_grabbed = true;
		return SDL_SetWindowMouseGrab(window.get(), mouse_grabbed);
	}

	bool WindowImpl::release_mouse() {
		mouse_grabbed = false;
		return SDL_SetWindowMouseGrab(window.get(), mouse_grabbed);
	}

	bool WindowImpl::add_always_on_top() {
		always_on_top = true;
		return SDL_SetWindowAlwaysOnTop(window.get(), always_on_top);
	}

	bool WindowImpl::remove_always_on_top() {
		always_on_top = false;
		return SDL_SetWindowAlwaysOnTop(window.get(), always_on_top);
	}

	bool WindowImpl::gain_focus() {
		focused = true;
		return SDL_SetWindowFocusable(window.get(), focused);
	}

	bool WindowImpl::lose_foucs() {
		focused = false;
		return SDL_SetWindowFocusable(window.get(), focused);
	}

	void WindowImpl::set_flags(penguin::window::WindowFlags& flags) {
		resizable = has_flag(flags, penguin::window::WindowFlags::Resizable);
		hidden = has_flag(flags, penguin::window::WindowFlags::Hidden);
		minimized = has_flag(flags, penguin::window::WindowFlags::Minimized);
		maximized = has_flag(flags, penguin::window::WindowFlags::Maximized);
		bordered = !(has_flag(flags, penguin::window::WindowFlags::Borderless)); // If the borderless flag is set, we need to set bordered to be false
		fullscreen = has_flag(flags, penguin::window::WindowFlags::Fullscreen);
		mouse_grabbed = has_flag(flags, penguin::window::WindowFlags::MouseGrabbed);
		always_on_top = has_flag(flags, penguin::window::WindowFlags::AlwaysOnTop);
		focused = has_flag(flags, penguin::window::WindowFlags::InputFocus) || has_flag(flags, penguin::window::WindowFlags::MouseFocus);
	}
}