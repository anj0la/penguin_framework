#pragma once

#include <penguin_framework/core/common/native_types.hpp>
#include <penguin_framework/core/rendering/primitives/penguin_texture.hpp>

#include <penguin_framework/core/math/rect2.hpp>
#include <penguin_framework/core/math/circle2.hpp>
#include <penguin_framework/core/math/colours.hpp>
#include <penguin_framework/core/math/vector2.hpp>
#include <penguin_framework/core/math/vector2i.hpp>

#include <penguin_framework/utils/exception.hpp>

#include <memory>
#include <vector>
#include <algorithm>

namespace penguin::core::rendering::primitives {

	struct SpriteImpl {
		std::shared_ptr<Texture> texture;
		Vector2 position;
		Vector2i size;
		Rect2 texture_region;
		Rect2 screen_placement;
		Vector2 scale_factor;
		double angle;
		Vector2 anchor;
		bool visible;
		FlipMode mode;
		Colour tint;
		Rect2 bounding_box; // to handle collisions between two sprites (NOTE: Update to BoundingShape struct to store other types of shapes, like Circle2, Polygon2, etc., after adding intersection functions)

		// Constructor
		SpriteImpl(std::shared_ptr<Texture> p_texture);

		// Copy and move constructors

		SpriteImpl(const SpriteImpl&) = default;
		SpriteImpl& operator=(const SpriteImpl&) = default;
		SpriteImpl(SpriteImpl&&) noexcept = default;
		SpriteImpl& operator=(SpriteImpl&&) noexcept = default;

		// Getters

		NativeTexturePtr get_native_ptr() const;

		Vector2 get_position() const;
		Vector2i get_size() const;
		Rect2 get_texture_region() const;
		Rect2 get_screen_placement() const;
		Vector2 get_scale() const;
		double get_angle() const;
		Vector2 get_anchor() const;
		bool is_hidden() const;
		FlipMode get_flip_mode() const;
		Colour get_colour_tint() const;
		Rect2 get_bounding_box() const;

		// Setters

		void set_texture(std::shared_ptr<Texture> new_texture);
		void set_position(const Vector2& new_position);
		void set_texture_region(const Rect2& new_region);
		void set_screen_placement(const Rect2& new_placement);
		void set_scale(const Vector2& new_scale_factor);
		void set_angle(double new_angle);
		void set_anchor(const Vector2& new_anchor);
		void normalize_anchor_point();
		void clear_anchor_point();
		void show();
		void hide();
		void set_flip_mode(const FlipMode& new_mode);
		void set_colour_tint(const Colour& new_tint);
		void set_bounding_box(const Rect2& new_bounding_box);

		// Other functions

		void clear_texture();
		bool has_texture();
		void use_full_region();
		void use_default_screen_placement();

		void update_screen_placement();


	};
}