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
        normal = true;
        bold = false;
        italic = false;
        underline = false;
        strikethrough = false;
    }
    
    void FontImpl::make_normal() {
        normal = true;
        bold = false;
        italic = false;
        underline = false;
        strikethrough = false;

        applied_styles = TTF_STYLE_NORMAL;
        TTF_SetFontStyle(font.get(), applied_styles);
    }

    void FontImpl::make_bold() {
        if (normal) {
            normal = false;
            applied_styles &= TTF_STYLE_NORMAL;
        }
        bold = true;

        applied_styles |= TTF_STYLE_BOLD;
        TTF_SetFontStyle(font.get(), applied_styles);
    }

    void FontImpl::make_italic() {
        if (normal) {
            normal = false;
            applied_styles &= TTF_STYLE_NORMAL;
        }
        italic = true;

        applied_styles |= TTF_STYLE_ITALIC;
        TTF_SetFontStyle(font.get(), applied_styles);
    }

    void FontImpl::make_underline() {
        if (normal) {
            normal = false;
            applied_styles &= TTF_STYLE_NORMAL;
        }
        underline = true;

        applied_styles |= TTF_STYLE_UNDERLINE;
        TTF_SetFontStyle(font.get(), applied_styles);
    }

    void FontImpl::make_strikethrough() {
        if (normal) {
            normal = false;
            applied_styles &= TTF_STYLE_NORMAL;
        }
        strikethrough = true;

        applied_styles |= TTF_STYLE_STRIKETHROUGH;
        TTF_SetFontStyle(font.get(), applied_styles);
    }

}