#pragma once

#include <penguin_framework/core/window/penguin_windowflags.hpp>
#include <penguin_framework/core/math/vector2i.hpp>
#include <penguin_framework/utils/string.hpp>

#include <memory>

namespace penguin::core::system {

	class GraphicsSystem {
		GraphicsSystem();
		~GraphicsSystem(); // quit SDL video subsystem with SDL_QuitSubsystem(SDL_VIDEO_INIT); -> will still call SQL_Quit when app is done

		std::unique_ptr<penguin::core::window::Window> create_window(const char* p_title = "", Vector2i p_size = Vector2i(640, 480), penguin::core::window::WindowFlags p_flags = penguin::core::window::WindowFlags::None);
		// std::unique_ptr<penguin::core::rendering::Renderer> create_renderer(penguin::core::window::Window::Window& window);
		// std::unique_ptr<penguin::core::rendering::Sprite> create_sprite(penguin::core::rendering::Renderer& renderer, const char* path);
		// std::unique_ptr<penguin::core::rendering::Text> create_text(penguin::core::rendering::Renderer& renderer, const char* path);
		
		// Prevent copying/moving
		GraphicsSystem(const GraphicsSystem&) = delete;
		GraphicsSystem& operator=(const GraphicsSystem&) = delete;
	};
}