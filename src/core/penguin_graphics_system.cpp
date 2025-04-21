#include <penguin_framework/core/system/penguin_graphics_system.hpp>
#include <penguin_framework/core/window/penguin_window.hpp>
#include <SDL3/SDL_init.h>

using penguin::core::system::GraphicsSystem;
using penguin::core::window::Window;
using penguin::core::window::WindowFlags;

GraphicsSystem::GraphicsSystem() {
	SDL_InitSubSystem(SDL_INIT_VIDEO);
}

GraphicsSystem::~GraphicsSystem() {
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

std::unique_ptr<Window> GraphicsSystem::create_window(const char* p_title = "", Vector2i p_size = Vector2i(640, 480), WindowFlags p_flags = WindowFlags::None) {
	return std::make_unique<Window>(p_title, p_size, p_flags);
}
