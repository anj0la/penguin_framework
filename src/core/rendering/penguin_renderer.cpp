#include <penguin_framework/core/rendering/penguin_renderer.hpp>
#include <penguin_framework/core/rendering/penguin_renderer_impl.hpp>

// --- Define RendererImpl Methods ---

using penguin::core::rendering::Renderer;
using penguin::core::rendering::RendererImpl;

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
	return SDL_SetRenderDrawColor(renderer.get(), colour.r, colour.g, colour.b, colour.a);
}

bool RendererImpl::clear() {
	set_colour(Colours::Black);
	return SDL_RenderClear(renderer.get());
}

// Drawing functions

bool RendererImpl::draw_line(Vector2 vec1, Vector2 vec2, Colour colour = Colours::White) {
	set_colour(colour);
	return SDL_RenderLine(renderer.get(), vec1.x, vec1.y, vec2.x, vec2.y);
}

bool RendererImpl::draw_pixel(Vector2 vec, Colour colour = Colours::White) {
	set_colour(colour);
	return SDL_RenderPoint(renderer.get(), vec.x, vec.y);
}

bool RendererImpl::draw_rect(Rect2 rect, Colour outline = Colours::White) {
	set_colour(outline);
	SDL_FRect frect = { rect.position.x, rect.position.y, rect.size.x, rect.size.y };
	return SDL_RenderRect(renderer.get(), &frect);
}

bool RendererImpl::draw_filled_rect(Rect2 rect, Colour fill = Colours::White) {
	set_colour(fill);
	SDL_FRect frect = { rect.position.x, rect.position.y, rect.size.x, rect.size.y };
	return SDL_RenderFillRect(renderer.get(), &frect);
}

bool RendererImpl::draw_triangle(Vector2 x, Vector2 y, Vector2 z, Colour outline = Colours::White) {
	return draw_line(x, y, outline) && draw_line(y, z, outline) && draw_line(x, z, outline);
}

bool RendererImpl::draw_filled_triangle(Vector2 x, Vector2 y, Vector2 z, Colour fill = Colours::White) {
	return true; // will implement later
}

bool RendererImpl::draw_circle(Vector2 center, int rad, Colour outline = Colours::White) {
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

	// Draw the circle.
	set_colour(outline);
	return SDL_RenderPoints(renderer.get(), points.data(), points.size());
}

bool RendererImpl::draw_filled_circle(Vector2 center, int radius, Colour fill = Colours::White) {
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

bool RendererImpl::draw_ellipse(Vector2 center, int radius_x, int radius_y, Colour outline = Colours::White) {
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

	// Draw the ellipse.
	set_colour(outline);
	return SDL_RenderPoints(renderer.get(), points.data(), points.size());
}

bool RendererImpl::draw_filled_ellipse(Vector2 center, int radius_x, int radius_y, Colour fill = Colours::White) {
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

	// Draw the filled ellipse.
	set_colour(fill);
	return SDL_RenderPoints(renderer.get(), points.data(), points.size());
}

// Helper functions

bool RendererImpl::draw_horizontal_line(float x1, float x2, float y, Colour colour) {
	set_colour(colour);
	return SDL_RenderLine(renderer.get(), x1, y, x2, y); // Faster to call SDL than converting to Vector2
}

// --- Define Renderer Methods ---

Renderer::Renderer(window::Window& window, const char* driver_name = "") : pimpl_(std::make_unique<RendererImpl>(window.get_native_ptr(), driver_name)) {}
Renderer::~Renderer() = default;

// Displaying / clearing the renderer

bool Renderer::display() { return pimpl_->display(); }
bool Renderer::clear() { return pimpl_->clear(); }

// Drawing functions

bool Renderer::draw_line(Vector2 vec1, Vector2 vec2, Colour colour = Colours::White) { return pimpl_->draw_line(vec1, vec2, colour); }
bool Renderer::draw_pixel(Vector2 vec, Colour colour = Colours::White) { return pimpl_->draw_pixel(vec, colour); }
bool Renderer::draw_rect(Rect2 rect, Colour outline = Colours::White) { return pimpl_->draw_rect(rect, outline); }
bool Renderer::draw_filled_rect(Rect2 rect, Colour fill = Colours::White) { return pimpl_->draw_filled_rect(rect, fill); }
bool Renderer::draw_triangle(Vector2 vec1, Vector2 vec2, Vector2 vec3, Colour outline = Colours::White) { return pimpl_->draw_triangle(vec1, vec2, vec3, outline); }
bool Renderer::draw_filled_triangle(Vector2 vec1, Vector2 vec2, Vector2 vec3, Colour fill = Colours::White) { return pimpl_->draw_filled_triangle(vec1, vec2, vec3, fill); }
bool Renderer::draw_circle(Vector2 center, int rad, Colour outline = Colours::White) { return pimpl_->draw_circle(center, rad, outline); }
bool Renderer::draw_circle(Circle2 circle, Colour outline = Colours::White) { return pimpl_->draw_circle(circle.center, static_cast<int>(circle.radius), outline); }
bool Renderer::draw_filled_circle(Vector2 center, int radius, Colour fill = Colours::White) { return pimpl_->draw_filled_circle(center, radius, fill); }
bool Renderer::draw_filled_circle(Circle2 circle, Colour fill = Colours::White) { return pimpl_->draw_filled_circle(circle.center, static_cast<int>(circle.radius), fill); }
bool Renderer::draw_ellipse(Vector2 center, int radius_x, int radius_y, Colour outline = Colours::White) { return pimpl_->draw_ellipse(center, radius_x, radius_y, outline); }
bool Renderer::draw_filled_ellipse(Vector2 center, int radius_x, int radius_y, Colour fill = Colours::White) { return pimpl_->draw_filled_ellipse(center, radius_x, radius_y, fill); }

NativeRendererPtr Renderer::get_native_ptr() const { return NativeRendererPtr{ pimpl_->renderer.get() }; }
