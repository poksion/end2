// Copyright (C) 2005-2014 The END Authors. All rights reserved.
//
// This file is part of the "END" (Engine for Dimensions).
// You can use this source code under the New BSD license
// that can be found in the LICENSE file.
// 이 파일은 "END" 의 일부분입니다.
// 소스코드는 New BSD license 에따라 사용이 가능합니다.

#ifndef _ECAMERA_UTIL_H__
#define _ECAMERA_UTIL_H__

#include "math/EMatrix4.h"
#include "math/EVector3.h"
#include "ECameraSceneNode.h"

namespace end2 {

//! Camera Utility
class ECameraUtil {
public:
    static void rotate(ECameraSceneNode& _camera, float _horizontal_move, float _vertical_move) {
        // camera transform 얻기
        EMatrix4 mat;
        _camera.getTransformRelativeToWorld(mat);

        // 수평회전 Z축을 중심으로 회전
        EMatrix4 mat_rot;
        EMatrix4::makeRotTM(mat_rot, EVector3::UNIT_Z, _horizontal_move);

        // 포지션에 적용
        EVector3 pos;
        EMatrix4::multiply(pos, mat_rot, *(mat.getFramePosition()));

        // 적용된 포지션에서 에서 원점을 바라보는 방향설정
        EVector3 dir(pos);
        dir.applyNormalization().applySymmetry();

        // 수직회전을 위해 포지션에서 오른쪽 축을 중심으로 회전
        EVector3 right;
        EVector3::crossProduct(right, dir, EVector3::UNIT_Z);
        if( EVector3::lengthSq(right) < 0.001f) {
            // 카메라가 수직에 너무 가까이 오는것을 방지
            _vertical_move = - _vertical_move;
        }

        // 수직회전 행렬
        right.applyNormalization();
        EMatrix4::makeRotTM(mat_rot, right, _vertical_move);

        // 수직회전을 적용하여 position과 direction 설정
        dir.set(pos);
        EMatrix4::multiply(pos, mat_rot, dir);
        dir.set(pos).applySymmetry();

        // camera transform 적용
        EMatrix4::makeFrame(mat, pos, dir, EVector3::UNIT_Z);
        _camera.setTransformRelativeToWorld(mat);
    }
};

}

#endif	//_ECAMERA_UTIL_H__

// vim: ts=4:sw=4
