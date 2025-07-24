#include <penguin_framework/rendering/systems/asset_manager.hpp>
#include <rendering/systems/internal/asset_manager_impl.hpp>
#include <penguin_framework/logger/logger.hpp>

namespace penguin::rendering::systems {

	// Assumes that NativeRendererPtr contains a valid renderer_ptr
	AssetManager::AssetManager(const rendering::Renderer& renderer) : pimpl_(nullptr) {
		// Log attempt to create asset loader
		PF_LOG_INFO("Attempting to create asset manager...");

		if (renderer.is_valid()) {
			try {
				pimpl_ = std::make_unique<penguin::internal::rendering::systems::AssetManagerImpl>(renderer.get_native_ptr());
				PF_LOG_INFO("Success: AssetManager created successfully.");
			}
			catch (const penguin::internal::error::InternalError& e) {
				// Get the error code and message
				std::string error_code_str = penguin::internal::error::error_code_to_string(e.get_error());
				std::string error_message = error_code_str + ": " + e.what();

				// Log the error
				PF_LOG_ERROR(error_message.c_str());

			}
			catch (const std::exception& e) { // Other specific C++ errors
				// Get error message
				std::string last_error_message = e.what();
				std::string error_message = "Unknown_Error: " + error_message;

				// Log the error
				PF_LOG_ERROR(error_message.c_str());
			}
		}
		else {
			PF_LOG_ERROR("Asset_Manager_Init_Failed: The renderer is null or has not been initialized.");
		}
	}
		
	AssetManager::~AssetManager() = default;

	// Validity checking

	bool AssetManager::is_valid() const noexcept {
		if (!pimpl_) {
			return false;
		}

		return pimpl_->texture_loader.is_valid() && pimpl_->renderer_ptr.ptr;
	}

	AssetManager::operator bool() const noexcept {
		return is_valid();
	}

	std::shared_ptr<primitives::Texture> AssetManager::load_texture(const char* path) {
		if (!is_valid()) {
			PF_LOG_WARNING("load_texture() called on an uninitialized or destroyed asset manager.");
			return nullptr;
		}

		return pimpl_->load_texture(path);
	}

	std::shared_ptr<primitives::Font> AssetManager::load_font(const char* path, float size, int outline) {
		if (!is_valid()) {
			PF_LOG_WARNING("load_font() called on an uninitialized or destroyed asset manager.");
			return nullptr;
		}

		return pimpl_->load_font(path, size, outline);
	}
}

