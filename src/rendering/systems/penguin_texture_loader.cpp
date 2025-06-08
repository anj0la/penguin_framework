#include <penguin_framework/rendering/systems/penguin_texture_loader.hpp>
#include <rendering/systems/internal/penguin_texture_loader_impl.hpp>
#include <penguin_framework/logger/logger.hpp>

namespace penguin::rendering::systems {

	TextureLoader::TextureLoader() : pimpl_(nullptr), valid_state_(false) {

		// Log attempt to create a sprite
		PF_LOG_INFO("Attempting to create texture loader...");

		try {
			pimpl_ = std::make_unique<penguin::internal::rendering::systems::TextureLoaderImpl>();
			valid_state_ = true;
			PF_LOG_INFO("Success: TextureLoader created successfully.");
		}
		catch (const penguin::internal::error::InternalError& e) {
			// Get the error code and message
			std::string error_code_str = penguin::internal::error::error_code_to_string(e.get_error());
			std::string error_message = e.what();
			std::string error_message = error_code_str + ": " + error_message;

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

	TextureLoader::~TextureLoader() = default;

	// Validity checking

	bool TextureLoader::is_valid() const noexcept { return valid_state_; }
	TextureLoader::operator bool() const noexcept { return is_valid(); }

	std::shared_ptr<penguin::rendering::primitives::Texture> TextureLoader::load(NativeRendererPtr renderer, const char* path) {
		if (!is_valid()) {
			PF_LOG_WARNING("load() called on an uninitialized or destroyed texture loader.");
			return nullptr;
		}

		return pimpl_->load(renderer, path);
	}
}
