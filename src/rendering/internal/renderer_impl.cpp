#include <rendering/internal/renderer_impl.hpp>
#include <SDL3_ttf/SDL_ttf.h>

namespace penguin::internal::rendering {

	RendererImpl::RendererImpl(NativeWindowPtr window, std::string driver_name)
		: renderer(SDL_CreateRenderer(
			window.as<SDL_Window>(),
			driver_name.empty() ? NULL : driver_name.c_str()), // If empty, allow SDL to handle getting the driver.
			&SDL_DestroyRenderer) {

		// Throw an exception if the renderer was not intialized.
		penguin::internal::error::InternalError::throw_if(
			!renderer,
			"Failed to create the renderer.",
			penguin::internal::error::ErrorCode::Renderer_Creation_Failed
		);
	}

	// Displaying / clearing the renderer

	bool RendererImpl::display() {
		return SDL_RenderPresent(renderer.get());
	}

	bool RendererImpl::set_colour(penguin::math::Colour colour) {
		return SDL_SetRenderDrawColorFloat(renderer.get(), colour.r, colour.g, colour.b, colour.a);
	}

	bool RendererImpl::clear() {
		return set_colour(Colours::Black) && SDL_RenderClear(renderer.get());
	}

	// VSync functions

	bool RendererImpl::enable_vsync() {
		vsync_enabled = true;
		return SDL_SetRenderVSync(renderer.get(), static_cast<int>(RendererVSyncFlags::VSync_Adaptive));
	}

	bool RendererImpl::disable_vsync() {
		vsync_enabled = false;
		return SDL_SetRenderVSync(renderer.get(), static_cast<int>(RendererVSyncFlags::VSync_Disabled));
	}

	bool RendererImpl::is_vsync_enabled() const {
		return vsync_enabled;
	}

	// Drawing functions

	bool RendererImpl::draw_line(penguin::math::Vector2 vec1, penguin::math::Vector2 vec2, penguin::math::Colour colour) {
		return set_colour(colour) && SDL_RenderLine(renderer.get(), vec1.x, vec1.y, vec2.x, vec2.y);
	}

	bool RendererImpl::draw_pixel(penguin::math::Vector2 vec, penguin::math::Colour colour) {
		return set_colour(colour) && SDL_RenderPoint(renderer.get(), vec.x, vec.y);
	}

	bool RendererImpl::draw_rect(penguin::math::Rect2 rect, penguin::math::Colour outline) {
		bool colour_applied = set_colour(outline);
		SDL_FRect frect = { rect.position.x, rect.position.y, rect.size.x, rect.size.y };
		return colour_applied && SDL_RenderRect(renderer.get(), &frect);
	}

	bool RendererImpl::draw_filled_rect(penguin::math::Rect2 rect, penguin::math::Colour fill) {
		bool colour_applied = set_colour(fill);
		SDL_FRect frect = { rect.position.x, rect.position.y, rect.size.x, rect.size.y };
		return colour_applied && SDL_RenderFillRect(renderer.get(), &frect);
	}

	bool RendererImpl::draw_triangle(penguin::math::Vector2 p1, penguin::math::Vector2 p2, penguin::math::Vector2 p3, penguin::math::Colour outline) {
		return draw_line(p1, p2, outline) && draw_line(p2, p3, outline) && draw_line(p1, p3, outline);
	}

	bool RendererImpl::draw_filled_triangle(penguin::math::Vector2 p1, penguin::math::Vector2 p2, penguin::math::Vector2 p3, penguin::math::Colour fill) {
		bool colour_applied = set_colour(fill);

		SDL_Vertex vertices[] = {
			{ {p1.x, p1.y}, {fill.r, fill.g, fill.b, fill.a}, {0, 0} },
			{ {p2.x, p2.y}, {fill.r, fill.g, fill.b, fill.a}, {0, 0} },
			{ {p3.x, p3.y}, {fill.r, fill.g, fill.b, fill.a}, {0, 0} }
		};

		return colour_applied && SDL_RenderGeometry(renderer.get(), nullptr, vertices, 3, nullptr, 0);
	}

	bool RendererImpl::draw_circle(penguin::math::Vector2 center, int rad, penguin::math::Colour outline) {
		// Initial points and decision variable.
		int x = rad - 1;
		int y = 0;
		int dx = 1;
		int dy = 1;
		int err = dx - (rad << 1); // (radius << 1 = diameter)

		// Vector for points to be rendered onto screen.
		std::vector<SDL_FPoint> points;

		// Fill all the 8 octances.
		while (x >= y) {
			points.push_back({ center.x + x, center.y + y });
			points.push_back({ center.x + x, center.y - y });
			points.push_back({ center.x - x, center.y + y });
			points.push_back({ center.x - x, center.y - y });
			points.push_back({ center.x + y, center.y + x });
			points.push_back({ center.x + y, center.y - x });
			points.push_back({ center.x - y, center.y + x });
			points.push_back({ center.x - y, center.y - x });

			if (err <= 0) {
				y++;
				err += dy;
				dy += 2;
			}

			if (err > 0) {
				x--;
				dx += 2;
				err += dx - (rad << 1);
			}
		}

		return set_colour(outline) && SDL_RenderPoints(renderer.get(), points.data(), points.size());
	}

	bool RendererImpl::draw_filled_circle(penguin::math::Vector2 center, int radius, penguin::math::Colour fill) {
		// Convert to Vector2i
		penguin::math::Vector2i center_(center.x, center.y);

		// Initial points and decision variable.
		int x = radius - 1;
		int y = 0;
		int dx = 1;
		int dy = 1;
		int err = dx - (radius << 1); // (radius << 1 = diameter)

		while (x >= y) {
			bool top_res = draw_horizontal_line(center.x - x, center.x + x, center.y + y, fill); // top span
			bool down_res = draw_horizontal_line(center.x - x, center.x + x, center.y - y, fill); // bottom span
			bool left_res = draw_horizontal_line(center.x - y, center.x + y, center.y + x, fill); // right span
			bool right_res = draw_horizontal_line(center.x - y, center.x + y, center.y - x, fill); // left span

			if (!top_res || !down_res || !left_res || !right_res) return false; // draw_line failed

			if (err <= 0) {
				y++;
				err += dy;
				dy += 2;
			}

			if (err > 0) {
				x--;
				dx += 2;
				err += dx - (radius << 1);
			}
		}

		return true;
	}

	bool RendererImpl::draw_ellipse(penguin::math::Vector2 center, int radius_x, int radius_y, penguin::math::Colour outline) {
		// Squares of the radii for the ellipse.
		int rx2 = radius_x * radius_x;
		int ry2 = radius_y * radius_y;

		// Initial points and decision variable for region 1.
		int x = 0;
		int y = radius_y;
		int dx = 2 * ry2 * x;
		int dy = 2 * rx2 * y;
		int err = ry2 - (rx2 * radius_y) + (rx2 / 4);

		// Vector for points to be rendered onto the screen.
		std::vector<SDL_FPoint> points;

		// |slope| < 1 (region 1).
		while (dx < dy) {
			// Symmetrical points.
			points.push_back({ center.x + x, center.y + y });
			points.push_back({ center.x - x, center.y + y });
			points.push_back({ center.x + x, center.y - y });
			points.push_back({ center.x - x, center.y - y });

			if (err < 0) {
				x++;
				dx += 2 * ry2;
				err += dx + ry2;
			}
			else {
				x++;
				y--;
				dx += 2 * ry2;
				dy -= 2 * rx2;
				err += dx - dy + ry2;
			}
		}

		err = ry2 * (x + 0.5) * (x + 0.5) + rx2 * (y - 1) * (y - 1) - rx2 * ry2;

		// |slope| >= 1 (region 2).
		while (y >= 0) {
			// Symmetrical points.
			points.push_back({ center.x + x, center.y + y });
			points.push_back({ center.x - x, center.y + y });
			points.push_back({ center.x + x, center.y - y });
			points.push_back({ center.x - x, center.y - y });

			if (err > 0) {
				y--;
				dy -= 2 * rx2;
				err += rx2 - dy;
			}
			else {
				y--;
				x++;
				dx += 2 * ry2;
				dy -= 2 * rx2;
				err += dx - dy + rx2;
			}
		}

		return 	set_colour(outline) && SDL_RenderPoints(renderer.get(), points.data(), points.size());
	}

	bool RendererImpl::draw_filled_ellipse(penguin::math::Vector2 center, int radius_x, int radius_y, penguin::math::Colour fill) {
		// Squares of the radii for the ellipse.
		int rx2 = radius_x * radius_x;
		int ry2 = radius_y * radius_y;

		// Initial points and decision variable for region 1.
		int x = 0;
		int y = radius_y;
		int dx = 2 * ry2 * x;
		int dy = 2 * rx2 * y;
		int err = ry2 - (rx2 * radius_y) + (rx2 / 4);

		// Vector for points to be rendered onto the screen.
		std::vector<SDL_FPoint> points;

		// |slope| < 1 (region 1).
		while (dx < dy) {
			// Fill horizontal lines for symmetrical points.
			for (int i = center.x - x; i <= center.x + x; i++) {
				points.push_back({ (float)i, center.y + y });
				points.push_back({ (float)i, center.y - y });
			}

			if (err < 0) {
				x++;
				dx += 2 * ry2;
				err += dx + ry2;
			}
			else {
				x++;
				y--;
				dx += 2 * ry2;
				dy -= 2 * rx2;
				err += dx - dy + ry2;
			}
		}

		err = ry2 * (x + 0.5) * (x + 0.5) + rx2 * (y - 1) * (y - 1) - rx2 * ry2;

		// |slope| >= 1 (region 2).
		while (y >= 0) {
			// Fill horizontal lines for symmetrical points.
			for (int i = center.x - x; i <= center.x + x; i++) {
				points.push_back({ (float)i, center.y + y });
				points.push_back({ (float)i, center.y - y });
			}

			if (err > 0) {
				y--;
				dy -= 2 * rx2;
				err += rx2 - dy;
			}
			else {
				y--;
				x++;
				dx += 2 * ry2;
				dy -= 2 * rx2;
				err += dx - dy + rx2;
			}
		}

		return set_colour(fill) && SDL_RenderPoints(renderer.get(), points.data(), points.size());
	}

	bool RendererImpl::draw_horizontal_line(float x1, float x2, float y, penguin::math::Colour colour) {
		return 	set_colour(colour) && SDL_RenderLine(renderer.get(), x1, y, x2, y);
	}

	bool RendererImpl::draw_sprite(NativeTexturePtr spr_texture, const penguin::math::Rect2& texture_region, const penguin::math::Rect2& screen_placement) {
		SDL_FRect sdl_source, sdl_dest;
		SDL_FRect* sdl_source_ptr = nullptr;
		SDL_FRect* sdl_dest_ptr = nullptr;
		SDL_Texture* texture = spr_texture.as<SDL_Texture>();

		// Set the source (texture region) and dest (screen placement) rects
		
		sdl_source.x = texture_region.position.x;
		sdl_source.y = texture_region.position.y;
		sdl_source.w = texture_region.size.x;
		sdl_source.h = texture_region.size.y;
		sdl_source_ptr = &sdl_source;
		
		sdl_dest.x = screen_placement.position.x;
		sdl_dest.y = screen_placement.position.y;
		sdl_dest.w = screen_placement.size.x;
		sdl_dest.h = screen_placement.size.y;
		sdl_dest_ptr = &sdl_dest;

		return SDL_RenderTexture(renderer.get(), texture, sdl_source_ptr, sdl_dest_ptr);
	}

	bool RendererImpl::draw_sprite_transformed(NativeTexturePtr spr_texture, const penguin::math::Rect2& texture_region, const penguin::math::Rect2& screen_placement,
		const penguin::math::Vector2& scale_factor, const penguin::math::Vector2& normalized_anchor, float angle, penguin::rendering::primitives::FlipMode mode) {
		SDL_FRect sdl_source, sdl_dest;
		SDL_FRect* sdl_source_ptr = nullptr;
		SDL_FRect* sdl_dest_ptr = nullptr;
		SDL_FPoint sdl_anchor;
		SDL_FPoint* sdl_anchor_ptr = nullptr;
		SDL_Texture* texture = spr_texture.as<SDL_Texture>();
		SDL_FlipMode sdl_mode = static_cast<SDL_FlipMode>(mode);

		penguin::math::Vector2 pixel_anchor = { screen_placement.size.x * normalized_anchor.x, screen_placement.size.y * normalized_anchor.y };

		// Set the source (texture region) and dest (screen placement) rects

		sdl_source.x = texture_region.position.x;
		sdl_source.y = texture_region.position.y;
		sdl_source.w = texture_region.size.x;
		sdl_source.h = texture_region.size.y;
		sdl_source_ptr = &sdl_source;

		sdl_dest.x = screen_placement.position.x;
		sdl_dest.y = screen_placement.position.y;
		sdl_dest.w = screen_placement.size.x;
		sdl_dest.h = screen_placement.size.y;
		sdl_dest_ptr = &sdl_dest;

		// Set the anchor point

		sdl_anchor.x = pixel_anchor.x;
		sdl_anchor.y = pixel_anchor.y;
		sdl_anchor_ptr = &sdl_anchor;

		return SDL_RenderTextureRotated(renderer.get(), texture, sdl_source_ptr, sdl_dest_ptr, angle, sdl_anchor_ptr, sdl_mode);
	}

	bool RendererImpl::draw_text(NativeTextPtr txt_ptr, float x, float y) {
		return TTF_DrawRendererText(txt_ptr.as<TTF_Text>(), x, y);
	}
}