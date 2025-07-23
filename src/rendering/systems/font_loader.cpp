#include <penguin_framework/rendering/systems/font_loader.hpp>
#include <rendering/systems/internal/font_loader_impl.hpp>
#include <penguin_framework/logger/logger.hpp>

namespace penguin::rendering::systems {

	FontLoader::FontLoader() : pimpl_(nullptr) {

		// Log attempt to create a font loader
		PF_LOG_INFO("Attempting to create font loader...");

		try {
			pimpl_ = std::make_unique<penguin::internal::rendering::systems::FontLoaderImpl>();
			PF_LOG_INFO("Success: FontLoader created successfully.");
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

	FontLoader::~FontLoader() = default;

	// Validity checking

	bool FontLoader::is_valid() const noexcept {
		if (!pimpl_) {
			return false;
		}
		return true;
	}

	FontLoader::operator bool() const noexcept {
		return is_valid();
	}

	std::shared_ptr<penguin::rendering::primitives::Font> FontLoader::load(const char* path, float size, int outline) {
		if (!is_valid()) {
			PF_LOG_WARNING("load() called on an uninitialized or destroyed font loader.");
			return nullptr;
		}

		return pimpl_->load(path, size, outline);
	}
}
