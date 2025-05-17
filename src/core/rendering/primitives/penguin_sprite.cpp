#include <penguin_framework/core/rendering/primitives/penguin_sprite.hpp>
#include <penguin_framework/core/rendering/primitives/penguin_sprite_impl.hpp>

// --- Define SpriteImpl Methods ---

using penguin::core::rendering::primitives::Sprite;
using penguin::core::rendering::primitives::SpriteImpl;
using penguin::core::rendering::primitives::Texture;
using penguin::core::rendering::primitives::FlipMode;

SpriteImpl::SpriteImpl(std::shared_ptr<Texture> p_texture, Vector2 p_position, Vector2 p_scale,
	Vector2 p_anchor_point, float p_angle, bool p_visible, FlipMode p_mode, Colour p_tint) {
	size = p_texture.get()->get_size();
	position = p_position;
	scale = p_scale;
	anchor_point = p_anchor_point;
	angle = p_angle;
	visible = p_visible;
	mode = p_mode;
	tint = p_tint;
	bounding_box = Rect2(position.x, position.y, size.x, size.y); // setting bounding box initially
}

NativeTexturePtr SpriteImpl::get_native_ptr() const {
    return texture->get_native_ptr();
}

Vector2 SpriteImpl::get_position() const {
	return position;
}

Vector2i SpriteImpl::get_size() const {
	return size;
}

Vector2 SpriteImpl::get_scale() const {
	return scale;
}

float SpriteImpl::get_angle() const {
	return angle;
}

Vector2 SpriteImpl::get_anchor_point() const {
	return anchor_point;
}

bool SpriteImpl::is_hidden() const {
	return visible;
}

FlipMode SpriteImpl::get_flip_mode() const {
	return mode;
}

Colour SpriteImpl::get_colour_tint() const {
	return tint;
}

Rect2 SpriteImpl::get_bounding_box() const {
	return bounding_box;
}

void SpriteImpl::set_texture(std::shared_ptr<Texture> new_texture) {
	texture = new_texture;
}

void SpriteImpl::set_position(Vector2 new_position) {
	position = new_position;
}

void SpriteImpl::set_scale(Vector2 new_scale) {
	scale = new_scale;
}

void SpriteImpl::set_angle(float new_angle) {
	angle = new_angle;
}

void SpriteImpl::set_anchor_point(Vector2 new_anchor_point) {
	anchor_point = new_anchor_point;
}

void SpriteImpl::show() {
	visible = true;
}

void SpriteImpl::hide() {
	visible = false;
}

void SpriteImpl::set_flip_mode(FlipMode new_mode) {
	mode = mode;
}

void SpriteImpl::set_colour_tint(Colour new_tint) {
	tint = new_tint;
}

void SpriteImpl::set_bounding_box(Rect2 new_bounding_box) {
	bounding_box = new_bounding_box;
}

// --- Define Sprite Methods ---

Sprite::Sprite(std::shared_ptr<Texture> tex, Vector2 position, Vector2 scale, Vector2 anchor_point,
	float angle, bool visible, FlipMode mode, Colour modulate) : pimpl_(std::make_unique<SpriteImpl>(tex, position, scale, anchor_point, angle, visible, mode, modulate)) {}
Sprite::~Sprite() = default;

Sprite::Sprite(Sprite&&) noexcept = default;
Sprite& Sprite::operator=(Sprite&&) noexcept = default;

// --- Getters ---

NativeTexturePtr Sprite::get_native_ptr() const { return pimpl_->get_native_ptr(); }

Vector2 Sprite::get_position() const { return pimpl_->get_position(); }
Vector2i Sprite::get_size() const { return pimpl_->get_size(); }
Vector2 Sprite::get_scale() const { return pimpl_->get_scale(); }
float Sprite::get_angle() const { return pimpl_->get_angle(); }
Vector2 Sprite::get_anchor_point() const { return pimpl_->get_anchor_point(); }
bool Sprite::is_hidden() const { return pimpl_->is_hidden(); }
FlipMode Sprite::get_flip_mode() const { return pimpl_->get_flip_mode(); }
Colour Sprite::get_colour_tint() const { return pimpl_->get_colour_tint(); }
Rect2 Sprite::get_bounding_box() const { return pimpl_->get_bounding_box(); }

// --- Setters ---

void Sprite::set_texture(std::shared_ptr<Texture> texture) { pimpl_->set_texture(texture); }
void Sprite::set_position(Vector2 new_position) { pimpl_->set_position(new_position); }
void Sprite::set_position(float x, float y) { pimpl_->set_position(Vector2(x, y)); }
void Sprite::set_scale(Vector2 new_scale) { pimpl_->set_scale(new_scale); }
void Sprite::set_scale(float x, float y) { pimpl_->set_scale(Vector2(x, y)); }
void Sprite::set_angle(float new_angle) { pimpl_->set_angle(new_angle); }
void Sprite::set_anchor_point(Vector2 new_anchor_point) { pimpl_->set_anchor_point(new_anchor_point); }
void Sprite::set_anchor_point(float x, float y) { pimpl_->set_anchor_point(Vector2(x, y)); }
void Sprite::show() { pimpl_->show(); }
void Sprite::hide() { pimpl_->hide(); }
void Sprite::set_flip_mode(FlipMode new_mode) { pimpl_->set_flip_mode(new_mode); }
void Sprite::set_colour_tint(Colour new_modulate) { pimpl_->set_colour_tint(new_modulate); }
void Sprite::set_bounding_box(Rect2 new_bounding_box) { pimpl_->set_bounding_box(new_bounding_box); }

// --- Collision detection ---

bool Sprite::intersects(const Sprite& other) const {
	return pimpl_->get_bounding_box().intersects(other.get_bounding_box());
}
