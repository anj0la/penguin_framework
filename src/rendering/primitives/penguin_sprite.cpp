#include <penguin_framework/core/rendering/primitives/penguin_sprite.hpp>
#include <penguin_framework/core/rendering/primitives/penguin_sprite_impl.hpp>

// Define SpriteImpl Methods

using penguin::core::rendering::primitives::Sprite;
using penguin::core::rendering::primitives::SpriteImpl;
using penguin::core::rendering::primitives::Texture;
using penguin::core::rendering::primitives::FlipMode;

SpriteImpl::SpriteImpl(std::shared_ptr<Texture> p_texture) : texture(std::move(p_texture)) {
	position = Vector2::Zero; // the top-left corner represents the position of the Sprite
	size = p_texture.get()->get_size();
	texture_region = Rect2{ position.x, position.y, size.x, size.y }; // position -> (0,0), size -> (texture_width, texture_height) for the full texture
	screen_placement = Rect2{ position.x, position.y, size.x, size.y };
	scale_factor = Vector2::One;
	angle = 0.0;
	anchor = Vector2{ 0.5f, 0.5f }; // center
	visible = true;
	mode = FlipMode::None;
	tint = Colours::NoTint;
	bounding_box = Rect2{ position.x, position.y, size.x, size.y }; // initally the size of the texture
}

// Getters

NativeTexturePtr SpriteImpl::get_native_ptr() const {
    return texture->get_native_ptr();
}

Vector2 SpriteImpl::get_position() const {
	return position;
}

Vector2i SpriteImpl::get_size() const {
	return size;
}

Rect2 SpriteImpl::get_texture_region() const {
	return texture_region;
}

Rect2 SpriteImpl::get_screen_placement() const {
	return screen_placement;
}

Vector2 SpriteImpl::get_scale() const {
	return scale_factor;
}

double SpriteImpl::get_angle() const {
	return angle;
}

Vector2 SpriteImpl::get_anchor() const {
	return anchor;
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

// Setters

void SpriteImpl::set_texture(std::shared_ptr<Texture> new_texture) {
	texture = std::move(new_texture);
	size = new_texture.get()->get_size();
}

void SpriteImpl::set_position(const Vector2& new_position) {
	position = new_position;  
}

void SpriteImpl::set_texture_region(const Rect2& new_region) {
	texture_region = new_region;
}

void SpriteImpl::set_screen_placement(const Rect2& new_placement) {
	screen_placement = new_placement;
}

void SpriteImpl::set_scale(const Vector2& new_scale_factor) {
	scale_factor = new_scale_factor;
}

void SpriteImpl::set_angle(double new_angle) {
	angle = new_angle;
}

void SpriteImpl::set_anchor(const Vector2& new_anchor) {
	anchor = std::clamp(new_anchor, Vector2::Zero, Vector2::One); // clamp between (0.0, 0.0) and (1.0, 1.0)
}

void SpriteImpl::show() {
	visible = true;
}

void SpriteImpl::hide() {
	visible = false;
}

void SpriteImpl::set_flip_mode(const FlipMode& new_mode) {
	mode = new_mode;
}

void SpriteImpl::set_colour_tint(const Colour& new_tint) {
	tint = new_tint;
}

void SpriteImpl::set_bounding_box(const Rect2& new_bounding_box) {
	bounding_box = new_bounding_box;
}

// Other functions

void SpriteImpl::clear_texture() {
	texture.reset(); // makes texture null
	size = Vector2i::Zero;
}

bool SpriteImpl::has_texture() {
	return texture.get() != nullptr;
}
 
void SpriteImpl::use_full_region() {
	texture_region = Rect2{ 0.0f, 0.0f, size.x, size.y };
}

void SpriteImpl::use_default_screen_placement() {
	screen_placement = Rect2{ 0.0f, 0.0f, size.x, size.y };
}

void SpriteImpl::update_screen_placement() {
	// Texture is invalid, nothing should be rendered onto the screen
	if (!texture) {
		screen_placement = Rect2{ Vector2::Zero, Vector2::Zero };
		return;
	}

	// Otherwise, we update the screen placement with the position and scale_factor
	Vector2 base_size{ texture_region.size.x, texture_region.size.y };

	// Texture is valid, but the source portion defines a zero-area.
	if (base_size.x <= 0 || base_size.y <= 0) {
		screen_placement = Rect2{ Vector2::Zero, Vector2::Zero };
		return;
	}

	// Texture is valid, and the source portion defines a valid non-zero area.
	Vector2 scaled_size{ base_size.x * scale_factor.x, base_size.y * scale_factor.y };
	screen_placement = Rect2{ position, scaled_size };

	// Update the anchor point
	anchor = anchor * scaled_size; // anchor.x * scaled_size.x and anchor.y * scaled_size.y
}


// Define Sprite Methods

Sprite::Sprite(std::shared_ptr<Texture> tex, Vector2 position, Vector2 scale_factor,
	double angle, Vector2 anchor_point, bool visible, FlipMode mode, Colour modulate) : pimpl_(std::make_unique<SpriteImpl>(tex, position, scale_factor, angle, anchor_point, visible, mode, modulate)) {}
Sprite::~Sprite() = default;

Sprite::Sprite(Sprite&&) noexcept = default;
Sprite& Sprite::operator=(Sprite&&) noexcept = default;

// Getters

NativeTexturePtr Sprite::get_native_ptr() const { 
	return pimpl_->get_native_ptr(); 
}

Vector2 Sprite::get_position() const {
	return pimpl_->get_position(); 
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
