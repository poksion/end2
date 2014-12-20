// Copyright (C) 2005-2014 The END Authors. All rights reserved.
//
// This file is part of the "END" (Engine for Dimensions).
// You can use this source code under the New BSD license
// that can be found in the LICENSE file.
// 이 파일은 "END" 의 일부분입니다.
// 소스코드는 New BSD license 에따라 사용이 가능합니다.

#ifdef _MSC_VER

#ifndef _EKEYBOARD_MODULE_WIN32_H__
#define _EKEYBOARD_MODULE_WIN32_H__

#include <string.h>

#include "EKeyboardModule.h"
#include "Windows.h"

namespace end2 {

//! The Specific Keyboard Module for Win32 Platform
class EKeyboardModuleWin32 : public EKeyboardModule {
private:
    // key buffer
    BYTE allKeys_[256];

public:

    //! constructor
    EKeyboardModuleWin32() {
        // init key buffer
        memset(allKeys_, 0, sizeof(allKeys_));
    }

    //! destructor
    virtual ~EKeyboardModuleWin32() {
    }

    //! queries whether key down
    virtual bool isKeyDown( E_KEY_CODE _eKey ) {
        return ((allKeys_[_eKey] & 0x80)!=0);
    }

    //! sets key buffer to be pressed or not
    virtual bool updateKeyState( int _platformKeyCode, bool _bDown ) {
        return false;
    }

    //! sets key buffer from another key state buffer
    virtual bool updateKeyState() {
        GetKeyboardState(allKeys_);
        return true;
    }
};

}

#endif //_EKEYBOARD_MODULE_WIN32_H__

#endif

// vim: ts=4:sw=4
