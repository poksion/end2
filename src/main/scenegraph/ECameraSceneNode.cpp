// Copyright (C) 2005-2014 The END Authors. All rights reserved.
//
// This file is part of the "END" (Engine for Dimensions).
// You can use this source code under the New BSD license
// that can be found in the LICENSE file.
// 이 파일은 "END" 의 일부분입니다.
// 소스코드는 New BSD license 에따라 사용이 가능합니다.

#include "ECameraSceneNode.h"

#include "math/EMath.h"

namespace end2 {

void ECameraSceneNode::updateProjection(int _changed_width, int _changed_height) {
    setProjection(fov_y_, float(_changed_width) / float(_changed_height), near_z_, far_z_);
}

void ECameraSceneNode::setProjection(float _fov_y, float _aspect_ratio, float _near_z, float _far_z) {
    fov_y_ = _fov_y;
    near_z_ = _near_z;
    far_z_ = _far_z;

    EMatrix4::makeProjectionTM(projection_tm_, fov_y_, _aspect_ratio, near_z_, far_z_);
}

void ECameraSceneNode::onTransformed_() {
    EMatrix4 mat_world;
    getTransformRelativeToWorld(mat_world);
    EMatrix4::makeViewTM(view_tm_, mat_world);
}

}

// vim: ts=4:sw=4
