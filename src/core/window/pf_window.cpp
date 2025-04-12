#include "core/window/pf_window.hpp"

using pf::core::PF_Window;
using pf::core::PF_WindowFlags;
using pf::core::PF_WindowVSyncFlags;
using pf::common::PF_Error;
using pf::events::PF_WindowEvent;
using pf::events::PF_WindowEventIndex;

PF_Window::PF_Window(const char* p_title, Vector2i p_size, PF_WindowFlags p_flags)
	: window(SDL_CreateWindow(p_title, p_size.x, p_size.y, p_flags)), title(p_title)	{

	Exception::throw_if(
		!window,
		SDL_GetError(),
		PF_Error::Window
	);

	size = p_size;
	min_size = p_size;
	max_size = p_size;

	set_flags(flags);
}

SDL_Window* PF_Window::get_window() {
	return window.get();
}

void PF_Window::set_title(const char* new_title) {
	title = new_title;

	Exception::throw_if(
		!SDL_SetWindowTitle(title.c_str()),
		SDL_GetError(),
		PF_Error::Window
	);
}

void PF_Window::set_max_size(Vector2i p_max_size) {
	max_size = p_max_size;

	Exception::throw_if(
		!SDL_SetWindowMaximumSize(window.get(), &max_size.x, &max_size.y),
		SDL_GetError(),
		PF_Error::Window
	);
}

void PF_Window::set_min_size(Vector2i p_min_size) {
	min_size = p_min_size;

	Exception::throw_if(
		!SDL_SetWindowMinimumSize(window.get(), &min_size.x, &min_size.y),
		SDL_GetError(),
		PF_Error::Window
	);
}

void PF_Window::resize(Vector2i new_size) {
	size = new_size;

	Exception::throw_if(
		!SDL_SetWindowSize(window.get(), &size.x, &size.y),
		SDL_GetError(),
		PF_Error::Window
	);
}

void PF_Window::show() {
	if (hidden) {
		hidden = false;
		
		Exception::throw_if(
			!SDL_ShowWindow(window.get()),
			SDL_GetError(),
			PF_Error::Window
		);
	}
}

void PF_Window::hide() {
	if (!hidden) {
		hidden = true;

		Exception::throw_if(
			!SDL_ShowWindow(window.get()),
			SDL_GetError(),
			PF_Error::Window
		);
	}
}

void PF_Window::minimize() {
	if (resizable && !minimized) {
		minimized = true;
		maximized = false; // Ensures the window isn't also marked as "maximized"

		Exception::throw_if(
			!SDL_MinimizeWindow(window.get()),
			SDL_GetError(),
			PF_Error::Window
		);
	}
}

// ONLY WORKS IF is_resizable is true
void PF_Window::maximize() {
	if (resizable && !maximized) {
		maximized = true;
		minimized = false; // Ensures the window isn't also marked as "minimized"

		Exception::throw_if(
			!SDL_MaximizeWindow(window.get()),
			SDL_GetError(),
			PF_Error::Window
		);
	}
}

void PF_Window::restore() {
	if (resizable) {

		Exception::throw_if(
			!SDL_RestoreWindow(window.get()),
			SDL_GetError(),
			PF_Error::Window
		);

		Exception::throw_if(
			!SDL_SyncWindow(window.get()),
			SDL_GetError(),
			PF_Error::Window
		);
	}
}

void PF_Window::restore_async() {
	if (resizable) {

		Exception::throw_if(
			!SDL_RestoreWindow(window.get()),
			SDL_GetError(),
			PF_Error::Window
		);
	}
}

void PF_Window::enable_resizing() {
	resizable = true;

	Exception::throw_if(
		!SDL_SetWindowResizable(window.get(), resizable),
		SDL_GetError(),
		PF_Error::Window
	);
}

void PF_Window::disable_resizing() {
	resizable = false;

	Exception::throw_if(
		!SDL_SetWindowResizable(window.get(), resizable),
		SDL_GetError(),
		PF_Error::Window
	);
}

void PF_Window::enable_borders() {
	bordered = true;

	Exception::throw_if(
		!SDL_SetWindowBordered(window.get(), bordered),
		SDL_GetError(),
		PF_Error::Window
	);
}
void PF_Window::disable_borders() {
	bordered = false;

	Exception::throw_if(
		!SDL_SetWindowBordered(window.get(), bordered),
		SDL_GetError(),
		PF_Error::Window
	);
}

void PF_Window::enter_fullscreen() {
	fullscreen = true;

	Exception::throw_if(
		!SDL_SetWindowFullscreen(window.get(), fullscreen),
		SDL_GetError(),
		PF_Error::Window
	);
}

void PF_Window::exit_fullscreen() {
	fullscreen = false;

	Exception::throw_if(
		!SDL_SetWindowFullscreen(window.get(), fullscreen),
		SDL_GetError(),
		PF_Error::Window
	);
}

void PF_Window::enable_vsync() {
	vsync_enabled = true;

	Exception::throw_if(
		!SDL_SetWindowSurfaceVSync(window.get(), PF_WindowVSyncFlags::VSync_Adaptive),
		SDL_GetError(),
		PF_Error::Window
	);
}

void PF_Window::disable_vsync() {
	vsync_enabled = false;

	Exception::throw_if(
		!SDL_SetWindowSurfaceVSync(window.get(), PF_WindowVSyncFlags::VSync_Disabled),
		SDL_GetError(),
		PF_Error::Window
	);
}

void PF_Window::grab_mouse() {
	mouse_grabbed = true;

	Exception::throw_if(
		!SDL_SetWindowMouseGrab(window.get(), mouse_grabbed),
		SDL_GetError(),
		PF_Error::Window
	);
}

void PF_Window::release_mouse() {
	mouse_grabbed = false;

	Exception::throw_if(
		!SDL_SetWindowMouseGrab(window.get(), mouse_grabbed),
		SDL_GetError(),
		PF_Error::Window
	);
}

void PF_Window::always_on_top() {
	always_on_top = true;

	Exception::throw_if(
		!SDL_SetWindowAlwaysOnTop(window.get(), always_on_top),
		SDL_GetError(),
		PF_Error::Window
	);
}

void PF_Window::remove_always_on_top() {
	always_on_top = false;

	Exception::throw_if(
		!SDL_SetWindowAlwaysOnTop(window.get(), always_on_top),
		SDL_GetError(),
		PF_Error::Window
	);
}

void PF_Window::gain_focus() {
	focused = true;

	Exception::throw_if(
		!SDL_SetWindowFocusable(window.get(), focused),
		SDL_GetError(),
		PF_Error::Window
	);
}

void PF_Window::lose_foucs() {
	focused = false;

	Exception::throw_if(
		!SDL_SetWindowFocusable(window.get(), focused),
		SDL_GetError(),
		PF_Error::Window
	);
}

void PF_Window::set_flags(PF_WindowFlags& flags) {
	resizable = has_flag(flags, PF_WindowFlags::Resizable);
	hidden = has_flag(flags, PF_WindowFlags::Hidden);
	minimized = has_flag(flags, PF_WindowFlags::Maximized);
	maximized = has_flag(flags, PF_WindowFlags::Minimized);
	bordered = !(has_flag(flags, PF_WindowFlags::Borderless)); // If the borderless flag is set, we need to set bordered to be false
	fullscreen = has_flag(flags, PF_WindowFlags::Fullscreen);
	mouse_grabbed = has_flag(flags, PF_WindowFlags::MouseGrabbed);
	always_on_top = has_flag(flags, PF_WindowFlags::AlwaysOnTop);
	focused = has_flag(flags, PF_WindowFlags::InputFocus) || has_flag(flags, PF_WindowFlags::MouseFocus);
}
