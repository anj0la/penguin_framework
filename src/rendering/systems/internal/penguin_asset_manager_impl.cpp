#include <rendering/systems/internal/penguin_asset_manager_impl.hpp>

namespace penguin::internal::rendering::systems {

	AssetManagerImpl::AssetManagerImpl(NativeRendererPtr renderer) : renderer_ptr(renderer) {}

	std::shared_ptr<penguin::rendering::primitives::Texture> AssetManagerImpl::load(const char* path) {
		if (!std::filesystem::exists(path)) {
			return nullptr; // Return nullptr as path doesn't exist
		}

		return texture_loader.load(renderer_ptr, path); // valid path, get the Texture
	}
}

