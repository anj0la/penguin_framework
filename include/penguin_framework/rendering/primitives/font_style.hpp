#pragma once 

#include <cstdint>

namespace penguin::rendering::primitives {

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

