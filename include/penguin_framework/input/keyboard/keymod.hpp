#pragma once

#include <cstdint>

namespace penguin::input::keyboard {

	enum class KeyMod : uint16_t {
		None = 0x0000u,
		LShift = 0x0001u,
		RShift = 0x0002u,
		Level5 = 0x0004u,
		LCtrl = 0x0040u,
		RCtrl = 0x0080u,
		LAlt = 0x0100u,
		RAlt = 0x0200u,
		LGui = 0x0400u,
		RGui = 0x0800u,
		NumLock = 0x1000u,
		CapsLock = 0x2000u,
		ScrollLock = 0x8000u,
		Ctrl = (LCtrl | RCtrl),
		Alt = (LAlt | RAlt),
		Gui = (LGui | RGui),
	};
}