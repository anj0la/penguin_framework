#include <penguin_framework/rendering/primitives/penguin_sprite.hpp>
#include <rendering/primitives/internal/penguin_sprite_impl.hpp>
#include <penguin_framework/logger/logger.hpp>

namespace penguin::rendering::primitives {

	Sprite::Sprite(std::shared_ptr<Texture> p_texture)
		: pimpl_(nullptr), valid_state_(false) {

		// Log attempt to create a sprite
		std::string message = "Attempting to create sprite...";
		PF_LOG_INFO(message.c_str());

		try {
			pimpl_ = std::make_unique<penguin::internal::rendering::primitives::SpriteImpl>(p_texture);
			valid_state_ = true;
		}
		catch (const penguin::internal::error::InternalError& e) {
			// Get the error code and message
			std::string error_code_str = penguin::internal::error::error_code_to_string(e.get_error());
			std::string error_message = e.what();
			std::string error_message = error_code_str + ": " + error_message;

			// Log the error
			PF_LOG_ERROR(error_message.c_str());

		}
		catch (const std::exception& e) { // Other specific C++ errors
			// Get error message
			std::string last_error_message = e.what();
			std::string error_message = "Unknown: " + error_message;

			// Log the error
			PF_LOG_ERROR(error_message.c_str());
		}
	}

	Sprite::~Sprite() = default;

	Sprite::Sprite(Sprite&&) noexcept = default;
	Sprite& Sprite::operator=(Sprite&&) noexcept = default;

	// Validity checking

	bool Sprite::is_valid() const noexcept {
		return valid_state_;
	}

	explicit Sprite::operator bool() const noexcept {
		return is_valid();
	}

	// Getters

	NativeTexturePtr Sprite::get_native_ptr() const {
		return pimpl_->get_native_ptr();
	}

	penguin::math::Vector2 Sprite::get_position() const {
		return pimpl_->position;
	}

	Vector2i Sprite::get_size() const {
		return pimpl_->get_size();
	}

	Vector2 Sprite::get_scale() const {
		return pimpl_->get_scale();
	}

	double Sprite::get_angle() const {
		return pimpl_->get_angle();
	}

	Vector2 Sprite::get_anchor_point() const {
		return pimpl_->get_anchor_point();
	}

	bool Sprite::is_hidden() const {
		return pimpl_->is_hidden();
	}

	FlipMode Sprite::get_flip_mode() const {
		return pimpl_->get_flip_mode();
	}

	Colour Sprite::get_colour_tint() const {
		return pimpl_->get_colour_tint();
	}

	Rect2 Sprite::get_bounding_box() const {
		return pimpl_->get_bounding_box();
	}

	// Setters

	void Sprite::set_texture(std::shared_ptr<Texture> texture) {
		pimpl_->set_texture(texture);
	}

	void Sprite::set_position(Vector2 new_position) {
		pimpl_->set_position(new_position);
	}

	void Sprite::set_position(float x, float y) {
		pimpl_->set_position(Vector2(x, y));
	}

	void Sprite::set_scale(Vector2 new_scale_factor) {
		pimpl_->set_scale(new_scale_factor);
	}
	void Sprite::set_scale(float x, float y) {
		pimpl_->set_scale(Vector2(x, y));
	}

	void Sprite::set_angle(double new_angle) {
		pimpl_->set_angle(new_angle);
	}

	void Sprite::set_anchor_point(Vector2 new_center) {
		pimpl_->set_anchor_point(new_center);
	}

	void Sprite::set_anchor_point(float x, float y) {
		pimpl_->set_anchor_point(Vector2(x, y));
	}

	void Sprite::show() {
		pimpl_->show();
	}

	void Sprite::hide() {
		pimpl_->hide();
	}

	void Sprite::set_flip_mode(FlipMode new_mode) {
		pimpl_->set_flip_mode(new_mode);
	}

	void Sprite::set_colour_tint(Colour new_modulate) {
		pimpl_->set_colour_tint(new_modulate);
	}

	void Sprite::set_bounding_box(Rect2 new_bounding_box) {
		pimpl_->set_bounding_box(new_bounding_box);
	}

	// Collision detection

	bool Sprite::intersects(const Sprite& other) const {
		return pimpl_->get_bounding_box().intersects(other.get_bounding_box());
	}

}




