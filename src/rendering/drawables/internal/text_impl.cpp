#include <rendering/drawables/internal/text_impl.hpp>

namespace penguin::internal::rendering::drawables {

    TextImpl::TextImpl(NativeTextContextPtr text_renderer_ptr, NativeFontPtr font,
        const char* p_str, penguin::math::Colour p_colour, penguin::math::Vector2 p_position)
    : text(TTF_CreateText(text_renderer_ptr.as<TTF_TextEngine>(), font.as<TTF_Font>(), p_str, 0), &TTF_DestroyText) {
        penguin::internal::error::InternalError::throw_if(
            !text,
            "Failed to create the text.",
            penguin::internal::error::ErrorCode::Text_Creation_Failed
        );

        str = p_str; 
        colour = p_colour;
        position = p_position;
    }

}