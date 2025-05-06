#include <penguin_framework/core/rendering/assets/penguin_texture.hpp>
#include <penguin_framework/core/rendering/assets/penguin_texture_impl.hpp>

// --- Define TextureImpl ---

using penguin::core::rendering::assets::Texture;

// MOVE THE UNIQUE PTR FROM ASSETLOADER TO TEXTURE
Texture::TextureImpl::TextureImpl(std::unique_ptr <SDL_Texture, void(*)(SDL_Texture*)> image, const char* path) : img(std::move(image)) {
	size.x = img->w;
	size.y = img->h;
}

NativeTexturePtr Texture::get_native_ptr() const { return NativeTexturePtr{ pimpl_->img.get() }; }

/*

bool Image::ImageImpl::draw(SDL_Renderer* renderer) {
	return SDL_RenderTexture(renderer, img.get(), nullptr, nullptr);
}

bool Image::ImageImpl::draw(SDL_Renderer* renderer, Rect2 source) {
	SDL_FRect sdl_source{ source.position.x, source.position.y, source.size.x, source.size.y };
	return SDL_RenderTexture(renderer, img.get(), &sdl_source, nullptr);
}

bool Image::ImageImpl::draw(SDL_Renderer* renderer, Rect2 dest) {
	SDL_FRect sdl_dest{ dest.position.x, dest.position.y, dest.size.x, dest.size.y };
	return SDL_RenderTexture(renderer, img.get(), nullptr, &sdl_dest);
}

bool Image::ImageImpl::draw(SDL_Renderer* renderer, Rect2 source, Rect2 dest) {
	SDL_FRect sdl_source{ source.position.x, source.position.y, source.size.x, source.size.y };
	SDL_FRect sdl_dest{ dest.position.x, dest.position.y, dest.size.x, dest.size.y };
	return SDL_RenderTexture(renderer, img.get(), &sdl_source, &sdl_dest);
}*/