#include <rendering/primitives/internal/penguin_sprite_impl.hpp>

namespace penguin::internal::rendering::primitives {

	SpriteImpl::SpriteImpl(std::shared_ptr<penguin::rendering::primitives::Texture> p_texture) : texture(std::move(p_texture)) {

		penguin::internal::error::InternalError::throw_if(
			!p_texture,
			"Failed to load the texture.",
			penguin::internal::error::ErrorCode::Resource_Load_Failed
		);

		position = penguin::math::Vector2::Zero; // the top-left corner represents the position of the Sprite
		size = p_texture.get()->get_size();
		texture_region = penguin::math::Rect2{ position.x, position.y, size.x, size.y }; // position -> (0,0), size -> (texture_width, texture_height) for the full texture
		screen_placement = penguin::math::Rect2{ position.x, position.y, size.x, size.y };
		scale_factor = penguin::math::Vector2::One;
		angle = 0.0;
		anchor = penguin::math::Vector2{ 0.5f, 0.5f }; // center
		visible = true;
		mode = penguin::rendering::primitives::FlipMode::None;
		tint = Colours::NoTint;
		bounding_box = penguin::math::Rect2{ position.x, position.y, size.x, size.y }; // initally the size of the texture
	}

	// Getters

	NativeTexturePtr SpriteImpl::get_native_ptr() const {
		return texture->get_native_ptr();
	}

	// Other functions

	bool SpriteImpl::update_screen_placement() {
		// Texture is invalid, nothing should be rendered onto the screen
		if (!texture) {
			screen_placement = penguin::math::Rect2{ penguin::math::Vector2::Zero, penguin::math::Vector2::Zero };
			return false;
		}

		// Otherwise, we update the screen placement with the position and scale_factor
		penguin::math::Vector2 base_size{ texture_region.size.x, texture_region.size.y };

		// Texture is valid, but the source portion defines a zero-area
		if (base_size.x <= 0 || base_size.y <= 0) { // same as base_size <= Vector2::Zero, but more readable
			screen_placement = penguin::math::Rect2{ penguin::math::Vector2::Zero, penguin::math::Vector2::Zero };
			return false;
		}

		// Texture is valid, and the source portion defines a valid non-zero area
		penguin::math::Vector2 scaled_size{ base_size.x * scale_factor.x, base_size.y * scale_factor.y };
		screen_placement = penguin::math::Rect2{ position, scaled_size };

		// Update the anchor point
		anchor = anchor * scaled_size; // anchor.x * scaled_size.x and anchor.y * scaled_size.y

		return true; // successfuly updated screen placement
	}
}