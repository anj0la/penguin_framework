#include <rendering/primitives/internal/texture_impl.hpp>

namespace penguin::internal::rendering::primitives {

	TextureImpl::TextureImpl(NativeRendererPtr ptr, const char* path) : texture(nullptr, &SDL_DestroyTexture) {
		SDL_Surface* surface = SDL_LoadBMP(path);

		texture.reset(
			SDL_CreateTextureFromSurface(ptr.as<SDL_Renderer>(), surface)
		);

		SDL_DestroySurface(surface);

		penguin::internal::error::InternalError::throw_if(
			!texture,
			"Failed to create the texture.",
			penguin::internal::error::ErrorCode::Texture_Creation_Failed
		);

		size.x = texture->w;
		size.y = texture->h;
	}
}