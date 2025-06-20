#include <penguin_framework/rendering/primitives/font.hpp>
#include <rendering/primitives/internal/font_impl.hpp>
#include <penguin_framework/logger/logger.hpp>

namespace penguin::rendering::primitives {

	Font::Font(const char* path, float size) : pimpl_(nullptr) {

		// Log attempt to create a sprite
		PF_LOG_INFO("Attempting to create font...");

		try {
			pimpl_ = std::make_unique<penguin::internal::rendering::primitives::FontImpl>(path, size);
			PF_LOG_INFO("Success: Font created successfully.");
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

	Font::~Font() = default;

	Font::Font(Font&&) noexcept = default;
	Font& Font::operator=(Font&&) noexcept = default;

	bool Font::is_valid() const noexcept {
		if (!pimpl_) {
			return false;
		}

		return pimpl_->font.get();
	}

	Font::operator bool() const noexcept {
		return is_valid();
	}

	float Font::get_size() {
		if (!is_valid()) {
			PF_LOG_WARNING("get_size() called on an uninitialized or destroyed sprite.");
			return 0.0f;
		}

		return pimpl_->size;
	}

	int Font::get_outline() {
		if (!is_valid()) {
			PF_LOG_WARNING("get_outline() called on an uninitialized or destroyed sprite.");
			return 0;
		}

		return pimpl_->outline;
	}

	const char* Font::get_styles() const {
		if (!is_valid()) {
			PF_LOG_WARNING("get_styles() called on an uninitialized or destroyed sprite.");
			return "";
		}

		return pimpl_->get_styles();
	}

	void Font::set_size(float new_size) {
		if (!is_valid()) {
			PF_LOG_WARNING("set_size() called on an uninitialized or destroyed sprite.");
			return;
		}

		pimpl_->size = new_size;
	}

	void Font::set_outline(int new_outline) {
		if (!is_valid()) {
			PF_LOG_WARNING("set_outline() called on an uninitialized or destroyed sprite.");
			return;
		}

		pimpl_->outline = new_outline;
	}

	void Font::add_style(FontStyle style) {
		if (!is_valid()) {
			PF_LOG_WARNING("add_style() called on an uninitialized or destroyed sprite.");
			return;
		}

		pimpl_->add_style(style);
	}

	void Font::remove_style(FontStyle style) {
		if (!is_valid()) {
			PF_LOG_WARNING("remove_style() called on an uninitialized or destroyed sprite.");
			return;
		}

		pimpl_->remove_style(style);
	}

	void Font::replace_style(FontStyle style) {
		if (!is_valid()) {
			PF_LOG_WARNING("override_style() called on an uninitialized or destroyed sprite.");
			return;
		}

		pimpl_->replace_style(style);
	}

	NativeFontPtr Font::get_native_ptr() {
		if (!is_valid()) {
			PF_LOG_WARNING("get_native_ptr() called on an uninitialized or destroyed sprite.");
			return NativeFontPtr{ nullptr };
		}

		return NativeFontPtr{ pimpl_->font.get() };
	}
}