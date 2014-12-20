// Copyright (C) 2005-2009 The END Authors. All rights reserved.
//
// This file is part of the "END" (Engine for Dimensions).
// You can use this source code under the New BSD license
// that can be found in the LICENSE file.
// 이 파일은 "END" 의 일부분입니다.
// 소스코드는 New BSD license 에따라 사용이 가능합니다.

#ifndef _EQUATERNION_H__
#define _EQUATERNION_H__

#include "EMatrix4.h"

namespace end2 {

class EQuaternion {
public:

    float w, x, y, z;

    /////////////////////////////////////////////////////////////////////
    //
    // EVector3 constructors / setters
    //
    //////////////////////////////////////////////////////////////////////

    EQuaternion(float _w, float _x, float _y, float _z) : w(_w), x(_x), y(_y), z(_z) {
    }
    EQuaternion(float _x_bank, float _y_attitude, float _z_heading) {
        set(_x_bank, _y_attitude, _z_heading);
    }
//    EQuaternion(float _angle, const EVector3& _axis) {
//    }
//    EQuaternion(const EMatrix4& _rotMat) {
//    }

    EQuaternion& set(float _w, float _x, float _y, float _z) {
        w = _w;
        x = _x;
        y = _y;
        z = _z;

        return *this;
    }

    EQuaternion& set(float _x_bank_roll, float _y_attitude_pitch, float _z_heading_yaw) {
        const float cos_x = cos(0.5f * _x_bank_roll);
        const float cos_y = cos(0.5f * _y_attitude_pitch);
        const float cos_z = cos(0.5f * _z_heading_yaw);

        const float sin_x = sin(0.5f * _x_bank_roll);
        const float sin_y = sin(0.5f * _y_attitude_pitch);
        const float sin_z = sin(0.5f * _z_heading_yaw);

        w = cos_z * cos_y * cos_x + sin_z * sin_y * sin_x;
        x = cos_z * cos_y * sin_x - sin_z * sin_y * cos_x;
        y = cos_z * sin_y * cos_x + sin_z * cos_y * sin_x;
        z = sin_z * cos_y * cos_x - cos_z * sin_y * sin_x;

        return applyNomalization();
    }

//    EQuaternion& set(float _angle, const EVector3& _axis) {
//    }

    EQuaternion& applyNomalization() {
        const float norm = w * w + x * x + y * y + z * z;
        if(norm == 1.f) {
            return *this;
        }

        norm = 1.0f / sqrtf(norm);
        w *= norm;
        x *= norm;
        y *= norm;
        z *= norm;
        return (*this);
    }

};

}

#endif	//_EQUATERNION_H__
