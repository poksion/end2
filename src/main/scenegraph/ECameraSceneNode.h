// Copyright (C) 2005-2014 The END Authors. All rights reserved.
//
// This file is part of the "END" (Engine for Dimensions).
// You can use this source code under the New BSD license
// that can be found in the LICENSE file.
// 이 파일은 "END" 의 일부분입니다.
// 소스코드는 New BSD license 에따라 사용이 가능합니다.

#ifndef _ECAMERA_SCENE_NODE_H__
#define _ECAMERA_SCENE_NODE_H__

#include "ESceneNode.h"

namespace end2 {

//! Camera SceneNode
class ECameraSceneNode: public ESceneNode {
private:
    //////////////////////////////////////////////////////////////////////

    //! view tm
    EMatrix4 view_tm_;

    //! projection tm
    EMatrix4 projection_tm_;

    //////////////////////////////////////////////////////////////////////

    //! fov, y
    float fov_y_;

    //! near z at clipping
    float near_z_;

    //! far z at clipping
    float far_z_;

public:

    //! constructor
    ECameraSceneNode() {
        fov_y_ = EMath::PI / 4.f;
        near_z_ = 1.f;
        far_z_ = 10000.f;

        EMatrix4::makeProjectionTM(projection_tm_, fov_y_, 4.f / 3.f, near_z_, far_z_);
    }

    //! destructor
    virtual ~ECameraSceneNode() {
    }

    //! sets projection
    void setProjection(float _fov_y, float _aspect_ratio, float _near_z, float _far_z);

    //! updates projection when display area changed
    void updateProjection(int _changed_width, int _changed_height);

    //! gets view transform
    const EMatrix4& getViewTransform() {
        return view_tm_;
    }

    //! gets projection transform
    const EMatrix4& getProjectionTransform() {
        return projection_tm_;
    }

protected:

    //////////////////////////////////////////////////////////////////////

    //! called on attached to parent
    virtual void onAttachedToParent_() {
    }

    //! called on dettached to parent
    virtual void onDetachedFromParent_() {
    }

    //! called on transfromed
    virtual void onTransformed_();
};

}

#endif	//_ECAMERA_SCENE_NODE_H__

// vim: ts=4:sw=4
