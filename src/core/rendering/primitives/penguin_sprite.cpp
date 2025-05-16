#include <penguin_framework/core/rendering/penguin_sprite.hpp>
#include <penguin_framework/core/rendering/penguin_sprite_impl.hpp>

// --- Define SpriteImpl Methods ---

using penguin::core::rendering::primitives::Sprite;
using penguin::core::rendering::primitives::SpriteImpl;
using penguin::core::rendering::primitives::Texture;
using penguin::core::rendering::primitives::FlipMode;

SpriteImpl::SpriteImpl(std::shared_ptr<Texture> tex) :texture(tex) {
	size = tex.get()->get_size();
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

Rect2 SpriteImpl::get_bounding_box() const {
	return bounding_box;
}

void SpriteImpl::set_texture(std::shared_ptr<Texture> tex) {
	texture = tex;
}

void SpriteImpl::set_position(Vector2 new_pos) {
	position = new_pos;
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
void SpriteImpl::set_bounding_box(Rect2 bound_box) {
	bounding_box = bound_box;
}

// --- Define Sprite Methods ---

Sprite::Sprite(std::shared_ptr<Texture> tex) : pimpl_(std::make_unique<SpriteImpl>(tex)) {}
Sprite::~Sprite() = default;

Sprite::Sprite(Sprite&&) noexcept = default;
Sprite& Sprite::operator=(Sprite&&) noexcept = default;

// --- Getters ---

NativeTexturePtr Sprite::get_native_ptr() const { return pimpl_->get_native_ptr(); }

Vector2 Sprite::get_position() const { return pimpl_->get_position(); }
Vector2i Sprite::get_size() const { return pimpl_->get_size(); }
float Sprite::get_angle() const { return pimpl_->get_angle(); }
Vector2 Sprite::get_anchor_point() const { return pimpl_->get_anchor_point(); }
bool Sprite::is_hidden() const { return pimpl_->is_hidden(); }
FlipMode Sprite::get_flip_mode() const { return pimpl_->get_flip_mode(); }
Rect2 Sprite::get_bounding_box() const { return pimpl_->get_bounding_box(); }

// --- Setters ---

void Sprite::set_texture(std::shared_ptr<Texture> texture) { pimpl_->set_texture(texture); }
void Sprite::set_position(Vector2 new_pos) { pimpl_->set_position(new_pos); }
void Sprite::set_position(float x, float y) { pimpl_->set_position(Vector2(x, y)); }
void Sprite::set_angle(float new_angle) { pimpl_->set_angle(new_angle); }
void Sprite::set_anchor_point(Vector2 new_anchor_point) { pimpl_->set_anchor_point(new_anchor_point); }
void Sprite::set_anchor_point(float x, float y) { pimpl_->set_anchor_point(Vector2(x, y)); }
void Sprite::show() { pimpl_->show(); }
void Sprite::hide() { pimpl_->hide(); }
void Sprite::set_flip_mode(FlipMode new_mode) { pimpl_->set_flip_mode(new_mode); }
void Sprite::set_bounding_box(Rect2 bound_box) { pimpl_->set_bounding_box(bound_box); }

// --- Collision detection ---

bool Sprite::intersects(const Sprite& other) const {
	return pimpl_->get_bounding_box().intersects(other.get_bounding_box());
}
