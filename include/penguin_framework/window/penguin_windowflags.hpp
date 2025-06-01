#pragma once

#include <cstdint>

namespace penguin::window {

	enum class WindowFlags : uint64_t {
		None = 0,
		Fullscreen = (0x0000000000000001ULL),				
		Hidden = (0x0000000000000008ULL),					
		Borderless = (0x0000000000000010ULL),				
		Resizable = (0x0000000000000020ULL),				
		Minimized = (0x0000000000000040ULL),				
		Maximized = (0x0000000000000080ULL),				
		MouseGrabbed = (0x0000000000000100ULL),				
		InputFocus = (0x0000000000000200ULL),				
		MouseFocus = (0x0000000000000400ULL),				
		MouseRelativeMode = (0x0000000000008000ULL),		
		AlwaysOnTop = (0x0000000000010000ULL),			
		Transparent = (0x0000000040000000ULL),				
		NotFocusable = (0x0000000080000000ULL)			
	};

	// Enable bitwise operations for WindowFlags

	constexpr WindowFlags operator|(WindowFlags lhs, WindowFlags rhs) {
		return static_cast<WindowFlags>(
			static_cast<uint64_t>(lhs) | static_cast<uint64_t>(rhs)
			);
	}

	constexpr WindowFlags operator&(WindowFlags lhs, WindowFlags rhs) {
		return static_cast<WindowFlags>(
			static_cast<uint64_t>(lhs) & static_cast<uint64_t>(rhs)
			);
	}

	constexpr WindowFlags operator~(WindowFlags flag) {
		return static_cast<WindowFlags>(~static_cast<uint64_t>(flag));
	}

	constexpr bool has_flag(WindowFlags flags, WindowFlags test) {
		return (flags & test) != WindowFlags::None;
	}

}