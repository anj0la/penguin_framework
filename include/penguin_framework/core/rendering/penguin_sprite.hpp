#pragma once

#include <penguin_framework/penguin_api.hpp>
#include <penguin_framework/core/common/native_types.hpp>

#include <penguin_framework/core/rendering/primitives/penguin_texture.hpp>

#include <memory>

namespace penguin::core::rendering::primitives {

	struct SpriteImpl;

	enum class PENGUIN_API FlipMode {
		None = 0,
		Horizontal = 1,
		Vertical = 2
	};

	class PENGUIN_API Sprite {
	public:
		Sprite(std::shared_ptr<Texture> tex);
		~Sprite();

		// Copy and move constructors

		Sprite(const Sprite&) = default;
		Sprite& operator=(const Sprite&) = default;
		Sprite(Sprite&&) noexcept = default;
		Sprite& operator=(Sprite&&) noexcept = default;

		NativeTexturePtr get_native_ptr() const;
		Vector2 get_position() const;
		Vector2i get_size() const;
		float get_angle() const;
		Vector2 get_anchor_point() const;
		bool is_hidden() const;
		FlipMode get_flip_mode() const;
		Rect2 get_bounding_box() const;

		void set_texture(std::shared_ptr<Texture> texture);
		void set_position(Vector2 new_pos);
		void set_position(float x, float y);
		void set_angle(float new_angle);
		void set_anchor_point(Vector2 new_anchor_point);
		void set_anchor_point(float x, float y);
		void show();
		void hide();
		void set_flip_mode(FlipMode new_mode);
		void set_bounding_box(Rect2 bound_box);

		bool intersects(const Sprite& other) const;

	private:
		std::unique_ptr<SpriteImpl> pimpl_;

	};


}