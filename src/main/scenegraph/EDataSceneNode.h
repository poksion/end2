// Copyright (C) 2005-2014 The END Authors. All rights reserved.
//
// This file is part of the "END" (Engine for Dimensions).
// You can use this source code under the New BSD license
// that can be found in the LICENSE file.
// 이 파일은 "END" 의 일부분입니다.
// 소스코드는 New BSD license 에따라 사용이 가능합니다.

#ifndef _EDATA_SCENE_NODE_H__
#define _EDATA_SCENE_NODE_H__

#include <string>
#include <list>

#include "math/EMath.h"
#include "math/EMatrix4.h"

#include "EFlagProperty.h"
#include "ESceneNodeVisitor.h"

namespace end2 {

class ESceneNode;
typedef std::list<ESceneNode*> ESceneNodeList;

//! The essential element class of the scene graph
template<typename T>
class EDataSceneNode : public ESceneNode {
protected:

    T data_;

    //! called on attached to parent
    virtual void onAttachedToParent_(){
    }

    //! called on dettached to parent
    virtual void onDetachedFromParent_(){
    }

    //! called on transformed
    virtual void onTransformed_(){

    }

public:
    T& getData(){
        return data_;
    }
};

}

#endif	//_EDATA_SCENE_NODE_H__

// vim: ts=4:sw=4
