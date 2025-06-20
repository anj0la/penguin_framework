#include <rendering/primitives/internal/texture_impl.hpp>
#include <SDL3_image/SDL_image.h>

namespace penguin::internal::rendering::primitives {

	TextureImpl::TextureImpl(NativeRendererPtr ptr, const char* path) : texture(IMG_LoadTexture(ptr.as<SDL_Renderer>(), path), &SDL_DestroyTexture) {
		penguin::internal::error::InternalError::throw_if(
			!texture,
			"Failed to create the texture.",
			penguin::internal::error::ErrorCode::Texture_Creation_Failed
		);

		size.x = texture->w;
		size.y = texture->h;
	}
}
