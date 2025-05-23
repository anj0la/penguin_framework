#pragma once

#include <SDL3/SDL_keycode.h>
#include <cstdint>
#include <array>


namespace penguin::core::input::keyboard {

    constexpr size_t NumKeys = 138; // the number of keys (can't store in the enum)

    enum class PF_Key : uint32_t {
        Unknown = SDLK_UNKNOWN,
        Enter = SDLK_RETURN,
        Escape = SDLK_ESCAPE,
        Backspace = SDLK_BACKSPACE,
        Tab = SDLK_TAB,
        Space = SDLK_SPACE,
        Exclaim = SDLK_EXCLAIM,
        At = SDLK_AT,
        Hash = SDLK_HASH,
        Dollar = SDLK_DOLLAR,
        Percent = SDLK_PERCENT,
        Caret = SDLK_CARET,
        Ampersand = SDLK_AMPERSAND,
        Asterisk = SDLK_ASTERISK,
        LBracket = SDLK_LEFTPAREN,
        RBracket = SDLK_RIGHTPAREN,
        Minus = SDLK_MINUS,
        Plus = SDLK_PLUS,
        Num0 = SDLK_0,
        Num1 = SDLK_1,
        Num2 = SDLK_2,
        Num3 = SDLK_3,
        Num4 = SDLK_4,
        Num5 = SDLK_5,
        Num6 = SDLK_6,
        Num7 = SDLK_7,
        Num8 = SDLK_8,
        Num9 = SDLK_9,
        Underscore = SDLK_UNDERSCORE,
        EqualSign = SDLK_EQUALS,
        GreaterThan = SDLK_GREATER,
        LessThan = SDLK_LESS,
        LBrace = SDLK_LEFTBRACE,
        RBrace = SDLK_RIGHTBRACE,
        LSquareBracket = SDLK_LEFTBRACKET,
        RSquareBracket = SDLK_RIGHTBRACKET,
        QuestionMark = SDLK_QUESTION,
        Slash = SDLK_SLASH,
        Backslash = SDLK_BACKSLASH,
        Pipe = SDLK_PIPE,
        Comma = SDLK_COMMA,
        Period = SDLK_PERIOD,
        Colon = SDLK_COLON,
        Semicolon = SDLK_SEMICOLON,
        DQoute = SDLK_DBLAPOSTROPHE,
        SQuote = SDLK_APOSTROPHE,
        Grave = SDLK_GRAVE,
        Tilde = SDLK_TILDE,
        A = SDLK_A,
        B = SDLK_B,
        C = SDLK_C,
        D = SDLK_D,
        E = SDLK_E,
        F = SDLK_F,
        G = SDLK_G,
        H = SDLK_H,
        I = SDLK_I,
        J = SDLK_J,
        K = SDLK_K,
        L = SDLK_L,
        M = SDLK_M,
        N = SDLK_N,
        O = SDLK_O,
        P = SDLK_P,
        Q = SDLK_Q,
        R = SDLK_R,
        S = SDLK_S,
        T = SDLK_T,
        U = SDLK_U,
        V = SDLK_V,
        W = SDLK_W,
        X = SDLK_X,
        Y = SDLK_Y,
        Z = SDLK_Z,
        Delete = SDLK_DELETE,
        PlusMinus = SDLK_PLUSMINUS,
        CapsLock = SDLK_CAPSLOCK,
        F1 = SDLK_F1,
        F2 = SDLK_F2,
        F3 = SDLK_F3,
        F4 = SDLK_F4,
        F5 = SDLK_F5,
        F6 = SDLK_F6,
        F7 = SDLK_F7,
        F8 = SDLK_F8,
        F9 = SDLK_F9,
        F10 = SDLK_F10,
        F11 = SDLK_F11,
        F12 = SDLK_F12,
        PrintScreen = SDLK_PRINTSCREEN,
        ScrollLock = SDLK_SCROLLLOCK,
        Pause = SDLK_PAUSE,
        Insert = SDLK_INSERT,
        Home = SDLK_HOME,
        PageUp = SDLK_PAGEUP,
        PageDown = SDLK_PAGEDOWN,
        End = SDLK_END,
        Right = SDLK_RIGHT,
        Left = SDLK_LEFT,
        Down = SDLK_DOWN,
        Up = SDLK_UP,
        KeypadDivide = SDLK_KP_DIVIDE,
        KeypadMultiply = SDLK_KP_MULTIPLY,
        KeypadMinus = SDLK_KP_MINUS,
        KeypadPlus = SDLK_KP_PLUS,
        KeypadEnter = SDLK_KP_ENTER,
        Keypad0 = SDLK_KP_0,
        Keypad1 = SDLK_KP_1,
        Keypad2 = SDLK_KP_2,
        Keypad3 = SDLK_KP_3,
        Keypad4 = SDLK_KP_4,
        Keypad5 = SDLK_KP_5,
        Keypad6 = SDLK_KP_6,
        Keypad7 = SDLK_KP_7,
        Keypad8 = SDLK_KP_8,
        Keypad9 = SDLK_KP_9,
        KeypadPeriod = SDLK_KP_PERIOD,
        KeypadEqualSign = SDLK_KP_EQUALS,
        Application = SDLK_APPLICATION,
        Undo = SDLK_UNDO,
        Cut = SDLK_CUT,
        Copy = SDLK_COPY,
        Paste = SDLK_PASTE,
        Find = SDLK_FIND,
        Mute = SDLK_MUTE,
        VolumeUp = SDLK_VOLUMEUP,
        VolumeDown = SDLK_VOLUMEDOWN,
        AltErase = SDLK_ALTERASE,
        Cancel = SDLK_CANCEL,
        Clear = SDLK_CLEAR,
        LCtrl = SDLK_LCTRL,
        RCtrl = SDLK_RCTRL,
        LShift = SDLK_LSHIFT,
        RShift = SDLK_RSHIFT,
        LGui = SDLK_LGUI,
        RGui = SDLK_RGUI
    };

    constexpr size_t InvalidKeyIndex = 0;

    constexpr std::array<PF_Key, NumKeys> PF_KeyList = {
        Unknown,
        Enter,
        Escape,
        Backspace,
        Tab,
        Space,
        Exclaim,
        At,
        Hash,
        Dollar,
        Percent,
        Caret,
        Ampersand,
        Asterisk,
        LBracket,
        RBracket,
        Minus,
        Plus,
        Num0,
        Num1,
        Num2,
        Num3,
        Num4,
        Num5,
        Num6,
        Num7,
        Num8,
        Num9,
        Underscore,
        EqualSign,
        GreaterThan,
        LessThan,
        LBrace,
        RBrace,
        LSquareBracket,
        RSquareBracket,
        QuestionMark,
        Slash,
        Backslash,
        Pipe,
        Comma,
        Period,
        Colon,
        Semicolon,
        DQoute,
        SQuote,
        Grave,
        Tilde,
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
        Delete,
        PlusMinus,
        CapsLock,
        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,
        PrintScreen,
        ScrollLock,
        Pause,
        Insert,
        Home,
        PageUp,
        PageDown,
        End,
        Right,
        Left,
        Down,
        Up,
        KeypadDivide,
        KeypadMultiply,
        KeypadMinus,
        KeypadPlus,
        KeypadEnter,
        Keypad0,
        Keypad1,
        Keypad2,
        Keypad3,
        Keypad4,
        Keypad5,
        Keypad6,
        Keypad7,
        Keypad8,
        Keypad9,
        KeypadPeriod,
        KeypadEqualSign,
        Application,
        Undo,
        Cut,
        Copy,
        Paste,
        Find,
        Mute,
        VolumeUp,
        VolumeDown,
        AltErase,
        Cancel,
        Clear,
        LCtrl,
        RCtrl,
        LShift,
        RShift,
        LGui,
        RGui
    };

    constexpr int key_to_index(PF_Key key) {
        for (size_t i = 0; i < KeyList.size(); ++i) {
            if (PF_KeyList[i] == key) {
                return i;
            }
        }
        return InvalidKeyIndex; // doesn't exist (unknown is the first value)
    }
}

