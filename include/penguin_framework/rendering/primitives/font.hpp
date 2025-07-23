#pragma once

#include <penguin_api.hpp>

#include <penguin_framework/common/native_types.hpp>

#include <memory>

namespace penguin::internal::rendering::primitives {
    // Forward declaration
    struct FontImpl;
}

namespace penguin::rendering::primitives {

    class PENGUIN_API Font {
    public:
        Font(const char* path, float size = 12.0f, int outline = 1);
        ~Font();

        Font(Font&&) noexcept;
        Font& operator=(Font&&) noexcept;

        // Validity checking

        [[nodiscard]] bool is_valid() const noexcept;
        [[nodiscard]] explicit operator bool() const noexcept;

        float get_size();
        int get_outline();

        void set_size(float new_size);
        void set_outline(int new_outline);
    
        void make_normal();
        void make_bold();
        void make_italic();
        void make_underline();
        void make_strikethrough();

        bool is_bold() const;
        bool is_italic() const;
        bool is_underline() const;
        bool is_strikethrough() const;
        bool is_normal() const;

        void clear();

        NativeFontPtr get_native_ptr();

    private:
        std::unique_ptr<penguin::internal::rendering::primitives::FontImpl> pimpl_;
    };
}