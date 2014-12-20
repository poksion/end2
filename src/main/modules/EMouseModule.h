// Copyright (C) 2005-2014 The END Authors. All rights reserved.
//
// This file is part of the "END" (Engine for Dimensions).
// You can use this source code under the New BSD license
// that can be found in the LICENSE file.
// 이 파일은 "END" 의 일부분입니다.
// 소스코드는 New BSD license 에따라 사용이 가능합니다.

#ifndef _EMOUSE_MODULE_H__
#define _EMOUSE_MODULE_H__

#include <string.h> //for memset
namespace end2 {

//! The general mouse device module
class EMouseModule {
public:

    //! The Mouse Events
    enum E_MOUSE_EVENT {
        E_ME_LBUTTON_UP = 0,    ///< Left Mouse Button Up
        E_ME_LBUTTON_DOWN,      ///< Left Mouse Button Down

        E_ME_RBUTTON_UP,        ///< Right Mouse Button Up
        E_ME_RBUTTON_DOWN,      ///< Right Mouse Button Down

        E_ME_MBUTTON_UP,        ///< Middle Mouse Button Up
        E_ME_MBUTTON_DOWN,      ///< Middle Mouse Button Down

        E_ME_MOVED,             ///< Mouse Moved
        E_ME_WHEEL,             ///< Mouse Wheel

        E_ME_COUNT
    };

private:

    //! current x position
    int current_pos_x_;

    //! current y position
    int current_pos_y_;

    //! previous x position
    int previous_pos_x_;

    //! previous y position
    int previous_pos_y_;

    //! wheel value
    float wheel_value_;

    //! mouse event state buffer
    int mosue_event_state_buffer_[E_ME_COUNT];

public:

    //! constructor
    EMouseModule() :
            current_pos_x_(0), current_pos_y_(0),
            previous_pos_x_(0), previous_pos_y_(0),
            wheel_value_(0.f) {
    }

    //! destructor
    virtual ~EMouseModule() {
    }

    //! sets position
    void setPositionBuffer(int _pos_x, int _pos_y) {
        // 예전값 설정
        previous_pos_x_ = current_pos_x_;
        previous_pos_y_ = current_pos_y_;

        // 현재값 설정
        current_pos_x_ = _pos_x;
        current_pos_y_ = _pos_y;
    }

    //! sets mouse event state
    void setEventStateBuffer(E_MOUSE_EVENT _eState, bool bChecked) {
        mosue_event_state_buffer_[_eState] = (bChecked ? 1 : 0);
    }

    //! sets wheel value
    void setWheelBuffer(float _fWheelValue) {
        wheel_value_ = _fWheelValue;
    }

    //! queries current mouse event state
    bool isCurrentState(E_MOUSE_EVENT _eEvent) {
        // wheel event
        if(_eEvent == E_ME_WHEEL) {
            return (0.f != wheel_value_);
        }

        return (mosue_event_state_buffer_[_eEvent] == 1);
    }

    //! gets current position
    void getCurrentPosition(int _pos_x, int _pos_y) {
        _pos_x = current_pos_x_;
        _pos_y = current_pos_y_;
    }

    //! gets previous position
    void getPreviousPosition(int& _pos_x, int& _pos_y) {
        _pos_x = previous_pos_x_;
        _pos_y = previous_pos_y_;
    }

    //! gets position difference between previous and current.
    void getDiffPosition(int& _pos_x, int& _pos_y) {
        if(mosue_event_state_buffer_[E_ME_MOVED] == 0) {
            _pos_x = 0;
            _pos_y = 0;
        } else {
            getCurrentPosition(_pos_x, _pos_y);

            int nPreX(0), nPreY(0);
            getPreviousPosition(nPreX, nPreY);

            _pos_x -= nPreX;
            _pos_y -= nPreY;
        }
    }

    //! gets the wheel value
    float getWheelValue() {
        return wheel_value_;
    }
};

}

#endif //_EMOUSE_MODULE_H__

// vim: ts=4:sw=4
