// Copyright (C) 2005-2014 The END Authors. All rights reserved.
//
// This file is part of the "END" (Engine for Dimensions).
// You can use this source code under the New BSD license
// that can be found in the LICENSE file.
// 이 파일은 "END" 의 일부분입니다.
// 소스코드는 New BSD license 에따라 사용이 가능합니다.

#include "ESceneNodeVisitor.h"
#include "ESceneNode.h"

namespace end2 {

// 포스트오더, 최하단 씬노드부터 vector로 모읍니다.
void ESceneNodeClearVisitor::onPostOrder(ESceneNode* _scene_node) {
    if(root_node_ != _scene_node)
        nodes_to_clear_.push_back(_scene_node);
}

// 포스트오더로 모은 씬노드 지우기
void ESceneNodeClearVisitor::clearSceneNodes() {
    for(std::vector<ESceneNode*>::iterator itr = nodes_to_clear_.begin();
            itr != nodes_to_clear_.end(); ++itr) {
        ESceneNode* scene_node = *itr;
        ESceneNode* parent_node = scene_node->getParent();
        if(parent_node)
            parent_node->destroyChild(scene_node);
    }

    nodes_to_clear_.clear();
}

}

// vim: ts=4:sw=4
