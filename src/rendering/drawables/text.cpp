#include <penguin_framework/rendering/drawables/text.hpp>
#include <rendering/drawables/internal/text_impl.hpp>
#include <penguin_framework/logger/logger.hpp>

namespace penguin::rendering::drawables {

	Text::Text(const systems::TextContext& text_context, std::shared_ptr<penguin::rendering::primitives::Font> font,
		const char* str, penguin::math::Colour colour, penguin::math::Vector2 position) : pimpl_(nullptr) {

		// Log attempt to create a text
		PF_LOG_INFO("Attempting to create text...");

		if (font && text_context.is_valid()) { // If the font / text context is invalid, don't bother trying to create it
			try {
				pimpl_ = std::make_unique<penguin::internal::rendering::drawables::TextImpl>(text_context.get_native_ptr(), font->get_native_ptr(), str, colour, position);
				PF_LOG_INFO("Success: Text created successfully.");
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
			PF_LOG_ERROR("Text_Creation_Failed: The font and/or the text context are either null or have not been initialized.");
		}
	}

	Text::~Text() = default;

	Text::Text(Text&&) noexcept = default;
	Text& Text::operator=(Text&&) noexcept = default;

	bool Text::is_valid() const noexcept {
		if (!pimpl_) {
			return false;
		}

		return pimpl_->text.get();
	}

	Text::operator bool() const noexcept {
		return is_valid();
	}

	penguin::math::Vector2 Text::get_position() const {
		if (!is_valid()) {
			PF_LOG_WARNING("get_position() called on an uninitialized or destroyed text.");
			return penguin::math::Vector2::Zero;
		}

		return pimpl_->position;
	}

	penguin::math::Colour Text::get_colour() const {
		if (!is_valid()) {
			PF_LOG_WARNING("get_colour() called on an uninitialized or destroyed text.");
			return Colours::NoTint;
		}

		return pimpl_->colour;
	}

	const char* Text::get_string() const {
		if (!is_valid()) {
			PF_LOG_WARNING("get_string() called on an uninitialized or destroyed text.");
			return "";
		}

		return pimpl_->str.c_str();;
	}

	void Text::set_position(penguin::math::Vector2 new_position) {
		if (!is_valid()) {
			PF_LOG_WARNING("set_position() called on an uninitialized or destroyed text.");
			return;
		}

		pimpl_->position = new_position;
	}

	void Text::set_colour(penguin::math::Colour new_colour) {
		if (!is_valid()) {
			PF_LOG_WARNING("set_colour() called on an uninitialized or destroyed text.");
			return;
		}

		pimpl_->colour = new_colour;
	}

	void Text::set_string(const char* new_string) {
		if (!is_valid()) {
			PF_LOG_WARNING("set_string() called on an uninitialized or destroyed text.");
			return;
		}

		pimpl_->str = new_string;
	}

	NativeTextPtr Text::get_native_ptr() const {
		if (!is_valid()) {
			PF_LOG_WARNING("get_native_ptr() called on an uninitialized or destroyed text.");
			return NativeTextPtr{ nullptr };
		}

		return NativeTextPtr{ pimpl_->text.get() };
	}
}