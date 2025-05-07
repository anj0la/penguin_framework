#include <penguin_framework/core/rendering/assets/penguin_texture.hpp>
#include <penguin_framework/core/rendering/assets/penguin_texture_impl.hpp>

// --- Define TextureImpl ---

using penguin::core::rendering::assets::Texture;

Texture::TextureImpl::TextureImpl(NativeRendererPtr ptr, const char* path) : texture(nullptr, &SDL_DestroyTexture) {
	SDL_Surface* surface = SDL_LoadBMP(path);

	texture.reset(
		SDL_CreateTextureFromSurface(ptr.as<SDL_Renderer>(), surface)
	);

	SDL_DestroySurface(surface);

	size.x = texture->w;
	size.y = texture->h;
}

// --- Define Texture ---

Texture::Texture(NativeRendererPtr renderer, const char* path) : pimpl_(std::make_unique<TextureImpl>(renderer, path)) {}

NativeTexturePtr Texture::get_native_ptr() const { return NativeTexturePtr{ pimpl_->texture.get() }; }

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