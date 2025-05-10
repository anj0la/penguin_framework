#include <penguin_framework/core/rendering/systems/penguin_asset_manager_impl.hpp>

// --- Define AssetManagerImpl ---

using penguin::core::rendering::systems::AssetManager;
using penguin::core::rendering::primitives::Texture;

AssetManager::AssetManagerImpl::AssetManagerImpl(NativeRendererPtr renderer) : renderer_ptr(renderer) {}

std::shared_ptr<Texture> AssetManager::AssetManagerImpl::load(const char* path) {
	return texture_loader.load(renderer_ptr, path); // call TextureLoader to handle loading texture
}

// --- Define AssetManager ---

AssetManager::AssetManager(NativeRendererPtr renderer_ptr) : pimpl_(std::make_unique<AssetManagerImpl>(renderer_ptr)) {}

AssetManager::~AssetManager() = default;

std::shared_ptr<Texture> AssetManager::load(const char* path) {
	return pimpl_->load(path);
}
