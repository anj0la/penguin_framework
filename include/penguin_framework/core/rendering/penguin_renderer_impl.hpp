#pragma once

#include <penguin_framework/utils/exception.hpp>
#include <penguin_framework/core/math/rect2.hpp>
#include <penguin_framework/core/math/circle2.hpp>
#include <penguin_framework/core/math/colours.hpp>

#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_rect.h>

#include <memory>
#include <vector>

namespace penguin::core::rendering {

	struct Renderer::RendererImpl {
		std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> renderer;

		// Constructor
		RendererImpl(SDL_Window* window, const char* driver_name);

		// Move constructor & assignment destructors (copy constructor / assignment not allowed)

		Renderer(const RendererImpl&) = delete;
		RendererImpl& operator=(const RendererImpl&) = delete;
		RendererImpl(RendererImpl&&) noexcept = default;
		RendererImpl& operator=(RendererImpl&&) noexcept = default;

		// Displaying / clearing the renderer

		bool display();
		bool clear();

		// Drawing functions

		bool draw_line(Vector2 vec1, Vector2 vec2, Colour colour = Colours::White);
		bool draw_pixel(Vector2 vec, Colour colour = Colours::White);
		bool draw_rect(Rect2 rect, Colour outline = Colours::White);
		bool draw_filled_rect(Rect2 rect, Colour fill = Colours::White);
		bool draw_triange(Vector2 vec1, Vector2 vec2, Vector2 vec3, Colour outline = Colours::White);
		bool draw_filled_triange(Vector2 vec1, Vector2 vec2, Vector2 vec3, Colour fill = Colours::White);
		bool draw_circle(Vector2 center, int rad, Colour outline = Colours::White);
		bool draw_circle(Circle2 circle, Colour outline = Colours::White);
		bool draw_filled_circle(Vector2 center, int radius, Colour fill = Colours::White);
		bool draw_filled_circle(Circle2 circle, Colour fill = Colours::White);
		bool draw_ellipse(Vector2 center, int radius_x, int radius_y, Colour outline = Colours::White);
		bool draw_filled_ellipse(Vector2 center, int radius_x, int radius_y, Colour fill = Colours::White);
	};
}