// Copyright (C) 2005-2014 The END Authors. All rights reserved.
//
// This file is part of the "END" (Engine for Dimensions).
// You can use this source code under the New BSD license
// that can be found in the LICENSE file.
// 이 파일은 "END" 의 일부분입니다.
// 소스코드는 New BSD license 에따라 사용이 가능합니다.

#ifndef _EKEYBOARD_MODULE_GLUT_H__
#define _EKEYBOARD_MODULE_GLUT_H__

#include <string.h>
#include "EKeyboardModule.h"

namespace end2 {

//! The Specific Keyboard Module
class EKeyboardModuleGlut : public EKeyboardModule {
private:
    int allKeys_[256];

public:

    //! constructor
    EKeyboardModuleGlut();

    //! destructor
    virtual ~EKeyboardModuleGlut() {
    }

    //! queries whether key down
    virtual bool isKeyDown(E_KEY_CODE _eKey) {
        return (allKeys_[_eKey] == 1);
    }

    //! sets key buffer to be pressed or not
    virtual bool updateKeyState( int _platformKeyCode, bool _bDown );

    //! sets key buffer from another key state buffer
    virtual bool updateKeyState() {
        return false;
    }

private:
    bool updateKeyState(E_KEY_CODE _key, E_KEY_CODE _start, E_KEY_CODE _end, bool _bDown);
};

}

#endif //_EKEYBOARD_MODULE_GLUT_H__

// vim: ts=4:sw=4
