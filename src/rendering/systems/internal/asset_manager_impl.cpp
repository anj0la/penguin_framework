#include <rendering/systems/internal/asset_manager_impl.hpp>

namespace penguin::internal::rendering::systems {

	AssetManagerImpl::AssetManagerImpl(NativeRendererPtr renderer) : renderer_ptr(renderer) {
		penguin::internal::error::InternalError::throw_if(
			!renderer_ptr.ptr,
			"Failed to initialize the asset manager.",
			penguin::internal::error::ErrorCode::Asset_Manager_Init_Failed
		);
	}

	std::shared_ptr<penguin::rendering::primitives::Texture> AssetManagerImpl::load(const char* path) {
		if (!std::filesystem::exists(path)) {
			return nullptr; // Return nullptr as path doesn't exist
		}

		// Check if file extension ends with the supported images: PNG, JPEG, BMP, etc. (impl later)
		if (!has_supported_image_ext(std::filesystem::path(path))) {
			return nullptr; // file image not supported
		}

		return texture_loader.load(renderer_ptr, path); // valid path, get the Texture
	}

	bool AssetManagerImpl::has_supported_image_ext(const std::filesystem::path& path) {
		std::string ext = path.extension().string();
		std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower); // make lowercase

		return std::find(supported.begin(), supported.end(), ext) != supported.end();
	}
}

