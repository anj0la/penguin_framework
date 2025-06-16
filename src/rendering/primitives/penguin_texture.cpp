#include <penguin_framework/rendering/primitives/penguin_texture.hpp>
#include <rendering/primitives/internal/penguin_texture_impl.hpp>
#include <penguin_framework/logger/logger.hpp>

namespace penguin::rendering::primitives {

	Texture::Texture(NativeRendererPtr renderer_ptr, const char* path) : pimpl_(nullptr), valid_state_(false) {
		// Log attempt to create a texture
		PF_LOG_INFO("Attempting to create a texture...");

		try {
			pimpl_ = std::make_unique<penguin::internal::rendering::primitives::TextureImpl>(renderer_ptr, path);
			valid_state_ = true;
			PF_LOG_INFO("Success: Texture created successfully.");
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

	Texture::~Texture() = default;

	Texture::Texture(Texture&&) noexcept = default;
	Texture& Texture::operator=(Texture&&) noexcept = default;


	// Validity checking

	bool Texture::is_valid() const noexcept {
		if (!pimpl_) {
			return false;
		}

		return pimpl_->texture.get(); // the internal texture may be invalid
	}
	explicit Texture::operator bool() const noexcept {
		return is_valid();
	}

	// Getters

	NativeTexturePtr Texture::get_native_ptr() const { 
		if (!is_valid()) {
			PF_LOG_WARNING("get_native_ptr() called on an uninitialized or destroyed texture.");
			return NativeTexturePtr{ nullptr }; // indicates that the underlying native pointer cannot be accessed
		}

		return NativeTexturePtr{ pimpl_->texture.get() };
	}

	penguin::math::Vector2i Texture::get_size() const { 
		if (!is_valid()) {
			PF_LOG_WARNING("get_size() called on an uninitialized or destroyed texture.");
		}
		return pimpl_->size;
	}
}
