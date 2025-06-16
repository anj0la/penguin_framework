#include <penguin_framework/rendering/systems/penguin_asset_manager.hpp>
#include <rendering/systems/internal/penguin_asset_manager_impl.hpp>

namespace penguin::rendering::systems {
	// Assumes that NativeRendererPtr contains a valid renderer_ptr
	AssetManager::AssetManager(NativeRendererPtr renderer_ptr) : pimpl_(std::make_unique<penguin::internal::rendering::systems::AssetManagerImpl>(renderer_ptr)) {}
	AssetManager::~AssetManager() = default;

	std::shared_ptr<primitives::Texture> AssetManager::load(const char* path) {
		return pimpl_->load(path);
	}
}

