// Copyright (C) 2005-2014 The END Authors. All rights reserved.
//
// This file is part of the "END" (Engine for Dimensions).
// You can use this source code under the New BSD license
// that can be found in the LICENSE file.
// 이 파일은 "END" 의 일부분입니다.
// 소스코드는 New BSD license 에따라 사용이 가능합니다.

#ifndef _EKEYBOARD_MODULE_H__
#define _EKEYBOARD_MODULE_H__

namespace end2 {

//! Keyboard Module
/**
 The Keyboard Device is inherited from EDevice.
 Platform specific parts are dealed with specific keyboard device driver
 **/
class EKeyboardModule {
public:

    //! Key Code (from Irricht keycodes.h)
    enum E_KEY_CODE {
        E_KC_LBUTTON      = 0x01,  ///< Left mouse button
        E_KC_RBUTTON      = 0x02,  ///< Right mouse button
        E_KC_CANCEL       = 0x03,  ///< Control-break processing
        E_KC_MBUTTON      = 0x04,  ///< Middle mouse button (three-button mouse)
        E_KC_XBUTTON1     = 0x05,  ///< Windows 2000/XP: X1 mouse button
        E_KC_XBUTTON2     = 0x06,  ///< Windows 2000/XP: X2 mouse button

        E_KC_BACK         = 0x08,  ///< BACKSPACE key
        E_KC_TAB          = 0x09,  ///< TAB key
        E_KC_CLEAR        = 0x0C,  ///< CLEAR key

        E_KC_RETURN       = 0x0D,  ///< ENTER key
        E_KC_SHIFT        = 0x10,  ///< SHIFT key
        E_KC_CONTROL      = 0x11,  ///< CTRL key
        E_KC_MENU         = 0x12,  ///< ALT key

        E_KC_PAUSE        = 0x13,  ///< PAUSE key
        E_KC_CAPITAL      = 0x14,  ///< CAPS LOCK key

        E_KC_KANA         = 0x15,  ///< IME Kana mode
        E_KC_HANGUEL      = 0x15,  ///< IME Hanguel mode (maintained for compatibility use E_KC_HANGUL)
        E_KC_HANGUL       = 0x15,  ///< IME Hangul mode
        E_KC_JUNJA        = 0x17,  ///< IME Junja mode
        E_KC_FINAL        = 0x18,  ///< IME final mode
        E_KC_HANJA        = 0x19,  ///< IME Hanja mode
        E_KC_KANJI        = 0x19,  ///< IME Kanji mode

        E_KC_ESCAPE       = 0x1B,  ///< ESC key

        E_KC_CONVERT      = 0x1C,  ///< IME convert
        E_KC_NONCONVERT   = 0x1D,  ///< IME nonconvert
        E_KC_ACCEPT       = 0x1E,  ///< IME accept
        E_KC_MODECHANGE   = 0x1F,  ///< IME mode change request

        E_KC_SPACE        = 0x20,  ///< SPACEBAR

        E_KC_PRIOR        = 0x21,  ///< PAGE UP key
        E_KC_NEXT         = 0x22,  ///< PAGE DOWN key
        E_KC_END          = 0x23,  ///< END key
        E_KC_HOME         = 0x24,  ///< HOME key

        E_KC_LEFT         = 0x25,  ///< LEFT ARROW key
        E_KC_UP           = 0x26,  ///< UP ARROW key
        E_KC_RIGHT        = 0x27,  ///< RIGHT ARROW key
        E_KC_DOWN         = 0x28,  ///< DOWN ARROW key

        E_KC_SELECT       = 0x29,  ///< SELECT key
        E_KC_PRINT        = 0x2A,  ///< PRINT key
        E_KC_EXECUT       = 0x2B,  ///< EXECUTE key
        E_KC_SNAPSHOT     = 0x2C,  ///< PRINT SCREEN key
        E_KC_INSERT       = 0x2D,  ///< INS key
        E_KC_DELETE       = 0x2E,  ///< DEL key
        E_KC_HELP         = 0x2F,  ///< HELP key

        E_KC_0            = 0x30,  ///< 0 key
        E_KC_1            = 0x31,  ///< 1 key
        E_KC_2            = 0x32,  ///< 2 key
        E_KC_3            = 0x33,  ///< 3 key
        E_KC_4            = 0x34,  ///< 4 key
        E_KC_5            = 0x35,  ///< 5 key
        E_KC_6            = 0x36,  ///< 6 key
        E_KC_7            = 0x37,  ///< 7 key
        E_KC_8            = 0x38,  ///< 8 key
        E_KC_9            = 0x39,  ///< 9 key

        E_KC_A            = 0x41,  ///< A key
        E_KC_B            = 0x42,  ///< B key
        E_KC_C            = 0x43,  ///< C key
        E_KC_D            = 0x44,  ///< D key
        E_KC_E            = 0x45,  ///< E key
        E_KC_F            = 0x46,  ///< F key
        E_KC_G            = 0x47,  ///< G key
        E_KC_H            = 0x48,  ///< H key
        E_KC_I            = 0x49,  ///< I key
        E_KC_J            = 0x4A,  ///< J key
        E_KC_K            = 0x4B,  ///< K key
        E_KC_L            = 0x4C,  ///< L key
        E_KC_M            = 0x4D,  ///< M key
        E_KC_N            = 0x4E,  ///< N key
        E_KC_O            = 0x4F,  ///< O key
        E_KC_P            = 0x50,  ///< P key
        E_KC_Q            = 0x51,  ///< Q key
        E_KC_R            = 0x52,  ///< R key
        E_KC_S            = 0x53,  ///< S key
        E_KC_T            = 0x54,  ///< T key
        E_KC_U            = 0x55,  ///< U key
        E_KC_V            = 0x56,  ///< V key
        E_KC_W            = 0x57,  ///< W key
        E_KC_X            = 0x58,  ///< X key
        E_KC_Y            = 0x59,  ///< Y key
        E_KC_Z            = 0x5A,  ///< Z key

        E_KC_LWIN         = 0x5B,  ///< Left Windows key (Microsoft Natural keyboard)
        E_KC_RWIN         = 0x5C,  ///< Right Windows key (Natural keyboard)
        E_KC_APPS         = 0x5D,  ///< Applications key (Natural keyboard)
        E_KC_SLEEP        = 0x5F,  ///< Computer Sleep key

        E_KC_NUMPAD0      = 0x60,  ///< Numeric keypad 0 key
        E_KC_NUMPAD1      = 0x61,  ///< Numeric keypad 1 key
        E_KC_NUMPAD2      = 0x62,  ///< Numeric keypad 2 key
        E_KC_NUMPAD3      = 0x63,  ///< Numeric keypad 3 key
        E_KC_NUMPAD4      = 0x64,  ///< Numeric keypad 4 key
        E_KC_NUMPAD5      = 0x65,  ///< Numeric keypad 5 key
        E_KC_NUMPAD6      = 0x66,  ///< Numeric keypad 6 key
        E_KC_NUMPAD7      = 0x67,  ///< Numeric keypad 7 key
        E_KC_NUMPAD8      = 0x68,  ///< Numeric keypad 8 key
        E_KC_NUMPAD9      = 0x69,  ///< Numeric keypad 9 key

        E_KC_MULTIPLY     = 0x6A,  ///< Multiply key
        E_KC_ADD          = 0x6B,  ///< Add key
        E_KC_SEPARATOR    = 0x6C,  ///< Separator key
        E_KC_SUBTRACT     = 0x6D,  ///< Subtract key
        E_KC_DECIMAL      = 0x6E,  ///< Decimal key
        E_KC_DIVIDE       = 0x6F,  ///< Divide key

        E_KC_F1           = 0x70,  ///< F1 key
        E_KC_F2           = 0x71,  ///< F2 key
        E_KC_F3           = 0x72,  ///< F3 key
        E_KC_F4           = 0x73,  ///< F4 key
        E_KC_F5           = 0x74,  ///< F5 key
        E_KC_F6           = 0x75,  ///< F6 key
        E_KC_F7           = 0x76,  ///< F7 key
        E_KC_F8           = 0x77,  ///< F8 key
        E_KC_F9           = 0x78,  ///< F9 key
        E_KC_F10          = 0x79,  ///< F10 key
        E_KC_F11          = 0x7A,  ///< F11 key
        E_KC_F12          = 0x7B,  ///< F12 key
        E_KC_F13          = 0x7C,  ///< F13 key
        E_KC_F14          = 0x7D,  ///< F14 key
        E_KC_F15          = 0x7E,  ///< F15 key
        E_KC_F16          = 0x7F,  ///< F16 key
        E_KC_F17          = 0x80,  ///< F17 key
        E_KC_F18          = 0x81,  ///< F18 key
        E_KC_F19          = 0x82,  ///< F19 key
        E_KC_F20          = 0x83,  ///< F20 key
        E_KC_F21          = 0x84,  ///< F21 key
        E_KC_F22          = 0x85,  ///< F22 key
        E_KC_F23          = 0x86,  ///< F23 key
        E_KC_F24          = 0x87,  ///< F24 key

        E_KC_NUMLOCK      = 0x90,  ///< NUM LOCK key
        E_KC_SCROLL       = 0x91,  ///< SCROLL LOCK key

        E_KC_LSHIFT       = 0xA0,  ///< Left SHIFT key
        E_KC_RSHIFT       = 0xA1,  ///< Right SHIFT key
        E_KC_LCONTROL     = 0xA2,  ///< Left CONTROL key
        E_KC_RCONTROL     = 0xA3,  ///< Right CONTROL key
        E_KC_LMENU        = 0xA4,  ///< Left MENU key
        E_KC_RMENU        = 0xA5,  ///< Right MENU key

        E_KC_PLUS         = 0xBB,  ///< Plus Key   (+)
        E_KC_COMMA        = 0xBC,  ///< Comma Key  (,)
        E_KC_MINUS        = 0xBD,  ///< Minus Key  (-)
        E_KC_PERIOD       = 0xBE,  ///< Period Key (.)
        E_KC_ATTN         = 0xF6,  ///< Attn key
        E_KC_CRSEL        = 0xF7,  ///< CrSel key
        E_KC_EXSEL        = 0xF8,  ///< ExSel key
        E_KC_EREOF        = 0xF9,  ///< Erase EOF key
        E_KC_PLAY         = 0xFA,  ///< Play key
        E_KC_ZOOM         = 0xFB,  ///< Zoom key
        E_KC_PA1          = 0xFD,  ///< PA1 key
        E_KC_OEM_CLEAR    = 0xFE,  ///< Clear key
    };

    //! constructor
    EKeyboardModule(){
    }

    //! destructor
    virtual ~EKeyboardModule(){
    }

    //! queries whether key down
    virtual bool isKeyDown(E_KEY_CODE _eKey) = 0;

    virtual bool updateKeyState( int _platformKeyCode, bool _bDown ) = 0;
    virtual bool updateKeyState() = 0;
};

}

#endif //_EKEYBOARD_MODULE_H__

// vim: ts=4:sw=4
