#include <penguin_framework/rendering/drawables/sprite.hpp>
#include <rendering/drawables/internal/sprite_impl.hpp>
#include <penguin_framework/logger/logger.hpp>

namespace penguin::rendering::drawables {

	Sprite::Sprite(std::shared_ptr<primitives::Texture> p_texture) : pimpl_(nullptr) {

		// Log attempt to create a sprite
		PF_LOG_INFO("Attempting to create sprite...");

		if (p_texture) { // Don't create the sprite if there's no valid texture!
			try {
				pimpl_ = std::make_unique<penguin::internal::rendering::drawables::SpriteImpl>(p_texture);
				PF_LOG_INFO("Success: Sprite created successfully.");
			}
			catch (const penguin::internal::error::InternalError& e) {
				// Get the error code and message
				std::string error_code_str = penguin::internal::error::error_code_to_string(e.get_error());
				std::string error_message = error_code_str + ": " + e.what();

				// Log the error
				PF_LOG_ERROR(error_message.c_str());

			}
			catch (const std::exception& e) { // Other specific C++ errors
				// Get error message
				std::string last_error_message = e.what();
				std::string error_message = "Unknown_Error: " + error_message;

				// Log the error
				PF_LOG_ERROR(error_message.c_str());
			}
		}
		else {
			PF_LOG_ERROR("Sprite_Creation_Failed: The texture is null or has not been initialized.");
		}
	}

	Sprite::~Sprite() = default;

	Sprite::Sprite(Sprite&&) noexcept = default;
	Sprite& Sprite::operator=(Sprite&&) noexcept = default;

	// Validity checking

	bool Sprite::is_valid() const noexcept {
		if (!pimpl_) {
			return false;
		}

		return pimpl_->texture.get() && pimpl_->get_native_ptr().ptr; // checks that the shared ptr Texture is not null along with the native texture ptr
	}

	Sprite::operator bool() const noexcept {
		return is_valid();
	}

	// Getters

	penguin::math::Vector2 Sprite::get_position() const {
		if (!is_valid()) {
			PF_LOG_WARNING("get_position() called on an uninitialized or destroyed sprite.");
			return penguin::math::Vector2::Zero;
		}

		return pimpl_->position;
	}

	penguin::math::Vector2i Sprite::get_size() const {
		if (!is_valid()) {
			PF_LOG_WARNING("get_size() called on an uninitialized or destroyed sprite.");
			return penguin::math::Vector2i::Zero;
		}

		return pimpl_->size;
	}

	int Sprite::get_width() const {
		if (!is_valid()) {
			PF_LOG_WARNING("get_width() called on an uninitialized or destroyed sprite.");
			return 0;
		}

		return pimpl_->size.x;
	}

	int Sprite::get_height() const {
		if (!is_valid()) {
			PF_LOG_WARNING("get_height() called on an uninitialized or destroyed sprite.");
			return 0;
		}

		return pimpl_->size.y;
	}

	penguin::math::Rect2 Sprite::get_texture_region() const {
		if (!is_valid()) {
			PF_LOG_WARNING("get_texture_region() called on an uninitialized or destroyed sprite.");
			return penguin::math::Rect2{ penguin::math::Vector2::Zero, penguin::math::Vector2::Zero };
		}

		return pimpl_->texture_region;
	}

	penguin::math::Rect2 Sprite::get_screen_placement() const {
		if (!is_valid()) {
			PF_LOG_WARNING("get_screen_placement() called on an uninitialized or destroyed sprite.");
			return penguin::math::Rect2{ penguin::math::Vector2::Zero, penguin::math::Vector2::Zero };
		}

		return pimpl_->screen_placement;
	}

	penguin::math::Vector2 Sprite::get_scale_factor() const {
		if (!is_valid()) {
			PF_LOG_WARNING("get_scale_factor() called on an uninitialized or destroyed sprite.");
			return penguin::math::Vector2::Zero;
		}

		return pimpl_->scale_factor;;
	}

	double Sprite::get_angle() const {
		if (!is_valid()) {
			PF_LOG_WARNING("get_angle() called on an uninitialized or destroyed sprite.");
			return 0.0;
		} 

		return pimpl_->angle;
	}

	penguin::math::Vector2 Sprite::get_anchor() const {
		if (!is_valid()) {
			PF_LOG_WARNING("get_anchor() called on an uninitialized or destroyed sprite.");
			return penguin::math::Vector2::Zero;
		}

		return pimpl_->anchor;
	}

	bool Sprite::is_hidden() const {
		if (!is_valid()) {
			PF_LOG_WARNING("is_hidden() called on an uninitialized or destroyed sprite.");
			return true;
		}

		return !pimpl_->visible;
	}

	penguin::math::Colour Sprite::get_colour_tint() const {
		if (!is_valid()) {
			PF_LOG_WARNING("get_colour_tint() called on an uninitialized or destroyed sprite.");
			return Colours::NoTint;
		}

		return pimpl_->tint;
	}

	primitives::FlipMode Sprite::get_flip_mode() const {
		if (!is_valid()) {
			PF_LOG_WARNING("get_flip_mode() called on an uninitialized or destroyed sprite.");
			return primitives::FlipMode::None;
		}

		return pimpl_->mode;
	}

	penguin::math::Rect2 Sprite::get_bounding_box() const {
		if (!is_valid()) {
			PF_LOG_WARNING("get_bounding_box() called on an uninitialized or destroyed sprite.");
			return penguin::math::Rect2{ penguin::math::Vector2::Zero, penguin::math::Vector2::Zero };
		}

		return pimpl_->bounding_box;
	}

	// Setters

	void Sprite::set_texture(std::shared_ptr<primitives::Texture> new_texture) {
		if (!is_valid()) {
			PF_LOG_WARNING("set_texture() called on an uninitialized or destroyed sprite.");
			return;
		}

		if (!new_texture) {
			PF_LOG_WARNING("Null_Argument: Texture is null."); 
			pimpl_->texture = std::move(new_texture);  // Still allow setting null
			pimpl_->size = penguin::math::Vector2i::Zero; // Set size to 0
			return; // Early return since we can't get size from null texture
		}

		pimpl_->texture = std::move(new_texture);
		pimpl_->size = pimpl_->texture->get_size();
	}

	void Sprite::set_position(const penguin::math::Vector2& new_position) {
		if (!is_valid()) {
			PF_LOG_WARNING("set_position() called on an uninitialized or destroyed sprite.");
			return;
		}

		pimpl_->position = new_position;
		pimpl_->bounding_box.position = new_position;

		bool res = pimpl_->update_screen_placement();

		if (!res) {
			// Log as warning 
			PF_LOG_WARNING("Invalid_Operation: Texture was null or the source portion had a zero area.");
		}
	}

	void Sprite::set_position(float x, float y) {
		if (!is_valid()) {
			PF_LOG_WARNING("set_position() called on an uninitialized or destroyed sprite.");
			return;
		}

		pimpl_->position = penguin::math::Vector2(x, y);
		pimpl_->bounding_box.position = pimpl_->position;

		bool res = pimpl_->update_screen_placement();

		if (!res) {
			// Log as warning 
			PF_LOG_WARNING("Invalid_Operation: Texture was null or the source portion had a zero area.");
		}
	}

	void Sprite::set_texture_region(const penguin::math::Rect2& new_region) {
		if (!is_valid()) {
			PF_LOG_WARNING("set_texture_region() called on an uninitialized or destroyed sprite.");
			return;
		}

		pimpl_->texture_region = new_region;

		bool res = pimpl_->update_screen_placement();

		if (!res) {
			// Log as warning 
			PF_LOG_WARNING("Invalid_Operation: Texture was null or the source portion had a zero area.");
		}
	}

	void Sprite::set_screen_placement(const penguin::math::Rect2& new_placement) {
		if (!is_valid()) {
			PF_LOG_WARNING("set_screen_placement() called on an uninitialized or destroyed sprite.");
			return;
		}

		pimpl_->screen_placement = new_placement;
	}

	void Sprite::set_scale_factor(const penguin::math::Vector2& new_scale_factor) {
		if (!is_valid()) {
			PF_LOG_WARNING("set_scale_factor() called on an uninitialized or destroyed sprite.");
			return;
		}

		pimpl_->scale_factor = new_scale_factor;

		bool res = pimpl_->update_screen_placement();

		if (!res) {
			// Log as warning 
			PF_LOG_WARNING("Invalid_Operation: Texture was null or the source portion had a zero area.");
		}
	}
	void Sprite::set_scale_factor(float x, float y) {
		if (!is_valid()) {
			PF_LOG_WARNING("set_scale_factor() called on an uninitialized or destroyed sprite.");
			return;
		}

		pimpl_->scale_factor = penguin::math::Vector2(x, y);

		bool res = pimpl_->update_screen_placement();

		if (!res) {
			// Log as warning 
			PF_LOG_WARNING("Invalid_Operation: Texture was null or the source portion had a zero area.");
		}
	}

	void Sprite::set_angle(double new_angle) {
		if (!is_valid()) {
			PF_LOG_WARNING("set_angle() called on an uninitialized or destroyed sprite.");
			return;
		}

		pimpl_->angle = new_angle;
	}

	void Sprite::set_anchor(const penguin::math::Vector2& new_anchor) {
		if (!is_valid()) {
			PF_LOG_WARNING("set_anchor() called on an uninitialized or destroyed sprite.");
			return;
		}

		pimpl_->anchor.x = std::clamp(new_anchor.x, 0.0f, 1.0f);
		pimpl_->anchor.y = std::clamp(new_anchor.y, 0.0f, 1.0f);

		bool res = pimpl_->update_screen_placement();

		if (!res) {
			// Log as warning 
			PF_LOG_WARNING("Invalid_Operation: Texture was null or the source portion had a zero area.");
		}
	}

	void Sprite::set_anchor(float x, float y) {
		if (!is_valid()) {
			PF_LOG_WARNING("set_anchor() called on an uninitialized or destroyed sprite.");
			return;
		}

		pimpl_->anchor.x = std::clamp(x, 0.0f, 1.0f);
		pimpl_->anchor.y = std::clamp(y, 0.0f, 1.0f);

		bool res = pimpl_->update_screen_placement();

		if (!res) {
			// Log as warning 
			PF_LOG_WARNING("Invalid_Operation: Texture was null or the source portion had a zero area.");
		}
	}

	void Sprite::show() {
		if (!is_valid()) {
			PF_LOG_WARNING("show() called on an uninitialized or destroyed sprite.");
			return;
		}

		pimpl_->visible = true;
	}

	void Sprite::hide() {
		if (!is_valid()) {
			PF_LOG_WARNING("hide() called on an uninitialized or destroyed sprite.");
			return;
		}

		pimpl_->visible = false;
	}

	void Sprite::set_flip_mode(primitives::FlipMode new_mode) {
		if (!is_valid()) {
			PF_LOG_WARNING("set_flip_mode() called on an uninitialized or destroyed sprite.");
			return;
		}

		pimpl_->mode = new_mode;
	}

	void Sprite::set_colour_tint(const penguin::math::Colour& new_tint) {
		if (!is_valid()) {
			PF_LOG_WARNING("set_colour_tint() called on an uninitialized or destroyed sprite.");
			return;
		}

		bool res = pimpl_->set_colour_tint(new_tint);

		if (!res) {
			PF_LOG_WARNING("Internal_System_Error: Failed to set colour tint on sprite.");
		}
	}

	void Sprite::set_bounding_box(const penguin::math::Rect2 &new_bounding_box) {
		if (!is_valid()) {
			PF_LOG_WARNING("set_bounding_box() called on an uninitialized or destroyed sprite.");
			return;
		}

		pimpl_->bounding_box = new_bounding_box;
	}

	// Collision detection

	bool Sprite::intersects(const Sprite& other) const {
		if (!is_valid()) {
			PF_LOG_WARNING("intersects() called on an uninitialized or destroyed sprite.");
			return false;
		}

		return pimpl_->bounding_box.intersects(other.get_bounding_box());
	}

	// Other functions

	void Sprite::clear_colour_tint() {
		if (!is_valid()) {
			PF_LOG_WARNING("clear_colour_tint() called on an uninitialized or destroyed sprite.");
			return; // can't access a function with a NULL pointer
		}

		bool res = pimpl_->clear_colour_tint();

		if (!res) {
			PF_LOG_WARNING("Internal_System_Error: Failed to clear colour tint on sprite.");
		}
	}

	bool Sprite::has_texture() const {
		if (!is_valid()) {
			PF_LOG_WARNING("has_texture() called on an uninitialized or destroyed sprite.");
			return false;
		}

		return pimpl_->texture != nullptr;
	}

	void Sprite::use_full_region() {
		if (!is_valid()) {
			PF_LOG_WARNING("clear_texture() called on an uninitialized or destroyed sprite.");
			return; // can't access a function with a NULL pointer
		}

		pimpl_->texture_region = penguin::math::Rect2{ 0.0f, 0.0f, static_cast<float>(pimpl_->size.x), static_cast<float>(pimpl_->size.y) };
	}

	void Sprite::use_default_screen_placement() {
		if (!is_valid()) {
			PF_LOG_WARNING("clear_texture() called on an uninitialized or destroyed sprite.");
			return; // can't access a function with a NULL pointer
		}

		pimpl_->screen_placement = penguin::math::Rect2{ 0.0f, 0.0f, static_cast<float>(pimpl_->size.x), static_cast<float>(pimpl_->size.y) };
	}

	NativeTexturePtr Sprite::get_native_ptr() const {
		if (!is_valid()) {
			PF_LOG_WARNING("get_native_ptr() called on an uninitialized or destroyed texture.");
			return NativeTexturePtr{ nullptr }; // indicates that the underlying native pointer cannot be accessed
		}

		return pimpl_->get_native_ptr();
	}
}




