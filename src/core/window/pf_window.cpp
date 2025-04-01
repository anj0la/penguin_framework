#include "core/window/pf_window.hpp"

using pf::PF_Window;
using pf::PF_WindowFlags;
using pf::PF_Error;

PenguinWindow::PenguinWindow(const std::string& title, Vector2<int> size, SDL_WindowFlags p_flags)
	: window(SDL_CreateWindow(title.c_str(), size.x, size.y, p_flags), &SDL_DestroyWindow) {

	Exception::throw_if(!window, "The window could not be initalized.", WINDOW_ERROR);
}

PF_Window::PF_Window(const char* p_title, Vector2i p_size, PF_WindowFlags p_flags)
	: window(SDL_CreateWindow(p_title, p_size.x, p_size.y, p_flags)) {

	Exception::throw_if(
		!window,
		PF_Error::Window,
		SDL_GetError()
	)

	width = p_size.x;
	height = p_size.y;
}

