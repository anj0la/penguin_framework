#include <penguin_framework/core/rendering/penguin_renderer.hpp>
#include <penguin_framework/core/rendering/penguin_renderer_impl.hpp>

// --- Define RendererImpl Methods ---

using penguin::core::rendering::Renderer;
using penguin::core::rendering::RendererImpl;
using penguin::core::rendering::RendererVSyncFlags;
using penguin::core::rendering::primitives::Sprite;
using penguin::core::rendering::primitives::FlipMode;

RendererImpl::RendererImpl(NativeWindowPtr window, const char* driver)
	: renderer(SDL_CreateRenderer(
		window.as<SDL_Window>(),
		String::compare("", driver) ? NULL : driver), // If empty, allow SDL to handle getting the driver.
		&SDL_DestroyRenderer) {

	// Throw an exception if the renderer was not intialized.
	Exception::throw_if(!renderer, "The renderer was not initialized.", Error::Renderer);
}

// Displaying / clearing the renderer

bool RendererImpl::display() {
	return SDL_RenderPresent(renderer.get());
}

bool RendererImpl::set_colour(Colour colour) {
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

bool RendererImpl::draw_line(Vector2 vec1, Vector2 vec2, Colour colour) {
	return set_colour(colour) && SDL_RenderLine(renderer.get(), vec1.x, vec1.y, vec2.x, vec2.y);
}

bool RendererImpl::draw_pixel(Vector2 vec, Colour colour) {
	return set_colour(colour) && SDL_RenderPoint(renderer.get(), vec.x, vec.y);
}

bool RendererImpl::draw_rect(Rect2 rect, Colour outline) {
	bool colour_applied = set_colour(outline);
	SDL_FRect frect = { rect.position.x, rect.position.y, rect.size.x, rect.size.y };
	return colour_applied && SDL_RenderRect(renderer.get(), &frect);
}

bool RendererImpl::draw_filled_rect(Rect2 rect, Colour fill) {
	bool colour_applied = set_colour(fill);
	SDL_FRect frect = { rect.position.x, rect.position.y, rect.size.x, rect.size.y };
	return colour_applied && SDL_RenderFillRect(renderer.get(), &frect);
}

bool RendererImpl::draw_triangle(Vector2 p1, Vector2 p2, Vector2 p3, Colour outline) {
	return draw_line(p1, p2, outline) && draw_line(p2, p3, outline) && draw_line(p1, p3, outline);
}

bool RendererImpl::draw_filled_triangle(Vector2 p1, Vector2 p2, Vector2 p3, Colour fill) {
	bool colour_applied = set_colour(fill);

	SDL_Vertex vertices[] = {
		{ {p1.x, p1.y}, {fill.r, fill.g, fill.b, fill.a}, {0, 0} },
		{ {p2.x, p2.y}, {fill.r, fill.g, fill.b, fill.a}, {0, 0} },
		{ {p3.x, p3.y}, {fill.r, fill.g, fill.b, fill.a}, {0, 0} }
	};

	return colour_applied && SDL_RenderGeometry(renderer.get(), nullptr, vertices, 3, nullptr, 0);
}

bool RendererImpl::draw_circle(Vector2 center, int rad, Colour outline) {
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

bool RendererImpl::draw_filled_circle(Vector2 center, int radius, Colour fill) {
	// Convert to Vector2i
	Vector2i center_(center.x, center.y);

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

bool RendererImpl::draw_ellipse(Vector2 center, int radius_x, int radius_y, Colour outline) {
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

bool RendererImpl::draw_filled_ellipse(Vector2 center, int radius_x, int radius_y, Colour fill) {
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

// Drawing functions for Sprites

bool RendererImpl::draw_sprite(NativeTexturePtr spr_texture, const Colour* tint_override) {
	return internal_draw_sprite(spr_texture, nullptr, nullptr, tint_override);
}

bool RendererImpl::draw_sprite_from(NativeTexturePtr spr_texture, const Rect2* source, const Colour* tint_override) {
	return internal_draw_sprite(spr_texture, source, nullptr, tint_override);
}

bool RendererImpl::draw_sprite_to(NativeTexturePtr spr_texture, const Rect2* dest, const Colour* tint_override) {
	return internal_draw_sprite(spr_texture, nullptr, dest, tint_override);
}

bool RendererImpl::draw_sprite_from_to(NativeTexturePtr spr_texture, const Rect2* source, const Rect2* dest, const Colour* tint_override) {
	return internal_draw_sprite(spr_texture, source, dest, tint_override);
}

bool RendererImpl::draw_sprite_transformed(NativeTexturePtr spr_texture, double angle, const Vector2* anchor_point, FlipMode mode, const Colour* tint_override) {
	return internal_draw_rotated_flipped(spr_texture, nullptr, nullptr, angle, anchor_point, mode, tint_override);
}

bool RendererImpl::draw_sprite_from_transformed(NativeTexturePtr spr_texture, const Rect2* source, double angle, const Vector2* anchor_point, FlipMode mode, const Colour* tint_override) {
	return internal_draw_rotated_flipped(spr_texture, source, nullptr, angle, anchor_point, mode, tint_override);
}

bool RendererImpl::draw_sprite_to_transformed(NativeTexturePtr spr_texture, const Rect2* dest, double angle, const Vector2* anchor_point, FlipMode mode, const Colour* tint_override) {
	return internal_draw_rotated_flipped(spr_texture, nullptr, dest, angle, anchor_point, mode, tint_override);
}

bool RendererImpl::draw_sprite_from_to_transformed(NativeTexturePtr spr_texture, const Rect2* source, const Rect2* dest, double angle, const Vector2* anchor_point, FlipMode mode, const Colour* tint_override) {
	return internal_draw_rotated_flipped(spr_texture, source, dest, angle, anchor_point, mode, tint_override);
}

bool RendererImpl::draw_sprite_global_scaled(NativeTexturePtr spr_texture, const Vector2* scale, const Colour* tint_override) {
	return internal_draw_fullscreen_scaled(spr_texture, nullptr, scale, tint_override);
}

bool RendererImpl::draw_sprite_from_scaled(NativeTexturePtr spr_texture, const Rect2* source, const Vector2* scale, const Colour* tint_override) {
	return internal_draw_fullscreen_scaled(spr_texture, source, scale, tint_override);
}

bool RendererImpl::draw_sprite_to_scaled(NativeTexturePtr spr_texture, const Rect2* dest, const Vector2* scale, const Colour* tint_override) {
	Rect2 final_dest;
	const Rect2* final_dest_ptr = nullptr;

	final_dest.position = dest->position;
	final_dest.size = {
		dest->size.x * scale->x,
		dest->size.y * scale->y
	};
	final_dest_ptr = &final_dest;
	
	return internal_draw_sprite(spr_texture, nullptr, final_dest_ptr, tint_override);
}

bool RendererImpl::draw_sprite_from_to_scaled(NativeTexturePtr spr_texture, const Rect2* source, const Rect2* dest, const Vector2* scale, const Colour* tint_override) {
	Rect2 final_dest;
	const Rect2* final_dest_ptr = nullptr;

	final_dest.position = dest->position;
	final_dest.size = {
		dest->size.x * scale->x,
		dest->size.y * scale->y
	};
	final_dest_ptr = &final_dest;

	return internal_draw_sprite(spr_texture, source, final_dest_ptr, tint_override);
}

// Helper functions

bool RendererImpl::draw_horizontal_line(float x1, float x2, float y, Colour colour) {
	set_colour(colour);
	return SDL_RenderLine(renderer.get(), x1, y, x2, y); // Faster to call SDL than converting to Vector2
}

bool RendererImpl::internal_draw_sprite(NativeTexturePtr spr_texture, const Rect2* source_ptr, const Rect2* dest_ptr, const Colour* tint_ptr) {
	SDL_FRect sdl_source, sdl_dest;
	SDL_FRect* sdl_source_ptr = nullptr;
	SDL_FRect* sdl_dest_ptr = nullptr;
	SDL_Texture* texture = spr_texture.as<SDL_Texture>();

	// Set the source and dest pointers
	if (source_ptr) {
		sdl_source.x = source_ptr->position.x;
		sdl_source.y = source_ptr->position.y;
		sdl_source.w = source_ptr->size.x;
		sdl_source.h = source_ptr->size.y;

		sdl_source_ptr = &sdl_source;
	}
	if (dest_ptr) {
		sdl_dest.x = dest_ptr->position.x;
		sdl_dest.y = dest_ptr->position.y;
		sdl_dest.w = dest_ptr->size.x;
		sdl_dest.h = dest_ptr->size.y;

		sdl_dest_ptr = &sdl_dest;
	}

	if (!tint_ptr) { // No tint exists, call function as normal
		return SDL_RenderTexture(renderer.get(), texture, sdl_source_ptr, sdl_dest_ptr); // No need to apply tint
	}

	bool applied_tint = SDL_SetTextureColorMod(texture, tint_ptr->r, tint_ptr->g, tint_ptr->b);
	bool applied_alpha_tint = SDL_SetTextureAlphaMod(texture, tint_ptr->a);
	bool rendered_texture = SDL_RenderTexture(renderer.get(), texture, sdl_source_ptr, sdl_dest_ptr);
	bool removed_tint = SDL_SetTextureColorMod(texture, Colours::Transparent.r, Colours::Transparent.g, Colours::Transparent.b);
	bool removed_alpha_tint = SDL_SetTextureAlphaMod(texture, Colours::Transparent.a);

	return applied_tint && applied_alpha_tint && rendered_texture && removed_tint && removed_alpha_tint; // checks that EVERY SDL call was successful
}

bool RendererImpl::internal_draw_rotated_flipped(NativeTexturePtr spr_texture, const Rect2* source_ptr, const Rect2* dest_ptr, double angle, const Vector2* anchor, FlipMode mode, const Colour* tint_ptr) {
	SDL_FRect sdl_source, sdl_dest;
	SDL_FRect* sdl_source_ptr = nullptr;
	SDL_FRect* sdl_dest_ptr = nullptr;
	SDL_FPoint sdl_anchor;
	SDL_FPoint* sdl_anchor_ptr = nullptr;
	SDL_Texture* texture = spr_texture.as<SDL_Texture>();

	// Set the source, dest and anchor pointers
	if (source_ptr) {
		sdl_source.x = source_ptr->position.x;
		sdl_source.y = source_ptr->position.y;
		sdl_source.w = source_ptr->size.x;
		sdl_source.h = source_ptr->size.y;

		sdl_source_ptr = &sdl_source;
	}
	if (dest_ptr) {
		sdl_dest.x = dest_ptr->position.x;
		sdl_dest.y = dest_ptr->position.y;
		sdl_dest.w = dest_ptr->size.x;
		sdl_dest.h = dest_ptr->size.y;

		sdl_dest_ptr = &sdl_dest;
	}
	if (anchor) {
		if (sdl_dest_ptr) { // Anchor is relative to the destination rect
			sdl_anchor.x = anchor->x * sdl_dest_ptr->w;
			sdl_anchor.y = anchor->y * sdl_dest_ptr->h;
		}
		else {
			// No dest_ptr, anchor is relative to the entire render target
			int output_w, output_h;
			SDL_GetRenderOutputSize(renderer.get(), &output_w, &output_h);
			sdl_anchor.x = anchor->x * static_cast<float>(output_w);
			sdl_anchor.y = anchor->y * static_cast<float>(output_h);
		}
		sdl_anchor_ptr = &sdl_anchor;
	}

	if (!tint_ptr) {
		return SDL_RenderTextureRotated(renderer.get(), texture, sdl_source_ptr, sdl_dest_ptr, angle, sdl_anchor_ptr, static_cast<SDL_FlipMode>(mode)); // No need to apply tint
	}

	bool applied_tint = SDL_SetTextureColorMod(texture, tint_ptr->r, tint_ptr->g, tint_ptr->b);
	bool applied_alpha_tint = SDL_SetTextureAlphaMod(texture, tint_ptr->a);
	bool rendered_texture = SDL_RenderTextureRotated(renderer.get(), texture, sdl_source_ptr, sdl_dest_ptr, angle, sdl_anchor_ptr, static_cast<SDL_FlipMode>(mode));
	bool removed_tint = SDL_SetTextureColorMod(texture, Colours::Transparent.r, Colours::Transparent.g, Colours::Transparent.b);
	bool removed_alpha_tint = SDL_SetTextureAlphaMod(texture, Colours::Transparent.a);

	return applied_tint && applied_alpha_tint && rendered_texture && removed_tint && removed_alpha_tint; // checks that EVERY SDL call was successful
}

bool RendererImpl::internal_draw_fullscreen_scaled(NativeTexturePtr spr_texture, const Rect2* source_ptr, const Vector2* scale_factor, const Colour* tint_ptr) {
	SDL_FRect sdl_source, sdl_dest;
	SDL_FRect* sdl_source_ptr = nullptr;
	SDL_FRect* sdl_dest_ptr = nullptr;
	SDL_Texture* texture = spr_texture.as<SDL_Texture>();

	// Set the source and dest pointers
	if (source_ptr) {
		sdl_source.x = source_ptr->position.x;
		sdl_source.y = source_ptr->position.y;
		sdl_source.w = source_ptr->size.x;
		sdl_source.h = source_ptr->size.y;

		sdl_source_ptr = &sdl_source;
	}

	if (!tint_ptr) { // No need to apply tint
		bool scaled_texture = SDL_SetRenderScale(renderer.get(), scale_factor->x, scale_factor->y);
		bool rendered_texture = SDL_RenderTexture(renderer.get(), texture, sdl_source_ptr, sdl_dest_ptr);
		bool reset_scale = SDL_SetRenderScale(renderer.get(), 1.0f, 1.0f);
		return scaled_texture && rendered_texture && reset_scale;
	}

	bool applied_tint = SDL_SetTextureColorMod(texture, tint_ptr->r, tint_ptr->g, tint_ptr->b);
	bool applied_alpha_tint = SDL_SetTextureAlphaMod(texture, tint_ptr->a);
	bool scaled_texture = SDL_SetRenderScale(renderer.get(), scale_factor->x, scale_factor->y);
	bool rendered_texture = SDL_RenderTexture(renderer.get(), texture, sdl_source_ptr, sdl_dest_ptr);
	bool reset_scale = SDL_SetRenderScale(renderer.get(), 1.0f, 1.0f);
	bool removed_tint = SDL_SetTextureColorMod(texture, Colours::NoTint.r, Colours::NoTint.g, Colours::NoTint.b);
	bool removed_alpha_tint = SDL_SetTextureAlphaMod(texture, Colours::NoTint.a);

	return applied_tint && applied_alpha_tint && scaled_texture && rendered_texture && reset_scale && removed_tint && removed_alpha_tint; // checks that EVERY SDL call was successful
}

// --- Define Renderer Methods ---

Renderer::Renderer(NativeWindowPtr window_ptr, const char* driver_name) : pimpl_(std::make_unique<RendererImpl>(window_ptr, driver_name)) {}
Renderer::~Renderer() = default;

// Displaying / clearing the renderer

bool Renderer::display() { return pimpl_->display(); }
bool Renderer::clear() { return pimpl_->clear(); }

// Drawing functions

bool Renderer::draw_line(Vector2 vec1, Vector2 vec2, Colour colour) { 
	return pimpl_->draw_line(vec1, vec2, colour); 
}

bool Renderer::draw_pixel(Vector2 vec, Colour colour) { 
	return pimpl_->draw_pixel(vec, colour); 
}

bool Renderer::draw_rect(Rect2 rect, Colour outline) { 
	return pimpl_->draw_rect(rect, outline); 
}

bool Renderer::draw_filled_rect(Rect2 rect, Colour fill) { 
	return pimpl_->draw_filled_rect(rect, fill); 
}

bool Renderer::draw_triangle(Vector2 vec1, Vector2 vec2, Vector2 vec3, Colour outline) { 
	return pimpl_->draw_triangle(vec1, vec2, vec3, outline); 
}

bool Renderer::draw_filled_triangle(Vector2 vec1, Vector2 vec2, Vector2 vec3, Colour fill) { 
	return pimpl_->draw_filled_triangle(vec1, vec2, vec3, fill); 
}

bool Renderer::draw_circle(Vector2 center, int rad, Colour outline) { 
	return pimpl_->draw_circle(center, rad, outline); 
}

bool Renderer::draw_circle(Circle2 circle, Colour outline) { 
	return pimpl_->draw_circle(circle.center, static_cast<int>(circle.radius), outline); 
}

bool Renderer::draw_filled_circle(Vector2 center, int radius, Colour fill) { 
	return pimpl_->draw_filled_circle(center, radius, fill); 
}

bool Renderer::draw_filled_circle(Circle2 circle, Colour fill) { 
	return pimpl_->draw_filled_circle(circle.center, static_cast<int>(circle.radius), fill); 
}

bool Renderer::draw_ellipse(Vector2 center, int radius_x, int radius_y, Colour outline) { 
	return pimpl_->draw_ellipse(center, radius_x, radius_y, outline); 
}

bool Renderer::draw_filled_ellipse(Vector2 center, int radius_x, int radius_y, Colour fill) { 
	return pimpl_->draw_filled_ellipse(center, radius_x, radius_y, fill); 
}

// Drawing functions for Sprites

bool Renderer::draw_sprite(Sprite spr) { 
	Colour tint = spr.get_colour_tint();
	return pimpl_->draw_sprite(spr.get_native_ptr(), &tint);
}

bool Renderer::draw_sprite_from(Sprite spr, Rect2 source) { 
	Colour tint = spr.get_colour_tint();
	return pimpl_->draw_sprite_from(spr.get_native_ptr(), &source, &tint);
}

bool Renderer::draw_sprite_to(Sprite spr, Rect2 dest_override) { 
	Colour tint = spr.get_colour_tint();
	return pimpl_->draw_sprite_to(spr.get_native_ptr(), &dest_override, &tint);
}

bool Renderer::draw_sprite_from_to(Sprite spr, Rect2 source, Rect2 dest_override) { 
	Colour tint = spr.get_colour_tint();
	return pimpl_->draw_sprite_from_to(spr.get_native_ptr(), &source, &dest_override, &tint);
}

bool Renderer::draw_sprite_transformed(Sprite spr) { 
	Colour tint = spr.get_colour_tint();
	return pimpl_->draw_sprite_transformed(spr.get_native_ptr(), spr.get_angle(), nullptr, spr.get_flip_mode(), &tint);
}

bool Renderer::draw_sprite_transformed_ex(Sprite spr, Vector2 anchor_point) {
	Colour tint = spr.get_colour_tint();
	return pimpl_->draw_sprite_transformed(spr.get_native_ptr(), spr.get_angle(), &anchor_point, spr.get_flip_mode(), &tint);
}

bool Renderer::draw_sprite_from_transformed(Sprite spr, Rect2 source) {
	Colour tint = spr.get_colour_tint();
	return pimpl_->draw_sprite_from_transformed(spr.get_native_ptr(), &source, spr.get_angle(), nullptr, spr.get_flip_mode(), &tint);
}

bool Renderer::draw_sprite_from_transformed_ex(Sprite spr, Rect2 source, Vector2 anchor_point) {
	Colour tint = spr.get_colour_tint();
	return pimpl_->draw_sprite_from_transformed(spr.get_native_ptr(), &source, spr.get_angle(), &anchor_point, spr.get_flip_mode(), &tint);
}

bool Renderer::draw_sprite_to_transformed(Sprite spr, Rect2 dest_override) {
	Colour tint = spr.get_colour_tint();
	return pimpl_->draw_sprite_to_transformed(spr.get_native_ptr(), &dest_override, spr.get_angle(), nullptr, spr.get_flip_mode(), &tint);
}

bool Renderer::draw_sprite_to_transformed_ex(Sprite spr, Rect2 dest_override, Vector2 anchor_point) {
	Colour tint = spr.get_colour_tint();
	return pimpl_->draw_sprite_to_transformed(spr.get_native_ptr(), &dest_override, spr.get_angle(), &anchor_point, spr.get_flip_mode(), &tint);
}

bool Renderer::draw_sprite_from_to_transformed(Sprite spr, Rect2 source, Rect2 dest_override) {
	Colour tint = spr.get_colour_tint();
	return pimpl_->draw_sprite_from_to_transformed(spr.get_native_ptr(), &source, &dest_override, spr.get_angle(), nullptr, spr.get_flip_mode(), &tint);
}

bool Renderer::draw_sprite_from_to_transformed_ex(Sprite spr, Rect2 source, Rect2 dest_override, Vector2 anchor_point) {
	Colour tint = spr.get_colour_tint();
	return pimpl_->draw_sprite_from_to_transformed(spr.get_native_ptr(), &source, &dest_override, spr.get_angle(), &anchor_point, spr.get_flip_mode(), &tint);
}

bool Renderer::draw_sprite_global_scaled(Sprite spr) {
	Colour tint = spr.get_colour_tint();
	Vector2 scale_val = spr.get_scale();
	return pimpl_->draw_sprite_global_scaled(spr.get_native_ptr(), &scale_val, &tint);
}

bool Renderer::draw_sprite_from_scaled(Sprite spr, Rect2 source) {
	Colour tint = spr.get_colour_tint();
	Vector2 scale_val = spr.get_scale();
	return pimpl_->draw_sprite_from_scaled(spr.get_native_ptr(), &source, &scale_val, &tint);
}

bool Renderer::draw_sprite_to_scaled(Sprite spr, Rect2 dest_override) {
	Colour tint = spr.get_colour_tint();
	Vector2 scale_val = spr.get_scale();
	return pimpl_->draw_sprite_to_scaled(spr.get_native_ptr(), &dest_override, &scale_val, &tint);
}

bool Renderer::draw_sprite_from_to_scaled(Sprite spr, Rect2 source, Rect2 dest_override) {
	Colour tint = spr.get_colour_tint();
	Vector2 scale_val = spr.get_scale();
	return pimpl_->draw_sprite_from_to_scaled(spr.get_native_ptr(), &source, &dest_override, &scale_val, &tint);
}

NativeRendererPtr Renderer::get_native_ptr() const { return NativeRendererPtr{ 
	pimpl_->renderer.get() }; 
}
