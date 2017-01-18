// Copyright (C) 2005-2014 The END Authors. All rights reserved.
//
// This file is part of the "END" (Engine for Dimensions).
// You can use this source code under the New BSD license
// that can be found in the LICENSE file.
// 이 파일은 "END" 의 일부분입니다.
// 소스코드는 New BSD license 에따라 사용이 가능합니다.

#include <string.h>
#include "EKeyboardModuleGlut.h"

#ifndef _MSC_VER
#ifndef __ANDROID_API__

#include "../graphics/EGLHeaderWrapper.h"

namespace end2 {

//! constructor
EKeyboardModuleGlut::EKeyboardModuleGlut() {
    // init key buffer
    memset(allKeys_, 0, sizeof(allKeys_));
}

//! sets key buffer to be pressed or not
bool EKeyboardModuleGlut::updateKeyState( int _platformKeyCode, bool _bDown ){
    bool result = false;

    if(_platformKeyCode >= GLUT_KEY_F1 && _platformKeyCode <= GLUT_KEY_F12){
        E_KEY_CODE kc = (E_KEY_CODE)(_platformKeyCode + 111);
        result = updateKeyState(kc, E_KC_F1, E_KC_F12, _bDown);
    }else if(_platformKeyCode >= GLUT_KEY_LEFT && _platformKeyCode <= GLUT_KEY_DOWN){
        E_KEY_CODE kc = (E_KEY_CODE)(_platformKeyCode - 63);
        result = updateKeyState(kc, E_KC_LEFT, E_KC_DOWN, _bDown);
    }else if(_platformKeyCode >= GLUT_KEY_PAGE_UP && _platformKeyCode <= GLUT_KEY_PAGE_DOWN){
        E_KEY_CODE kc = (E_KEY_CODE)(_platformKeyCode - 71);
        result = updateKeyState(kc, E_KC_PRIOR, E_KC_NEXT, _bDown);
    }else if(_platformKeyCode == GLUT_KEY_HOME){
        E_KEY_CODE kc = (E_KEY_CODE)(_platformKeyCode - 70);
        result = updateKeyState(kc, E_KC_HOME, E_KC_HOME, _bDown);
    }else if(_platformKeyCode == GLUT_KEY_END){
        E_KEY_CODE kc = (E_KEY_CODE)(_platformKeyCode - 68);
        result = updateKeyState(kc, E_KC_END, E_KC_END, _bDown);
    }else if(_platformKeyCode == GLUT_KEY_INSERT){
        E_KEY_CODE kc = (E_KEY_CODE)(_platformKeyCode - 63);
        result = updateKeyState(kc, E_KC_INSERT, E_KC_INSERT, _bDown);
    }else{
        E_KEY_CODE kc = (E_KEY_CODE)(_platformKeyCode);
        result = updateKeyState(kc, E_KC_0, E_KC_Z, _bDown);
    }

    return result;
}

bool EKeyboardModuleGlut::updateKeyState(E_KEY_CODE _key, E_KEY_CODE _start, E_KEY_CODE _end, bool _bDown){
    bool inRange = true;
    if(_key >= _start && _key <= _end){
       if(_bDown) {
           allKeys_[_key] = 1;
       }else{
           allKeys_[_key] = 0;
       }
    }else{
        inRange = false;
    }

    int modifier = glutGetModifiers();
    if(modifier == 0){
        allKeys_[E_KC_SHIFT] = 0;
        allKeys_[E_KC_CONTROL] = 0;
        allKeys_[E_KC_MENU] = 0;
    }else if(modifier == GLUT_ACTIVE_SHIFT){
        allKeys_[E_KC_SHIFT] = 1;
    }else if(modifier == GLUT_ACTIVE_CTRL){
        allKeys_[E_KC_CONTROL] = 1;
    }else if(modifier == GLUT_ACTIVE_CTRL){
        allKeys_[GLUT_ACTIVE_ALT] = 1;
    }
    return inRange;
}

}

#endif
#endif

// vim: ts=4:sw=4
