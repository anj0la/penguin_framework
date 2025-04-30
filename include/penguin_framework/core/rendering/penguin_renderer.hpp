#pragma once

#include <penguin_framework/core/window/penguin_window.hpp>
#include <penguin_framework/core/math/rect2.hpp>
#include <penguin_framework/core/math/circle2.hpp>
#include <penguin_framework/core/math/colours.hpp>
#include <penguin_framework/utils/string.hpp>

#include <memory>
#include <vector>

// Forward declaration of GraphicsSystem
namespace penguin::core::system {
	class GraphicsSystem;
}

namespace penguin::core::rendering {

	class PENGUIN_API Renderer {
	public:
		explicit Renderer(window::Window& window, const char* driver_name = "");

		// Move constructor & assignment destructors (copy constructor / assignment not allowed)

		Renderer(const Renderer&) = delete;
		Renderer& operator=(const Renderer&) = delete;
		Renderer(Renderer&&) noexcept = default;
		Renderer& operator=(Renderer&&) noexcept = default;

		// Displaying / clearing the renderer

		void display();
		void clear();

		// Drawing functions

		void draw_line(Vector2 x, Vector2 y, Colour colour = Colours::White);
		void draw_pixel(Vector2 vect, Colour colour = Colours::White);
		void draw_rect(Rect2 rect, Colour outline = Colours::White);
		void draw_filled_rect(Rect2 rect, Colour fill = Colours::White);
		void draw_triange(Vector2 x, Vector2 y, Vector2 z, Colour fill = Colours::White);
		void draw_filled_triange(Vector2 x, Vector2 y, Vector2 z, Colour fill = Colours::White);
		void draw_circle(Circle2 circle, Colour outline = Colours::White);
		void draw_circle(Vector2 center, int rad, Colour outline = Colours::White);
		void draw_filled_circle(Vector2 center, int radius, Colour fill = Colours::White);
		void draw_filled_circle(Circle2 circle, Colour fill = Colours::White);
		void draw_ellipse(Vector2 center, int radius_x, int radius_y, Colour outline = Colours::White);
		void draw_filled_ellipse(Vector2 center, int radius_x, int radius_y, Colour fill = Colours::White);

		// Rendering functions (to be implemented in the future)
		// draw_sprite(Sprite spr, Vector2 pos);
		// draw_text(Text txt, Vector2 pos);

	private:
		// Forward declaration
		struct RendererImpl;

		// Gives access to internal implementation (needed to create sprite and text)
		friend class GraphicsSystem;

		std::unique_ptr<RendererImpl> pimpl_;

		// PUT INSIDE THE pimpl_
		void set_colour(Colour colour);
		void reset_colour();


	};
}