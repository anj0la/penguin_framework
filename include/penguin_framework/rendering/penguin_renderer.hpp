#pragma once

#include <penguin_framework/penguin_api.hpp>

#include <penguin_framework/common/native_types.hpp>
#include <penguin_framework/window/penguin_window.hpp>
#include <penguin_framework/rendering/primitives/penguin_sprite.hpp>
#include <penguin_framework/math/rect2.hpp>
#include <penguin_framework/math/vector2.hpp>
#include <penguin_framework/math/circle2.hpp>
#include <penguin_framework/math/colours.hpp>

#include <memory>

namespace penguin::internal::rendering {
	// Forward declaration
	class RendererImpl;
}

namespace penguin::rendering {

	class PENGUIN_API Renderer {
	public:
		Renderer(NativeWindowPtr window_ptr, const char* driver_name = "");
		~Renderer();

		// Move semantics

		Renderer(const Renderer&) = default;
		Renderer& operator=(const Renderer&) = default;

		// Validity checking

		[[nodiscard]] bool is_valid() const noexcept;
		[[nodiscard]] explicit operator bool() const noexcept;

		// Displaying / clearing the renderer

		void display();
		void clear();

		// Drawing functions

		void draw_line(penguin::math::Vector2 vec1, penguin::math::Vector2 vec2, penguin::math::Colour colour = Colours::White);
		void draw_pixel(penguin::math::Vector2 vec, penguin::math::Colour colour = Colours::White);
		void draw_rect(penguin::math::Rect2 rect, penguin::math::Colour outline = Colours::White);
		void draw_filled_rect(penguin::math::Rect2 rect, penguin::math::Colour fill = Colours::White);
		void draw_triangle(penguin::math::Vector2 vec1, penguin::math::Vector2 vec2, penguin::math::Vector2 vec3, penguin::math::Colour outline = Colours::White);
		void draw_filled_triangle(penguin::math::Vector2 vec1, penguin::math::Vector2 vec2, penguin::math::Vector2 vec3, penguin::math::Colour fill = Colours::White);
		void draw_circle(penguin::math::Circle2 circle, penguin::math::Colour outline = Colours::White);
		void draw_circle(penguin::math::Vector2 center, int radius, penguin::math::Colour outline = Colours::White);
		void draw_filled_circle(penguin::math::Circle2 circle, penguin::math::Colour fill = Colours::White);
		void draw_filled_circle(penguin::math::Vector2 center, int radius, penguin::math::Colour fill = Colours::White);
		void draw_ellipse(penguin::math::Vector2 center, int radius_x, int radius_y, penguin::math::Colour outline = Colours::White);
		void draw_filled_ellipse(penguin::math::Vector2 center, int radius_x, int radius_y, penguin::math::Colour fill = Colours::White);

		// Drawing functions for Sprites

		void draw_sprite(penguin::rendering::primitives::Sprite& spr);
		void draw_sprite_transformed(penguin::rendering::primitives::Sprite spr);

		NativeRendererPtr get_native_ptr() const;

	private:
		std::unique_ptr<penguin::internal::rendering::RendererImpl> pimpl_;
	};
}