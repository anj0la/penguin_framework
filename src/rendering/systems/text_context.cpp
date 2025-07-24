#include <penguin_framework/rendering/systems/text_context.hpp>
#include <rendering/systems/internal/text_context_impl.hpp>
#include <penguin_framework/logger/logger.hpp>

namespace penguin::rendering::systems {

	TextContext::TextContext(NativeRendererPtr renderer) : pimpl_(nullptr) {

		// Log attempt to create a sprite
		PF_LOG_INFO("Attempting to create text context...");

		if (renderer.ptr) {
			try {
				pimpl_ = std::make_unique<penguin::internal::rendering::systems::TextContextImpl>(renderer);
				PF_LOG_INFO("Success: Text Context created successfully.");
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
			PF_LOG_ERROR("Text_Context_Init_Failed: The renderer is null or has not been initialized.");
		}

	}

	TextContext::~TextContext() = default;

	bool TextContext::is_valid() const noexcept {
		if (!pimpl_) {
			return false;
		}

		return pimpl_->context.get();
	}

	TextContext::operator bool() const noexcept {
		return is_valid();
	}

	NativeTextContextPtr TextContext::get_native_ptr() const {
		if (!is_valid()) {
			PF_LOG_WARNING("get_native_ptr() called on an uninitialized or destroyed text context.");
			return NativeTextContextPtr{ nullptr };
		}

		return NativeTextContextPtr{ pimpl_->context.get() };
	}
}