// Copyright (C) 2005-2014 The END Authors. All rights reserved.
//
// This file is part of the "END" (Engine for Dimensions).
// You can use this source code under the New BSD license
// that can be found in the LICENSE file.
// 이 파일은 "END" 의 일부분입니다.
// 소스코드는 New BSD license 에따라 사용이 가능합니다.

#ifndef _ECOLOR4_EDITOR_H__
#define _ECOLOR4_EDITOR_H__

namespace end2 {

class EColor4Editor {

private:
    const int* rgba_;

public:
    EColor4Editor(const int* _rgba) {
        rgba_ = _rgba;
    }

    inline int getR() const {
        return rgba_[0];
    }
    inline int getG() const {
        return rgba_[1];
    }
    inline int getB() const {
        return rgba_[2];
    }
    inline int getA() const {
        return rgba_[3];
    }

    inline float getClampR() const {
        return (float(getR()) / float(255));
    }
    inline float getClampG() const {
        return (float(getG()) / float(255));
    }
    inline float getClampB() const {
        return (float(getB()) / float(255));
    }
    inline float getClampA() const {
        return (float(getA()) / float(255));
    }

    inline bool hasAlpha() const {
        return (getA() != -1);
    }
};

}

#endif	//_ECOLOR4_EDITOR_H__
