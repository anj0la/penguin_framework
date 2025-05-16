#pragma once

#include <penguin_framework/penguin_api.hpp>

#include <penguin_framework/core/common/native_types.hpp>
#include <penguin_framework/core/window/penguin_window.hpp>
#include <penguin_framework/core/math/rect2.hpp>
#include <penguin_framework/core/math/circle2.hpp>
#include <penguin_framework/core/math/colours.hpp>

#include <memory>

namespace penguin::core::rendering {

	// Forward declaration
	struct RendererImpl;

	class PENGUIN_API Renderer {
	public:
		Renderer(window::Window& window, const char* driver_name = "");
		~Renderer();

		// Deleting move semantics

		Renderer(const Renderer&) = delete;
		Renderer& operator=(const Renderer&) = delete;

		// Displaying / clearing the renderer

		bool display();
		bool clear();

		// Drawing functions

		bool draw_line(Vector2 vec1, Vector2 vec2, Colour colour = Colours::White);
		bool draw_pixel(Vector2 vec, Colour colour = Colours::White);
		bool draw_rect(Rect2 rect, Colour outline = Colours::White);
		bool draw_filled_rect(Rect2 rect, Colour fill = Colours::White);
		bool draw_triangle(Vector2 vec1, Vector2 vec2, Vector2 vec3, Colour outline = Colours::White);
		bool draw_filled_triangle(Vector2 vec1, Vector2 vec2, Vector2 vec3, Colour fill = Colours::White);
		bool draw_circle(Vector2 center, int rad, Colour outline = Colours::White);
		bool draw_circle(Circle2 circle, Colour outline = Colours::White);
		bool draw_filled_circle(Vector2 center, int radius, Colour fill = Colours::White);
		bool draw_filled_circle(Circle2 circle, Colour fill = Colours::White);
		bool draw_ellipse(Vector2 center, int radius_x, int radius_y, Colour outline = Colours::White);
		bool draw_filled_ellipse(Vector2 center, int radius_x, int radius_y, Colour fill = Colours::White);

		// Drawing sprites
		//bool draw_sprite(Sprite spr);
		//bool draw_sprite(Sprite spr, Rect2 source);
		//bool draw_sprite(Sprite spr, Rect2 dest);
		//bool draw_sprite(Sprite str, Rect2 source, Rect2 dest);

		NativeRendererPtr get_native_ptr() const;

	private:
		std::unique_ptr<RendererImpl> pimpl_;
	};
}