// Copyright (C) 2005-2014 The END Authors. All rights reserved.
//
// This file is part of the "END" (Engine for Dimensions).
// You can use this source code under the New BSD license
// that can be found in the LICENSE file.
// 이 파일은 "END" 의 일부분입니다.
// 소스코드는 New BSD license 에따라 사용이 가능합니다.

#ifndef _ETOUCH_SCREEN_MODULE_H__
#define _ETOUCH_SCREEN_MODULE_H__

namespace end2 {

//! The general touch screen device moudle
class ETouchScreenModule {
private:

    //! current x position
    float current_pos_x_;

    //! current y position
    float current_pos_y_;

    //! previous x position
    float previous_pos_x_;

    //! previous y position
    float previous_pos_y_;

public:

    //! constructor
    ETouchScreenModule() :
            current_pos_x_(0), current_pos_y_(0),
            previous_pos_x_(0), previous_pos_y_(0) {
    }

    //! destructor
    virtual ~ETouchScreenModule() {
    }

    //! sets position
    void setPositionBuffer(float _pos_x, float _pos_y) {
        // 예전값 설정
        previous_pos_x_ = current_pos_x_;
        previous_pos_y_ = current_pos_y_;

        // 현재값 설정
        current_pos_x_ = _pos_x;
        current_pos_y_ = _pos_y;
    }

    //! gets current position
    void getCurrentPosition(float& _pos_x, float& _pos_y) {
        _pos_x = current_pos_x_;
        _pos_y = current_pos_y_;
    }

    //! gets previous position
    void getPreviousPosition(float& _pos_x, float& _pos_y) {
        _pos_x = previous_pos_x_;
        _pos_y = previous_pos_y_;
    }

    //! gets position difference between previous and current.
    void getDiffPosition(float& _pos_x, float& _pos_y) {
        getCurrentPosition(_pos_x, _pos_y);

        float preX(0), preY(0);
        getPreviousPosition(preX, preY);

        _pos_x -= preX;
        _pos_y -= preY;
    }
};

}

#endif //_ETOUCH_SCREEN_MODULE_H__

// vim: ts=4:sw=4
