#include <penguin_framework/core/rendering/penguin_sprite_impl.hpp>

// --- Define SpriteImpl ---

using penguin::core::rendering::primitives::Sprite;
using penguin::core::rendering::primitives::Texture;
using penguin::core::rendering::primitives::FlipMode;

Sprite::SpriteImpl::SpriteImpl(std::shared_ptr<Texture> tex) :texture(tex) {
	size = tex.get()->get_size();
}

NativeTexturePtr Sprite::SpriteImpl::get_native_ptr() const {
    return texture ? texture->get_native_ptr() : NativeTexturePtr{ nullptr }; // if no texture is associated with the sprite, return nullptr (SDL call should fail)
}

Vector2 Sprite::SpriteImpl::get_position() const {
	return position;
}

Vector2i Sprite::SpriteImpl::get_size() const {
	return size;
}

float Sprite::SpriteImpl::get_angle() const {
	return angle;
}

Vector2 Sprite::SpriteImpl::get_anchor_point() const {
	return anchor_point;
}

bool Sprite::SpriteImpl::is_hidden() const {
	return visible;
}

FlipMode Sprite::SpriteImpl::get_flip_mode() const {
	return mode;
}

Rect2 Sprite::SpriteImpl::get_bounding_box() const {
	return bounding_box;
}

// Setters

void Sprite::SpriteImpl::set_texture(std::shared_ptr<Texture> tex) {
	texture = tex;
}

void Sprite::SpriteImpl::set_position(Vector2 new_pos) {
	position = new_pos;
}

void Sprite::SpriteImpl::set_position(float x, float y) {
	position = Vector2(x, y);
}

void Sprite::SpriteImpl::set_angle(float new_angle) {
	angle = new_angle;
}

void Sprite::SpriteImpl::set_anchor_point(Vector2 new_anchor_point) {
	anchor_point = new_anchor_point;
}

void Sprite::SpriteImpl::set_anchor_point(float x, float y) {
	anchor_point = Vector2(x, y);
}

void Sprite::SpriteImpl::show() {
	visible = true;
}

void Sprite::SpriteImpl::hide() {
	visible = false;
}

void Sprite::SpriteImpl::set_flip_mode(FlipMode new_mode) {
	mode = mode;
}
void Sprite::SpriteImpl::set_bounding_box(Rect2 bound_box) {
	bounding_box = bound_box;
}

// --- Define Sprite ---

Sprite::Sprite(std::shared_ptr<Texture> tex) : pimpl_(std::make_unique<SpriteImpl>(tex)) {}

Sprite::~Sprite() = default;