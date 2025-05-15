#include <penguin_framework/core/rendering/systems/penguin_asset_manager.hpp>
#include <penguin_framework/core/rendering/systems/penguin_asset_manager_impl.hpp>

// --- Define AssetManagerImpl Methods ---

using penguin::core::rendering::systems::AssetManager;
using penguin::core::rendering::systems::AssetManagerImpl;
using penguin::core::rendering::primitives::Texture;

AssetManagerImpl::AssetManagerImpl(NativeRendererPtr renderer) : renderer_ptr(renderer) {}

std::shared_ptr<Texture> AssetManagerImpl::load(const char* path) {
	if (!std::filesystem::exists(path)) {
		return nullptr; // Return nullptr as path doesn't exist
	}

	return texture_loader.load(renderer_ptr, path); // valid path, get the Texture
}

// --- Define AssetManager Methods ---

AssetManager::AssetManager(NativeRendererPtr renderer_ptr) : pimpl_(std::make_unique<AssetManagerImpl>(renderer_ptr)) {}
AssetManager::~AssetManager() = default;

// --- Loading Functions ---

std::shared_ptr<Texture> AssetManager::load(const char* path) {
	return pimpl_->load(path);
}
