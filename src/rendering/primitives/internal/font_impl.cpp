#include <rendering/primitives/internal/font_impl.hpp>
#include <string>

namespace penguin::internal::rendering::primitives {

    FontImpl::FontImpl(const char* path, float p_size, int p_outline) : font(TTF_OpenFont(path, p_size), &TTF_CloseFont) {
        penguin::internal::error::InternalError::throw_if(
            !font,
            "Failed to create the font.",
            penguin::internal::error::ErrorCode::Font_Creation_Failed
        );

        size = p_size;
        outline = p_outline;
        applied_styles = TTF_STYLE_NORMAL;
    }

    void FontImpl::add_style(penguin::rendering::primitives::FontStyle style_flags) {
        applied_styles |= static_cast<TTF_FontStyleFlags>(style_flags);
        TTF_SetFontStyle(font.get(), applied_styles);
    }

    void FontImpl::remove_style(penguin::rendering::primitives::FontStyle style_flags) {
        applied_styles &= ~static_cast<TTF_FontStyleFlags>(style_flags);
        TTF_SetFontStyle(font.get(), applied_styles);
    }

    void FontImpl::replace_style(penguin::rendering::primitives::FontStyle style_flag) {
        applied_styles = static_cast<TTF_FontStyleFlags>(style_flag);
        TTF_SetFontStyle(font.get(), applied_styles);
    }

    const char* FontImpl::get_styles() const {
        int bitmask = TTF_GetFontStyle(font.get());
        return style_names[bitmask];
    }

}