#pragma once

#include <penguin_framework/common/native_types.hpp>

#include <penguin_framework/rendering/primitives/sprite.hpp>

#include <penguin_framework/math/rect2.hpp>
#include <penguin_framework/math/circle2.hpp>
#include <penguin_framework/math/colours.hpp>
#include <penguin_framework/math/vector2i.hpp>

#include <error/internal/internal_error.hpp>

#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_rect.h>

#include <memory>
#include <vector>
#include <string>

namespace penguin::internal::rendering {

	enum class RendererVSyncFlags : int {
		VSync_Adaptive = -1,
		VSync_Disabled
	};

	class RendererImpl {
	public:
		std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> renderer;
		bool vsync_enabled = false; // disabled by default

		// Constructor

		RendererImpl(NativeWindowPtr window, std::string driver_name);

		// Move constructor & assignment destructors

		RendererImpl(const RendererImpl&) = delete;
		RendererImpl& operator=(const RendererImpl&) = delete;
		RendererImpl(RendererImpl&&) noexcept = default;
		RendererImpl& operator=(RendererImpl&&) noexcept = default;

		// Displaying / clearing the renderer

		bool display();
		bool clear();
		bool set_colour(penguin::math::Colour colour);

		// VSync functions

		bool enable_vsync();
		bool disable_vsync();
		bool is_vsync_enabled() const;

		// Drawing functions

		bool draw_line(penguin::math::Vector2 vec1, penguin::math::Vector2 vec2, penguin::math::Colour colour = Colours::White);
		bool draw_pixel(penguin::math::Vector2 vec, penguin::math::Colour colour = Colours::White);
		bool draw_rect(penguin::math::Rect2 rect, penguin::math::Colour outline = Colours::White);
		bool draw_filled_rect(penguin::math::Rect2 rect, penguin::math::Colour fill = Colours::White);
		bool draw_triangle(penguin::math::Vector2 vec1, penguin::math::Vector2 vec2, penguin::math::Vector2 vec3, penguin::math::Colour outline = Colours::White);
		bool draw_filled_triangle(penguin::math::Vector2 vec1, penguin::math::Vector2 vec2, penguin::math::Vector2 vec3, penguin::math::Colour fill = Colours::White);
		bool draw_circle(penguin::math::Vector2 center, int rad, penguin::math::Colour outline = Colours::White);
		bool draw_filled_circle(penguin::math::Vector2 center, int radius, penguin::math::Colour fill = Colours::White);
		bool draw_ellipse(penguin::math::Vector2 center, int radius_x, int radius_y, penguin::math::Colour outline = Colours::White);
		bool draw_filled_ellipse(penguin::math::Vector2 center, int radius_x, int radius_y, penguin::math::Colour fill = Colours::White);

		// Drawing functions for Sprites

		bool draw_sprite(NativeTexturePtr spr_texture, const penguin::math::Rect2& texture_region, const penguin::math::Rect2& screen_placement);
		bool draw_sprite_transformed(NativeTexturePtr spr_texture, const penguin::math::Rect2& texture_region, const penguin::math::Rect2& screen_placement,
			const penguin::math::Vector2& scale_factor, const penguin::math::Vector2& normalized_anchor, float angle, penguin::rendering::primitives::FlipMode mode);

	private:
		bool draw_horizontal_line(float x1, float x2, float y, penguin::math::Colour colour);
	};
}