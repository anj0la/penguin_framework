#include <penguin_framework/core/rendering/assets/penguin_asset_loader.hpp>
#include <penguin_framework/core/rendering/assets/penguin_asset_loader_impl.hpp>

// --- Define AssetLoaderImpl ---

using penguin::core::rendering::assets::AssetLoader;
using penguin::core::rendering::assets::Texture;

AssetLoader::AssetLoaderImpl::AssetLoaderImpl(NativeRendererPtr renderer) : ptr(renderer) {}

Texture AssetLoader::AssetLoaderImpl::load(const char* path) {
	// NOTE: Update to use the IMG_Load function to directly create a texture
	// std::unique_ptr <SDL_Texture, void(*)(SDL_Texture*)> texture(IMG_LoadTexture(ptr.as<SDL_Renderer>(), path), &SDL_DestroyTexture);

	// Create the texture (moving ownership of the SDL texture to the Texture class
	Texture texture(ptr, path);

	// Create the Sprite -> don't create the texture on your own

	return texture;
}
