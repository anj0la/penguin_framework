#pragma once

#include <penguin_framework/input/keyboard/key.hpp>
#include <penguin_framework/input/keyboard/scan.hpp>

#include <unordered_map>

namespace penguin::internal::input::keyboard {

    using Key = penguin::input::keyboard::Key;
    using Scan = penguin::input::keyboard::Scan;

    inline const std::unordered_map<Key, Scan> key_to_scan = {
        { Key::Unknown, Scan::Unknown },

        { Key::A, Scan::A },
        { Key::B, Scan::B },
        { Key::C, Scan::C },
        { Key::D, Scan::D },
        { Key::E, Scan::E },
        { Key::F, Scan::F },
        { Key::G, Scan::G },
        { Key::H, Scan::H },
        { Key::I, Scan::I },
        { Key::J, Scan::J },
        { Key::K, Scan::K },
        { Key::L, Scan::L },
        { Key::M, Scan::M },
        { Key::N, Scan::N },
        { Key::O, Scan::O },
        { Key::P, Scan::P },
        { Key::Q, Scan::Q },
        { Key::R, Scan::R },
        { Key::S, Scan::S },
        { Key::T, Scan::T },
        { Key::U, Scan::U },
        { Key::V, Scan::V },
        { Key::W, Scan::W },
        { Key::X, Scan::X },
        { Key::Y, Scan::Y },
        { Key::Z, Scan::Z },

        { Key::Num0, Scan::Num0 },
        { Key::Num1, Scan::Num1 },
        { Key::Num2, Scan::Num2 },
        { Key::Num3, Scan::Num3 },
        { Key::Num4, Scan::Num4 },
        { Key::Num5, Scan::Num5 },
        { Key::Num6, Scan::Num6 },
        { Key::Num7, Scan::Num7 },
        { Key::Num8, Scan::Num8 },
        { Key::Num9, Scan::Num9 },


        { Key::Enter, Scan::Enter },
        { Key::Escape, Scan::Escape },
        { Key::Backspace, Scan::Backspace },
        { Key::Tab, Scan::Tab },
        { Key::Space, Scan::Space },

        { Key::Minus, Scan::Minus },
        { Key::EqualSign, Scan::EqualSign },
        { Key::LBracket, Scan::LBracket },
        { Key::RBracket, Scan::RBracket },
        { Key::Backslash, Scan::Backslash },
        { Key::Tab, Scan::Tab },

        { Key::Semicolon, Scan::Semicolon },
        { Key::Apostrophe, Scan::Apostrophe },
        { Key::Grave, Scan::Grave },
        { Key::Comma, Scan::Comma },
        { Key::Period, Scan::Period },
        { Key::Slash, Scan::Slash },
   
        { Key::CapsLock, Scan::CapsLock },

        { Key::F1, Scan::F1 },
        { Key::F2, Scan::F2 },
        { Key::F3, Scan::F3 },
        { Key::F4, Scan::F4 },
        { Key::F5, Scan::F5 },
        { Key::F6, Scan::F6 },
        { Key::F7, Scan::F7 },
        { Key::F8, Scan::F8 },
        { Key::F9, Scan::F9 },
        { Key::F10, Scan::F10 },
        { Key::F11, Scan::F11 },
        { Key::F12, Scan::F12 },

        { Key::PrintScreen, Scan::PrintScreen },
        { Key::ScrollLock, Scan::ScrollLock },
        { Key::Pause, Scan::Pause },
        { Key::Insert, Scan::Insert },
        { Key::Home, Scan::Home },
        { Key::PageUp, Scan::PageUp },
        { Key::Delete, Scan::Delete },
        { Key::End, Scan::End },
        { Key::PageDown, Scan::PageDown },
        { Key::Right, Scan::Right },
        { Key::Left, Scan::Left },
        { Key::Down, Scan::Down },
        { Key::Up, Scan::Up },

        { Key::NumpadDivide, Scan::NumpadDivide },
        { Key::NumpadMultiply, Scan::NumpadMultiply },
        { Key::NumpadMinus, Scan::NumpadMinus },
        { Key::NumpadPlus, Scan::NumpadPlus },
        { Key::NumpadEnter, Scan::NumpadEnter },
        { Key::Numpad0, Scan::Numpad0 },
        { Key::Numpad1, Scan::Numpad1 },
        { Key::Numpad2, Scan::Numpad2 },
        { Key::Numpad3, Scan::Numpad3 },
        { Key::Numpad4, Scan::Numpad4 },
        { Key::Numpad5, Scan::Numpad5 },
        { Key::Numpad6, Scan::Numpad6 },
        { Key::Numpad7, Scan::Numpad7 },
        { Key::Numpad8, Scan::Numpad8 },
        { Key::Numpad9, Scan::Numpad9 },
        { Key::NumpadPeriod, Scan::NumpadPeriod },

        { Key::NumpadLockClear, Scan::NumpadLockClear },
        
        { Key::NumpadEqualSign, Scan::NumpadEqualSign },

        { Key::F13, Scan::F13 },
        { Key::F14, Scan::F14 },
        { Key::F15, Scan::F15 },
        { Key::F16, Scan::F16 },
        { Key::F17, Scan::F17 },
        { Key::F18, Scan::F18 },
        { Key::F19, Scan::F19 },
        { Key::F20, Scan::F20 },
        { Key::F21, Scan::F21 },
        { Key::F22, Scan::F22 },
        { Key::F23, Scan::F23 },
        { Key::F24, Scan::F24 },

        { Key::NumpadComma, Scan::NumpadComma },

        { Key::LCtrl, Scan::LCtrl },
        { Key::LShift, Scan::LShift },
        { Key::LAlt, Scan::LAlt },
        { Key::LGui, Scan::LGui },
        { Key::RCtrl, Scan::RCtrl },
        { Key::RShift, Scan::RShift },
        { Key::RAlt, Scan::RAlt },
        { Key::RGui, Scan::RGui }
    };

}

