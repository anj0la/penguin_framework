#pragma once

#include <penguin_framework/core/common/native_types.hpp>

#include <penguin_framework/core/rendering/primitives/penguin_sprite.hpp>

#include <penguin_framework/utils/exception.hpp>
#include <penguin_framework/core/math/rect2.hpp>
#include <penguin_framework/core/math/circle2.hpp>
#include <penguin_framework/core/math/colours.hpp>
#include <penguin_framework/core/math/vector2i.hpp>

#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_rect.h>

#include <memory>
#include <vector>

namespace penguin::core::rendering {

	enum class RendererVSyncFlags : int {
		VSync_Adaptive = -1,
		VSync_Disabled
	};

	struct RendererImpl {
		std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> renderer;
		bool vsync_enabled = false; // disabled by default

		// Constructor
		RendererImpl(NativeWindowPtr window, const char* driver_name);

		// Move constructor & assignment destructors (copy constructor / assignment not allowed)

		RendererImpl(const RendererImpl&) = delete;
		RendererImpl& operator=(const RendererImpl&) = delete;
		RendererImpl(RendererImpl&&) noexcept = default;
		RendererImpl& operator=(RendererImpl&&) noexcept = default;

		// Displaying / clearing the renderer

		bool display();
		bool clear();
		bool set_colour(Colour colour);

		// VSync functions

		bool enable_vsync();
		bool disable_vsync();
		bool is_vsync_enabled() const;

		// Drawing functions

		bool draw_line(Vector2 vec1, Vector2 vec2, Colour colour = Colours::White);
		bool draw_pixel(Vector2 vec, Colour colour = Colours::White);
		bool draw_rect(Rect2 rect, Colour outline = Colours::White);
		bool draw_filled_rect(Rect2 rect, Colour fill = Colours::White);
		bool draw_triangle(Vector2 vec1, Vector2 vec2, Vector2 vec3, Colour outline = Colours::White);
		bool draw_filled_triangle(Vector2 vec1, Vector2 vec2, Vector2 vec3, Colour fill = Colours::White);
		bool draw_circle(Vector2 center, int rad, Colour outline = Colours::White);
		bool draw_filled_circle(Vector2 center, int radius, Colour fill = Colours::White);
		bool draw_ellipse(Vector2 center, int radius_x, int radius_y, Colour outline = Colours::White);
		bool draw_filled_ellipse(Vector2 center, int radius_x, int radius_y, Colour fill = Colours::White);

		// Drawing functions for Sprites

		bool draw_sprite(primitives::Sprite spr, Rect2 source, Rect2 dest);
		bool draw_sprite(primitives::Sprite spr, Rect2 source);
		bool draw_sprite(primitives::Sprite spr, Rect2 dest);
		bool draw_sprite(primitives::Sprite spr);

		bool draw_sprite_rotated(primitives::Sprite spr, Rect2 source, Rect2 dest);
		bool draw_sprite_rotated(primitives::Sprite spr, Rect2 source);
		bool draw_sprite_rotated(primitives::Sprite spr, Rect2 dest);
		bool draw_sprite_rotated(primitives::Sprite spr);

		bool draw_sprite_scaled(primitives::Sprite spr, Rect2 source, Rect2 dest);
		bool draw_sprite_scaled(primitives::Sprite spr, Rect2 source);
		bool draw_sprite_scaled(primitives::Sprite spr, Rect2 dest);
		bool draw_sprite_scaled(primitives::Sprite spr);

		// Additional functions for Sprites

		bool modulate_sprite(primitives::Sprite spr, Colour colour = Colours::Transparent);

		// Helper functions

		bool draw_horizontal_line(float x1, float x2, float y, Colour colour);
	};
}