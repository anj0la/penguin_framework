#pragma once 

#include <cstdint>

namespace penguin::rendering::primitives {

	class FontStyles {
	public:
		FontStyles() = default;
		~FontStyles() = default;

		constexpr void make_normal() { normal = true; bold = false; italic = false; underline = false; strikethrough = false; }
		constexpr void make_bold() { normal = false; bold = true; }
		constexpr void make_italic() { normal = false; italic = true; }
		constexpr void make_underline() { normal = false; underline = true; }
		constexpr void make_strikethrough() { normal = false; underline = true; }

		constexpr bool is_bold() const { return bold; }
		constexpr bool is_italic() const { return italic; }
		constexpr bool is_underline() const { return underline; }
		constexpr bool is_strikethrough() const { return strikethrough; }
		constexpr bool is_normal() const { return normal; };

		constexpr void clear() { make_normal(); };

	private:
		bool normal = true;
		bool bold = false;
		bool italic = false;
		bool underline = false;
		bool strikethrough = false;
	};

	enum class FontStyle : uint32_t {
		Normal = 0x00,
		Bold = 0x01,
		Italic = 0x02,
		Underline = 0x04,
		Strikethrough = 0x08
	};

	// Enable bitwise operations for FontStyles

	constexpr FontStyle operator|(FontStyle lhs, FontStyle rhs) {
		return static_cast<FontStyle>(
			static_cast<uint32_t>(lhs) | static_cast<uint32_t>(rhs)
			);
	}

	constexpr FontStyle operator&(FontStyle lhs, FontStyle rhs) {
		return static_cast<FontStyle>(
			static_cast<uint32_t>(lhs) & static_cast<uint32_t>(rhs)
			);
	}

	constexpr FontStyle operator~(FontStyle flag) {
		return static_cast<FontStyle>(~static_cast<uint64_t>(flag));
	}

}

