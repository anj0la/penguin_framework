#include <penguin_framework/rendering/primitives/font.hpp>
#include <rendering/primitives/internal/font_impl.hpp>
#include <penguin_framework/logger/logger.hpp>

namespace penguin::rendering::primitives {

	Font::Font(const char* path, float size, int outline) : pimpl_(nullptr) {

		// Log attempt to create a sprite
		PF_LOG_INFO("Attempting to create font...");

		try {
			pimpl_ = std::make_unique<penguin::internal::rendering::primitives::FontImpl>(path, size, outline);
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
			PF_LOG_WARNING("get_size() called on an uninitialized or destroyed font.");
			return 0.0f;
		}

		return pimpl_->size;
	}

	int Font::get_outline() {
		if (!is_valid()) {
			PF_LOG_WARNING("get_outline() called on an uninitialized or destroyed font.");
			return 0;
		}

		return pimpl_->outline;
	}

	void Font::set_size(float new_size) {
		if (!is_valid()) {
			PF_LOG_WARNING("set_size() called on an uninitialized or destroyed font.");
			return;
		}

		pimpl_->size = new_size;
	}

	void Font::set_outline(int new_outline) {
		if (!is_valid()) {
			PF_LOG_WARNING("set_outline() called on an uninitialized or destroyed font.");
			return;
		}

		pimpl_->outline = new_outline;
	}

	void Font::make_normal() {
		if (!is_valid()) {
			PF_LOG_WARNING("make_normal() called on an uninitialized or destroyed font.");
			return;
		}

		pimpl_->make_normal();
	}

	void Font::make_bold() {
		if (!is_valid()) {
			PF_LOG_WARNING("make_bold() called on an uninitialized or destroyed font.");
			return;
		}

		pimpl_->make_bold();
	}

	void Font::make_italic() {
		if (!is_valid()) {
			PF_LOG_WARNING("make_italic() called on an uninitialized or destroyed font.");
			return;
		}

		pimpl_->make_italic();
	}

	void Font::make_underline() {
		if (!is_valid()) {
			PF_LOG_WARNING("make_underline() called on an uninitialized or destroyed font.");
			return;
		}

		pimpl_->make_underline();
	}

	void Font::make_strikethrough() {
		if (!is_valid()) {
			PF_LOG_WARNING("make_strikethrough() called on an uninitialized or destroyed font.");
			return;
		}

		pimpl_->make_strikethrough();
	}

	bool Font::is_bold() const {
		if (!is_valid()) {
			PF_LOG_WARNING("is_bold() called on an uninitialized or destroyed font.");
			return false;
		}

		return pimpl_->bold;
	}

	bool Font::is_italic() const {
		if (!is_valid()) {
			PF_LOG_WARNING("is_italic() called on an uninitialized or destroyed font.");
			return false;
		}

		return pimpl_->italic;
	}

	bool Font::is_underline() const {
		if (!is_valid()) {
			PF_LOG_WARNING("is_underline() called on an uninitialized or destroyed font.");
			return false;
		}

		return pimpl_->underline;
	}

	bool Font::is_strikethrough() const {
		if (!is_valid()) {
			PF_LOG_WARNING("is_strikethrough() called on an uninitialized or destroyed font.");
			return false;
		}

		return pimpl_->strikethrough;
	}

	bool Font::is_normal() const {
		if (!is_valid()) {
			PF_LOG_WARNING("is_normal() called on an uninitialized or destroyed font.");
			return false;
		}

		return pimpl_->normal;
	}

	void Font::clear() {
		if (!is_valid()) {
			PF_LOG_WARNING("clear() called on an uninitialized or destroyed font.");
			return;
		}

		pimpl_->make_normal();
	}

	NativeFontPtr Font::get_native_ptr() {
		if (!is_valid()) {
			PF_LOG_WARNING("get_native_ptr() called on an uninitialized or destroyed font.");
			return NativeFontPtr{ nullptr };
		}

		return NativeFontPtr{ pimpl_->font.get() };
	}
}