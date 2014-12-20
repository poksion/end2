// Copyright (C) 2005-2014 The END Authors. All rights reserved.
//
// This file is part of the "END" (Engine for Dimensions).
// You can use this source code under the New BSD license
// that can be found in the LICENSE file.
// 이 파일은 "END" 의 일부분입니다.
// 소스코드는 New BSD license 에따라 사용이 가능합니다.

#ifndef _ESCENE_NODE_VISITOR_H__
#define _ESCENE_NODE_VISITOR_H__

#include <vector>
#include <set>

namespace end2 {

class ESceneNode;

//! Vistor Class. With traverse method in scene node, visiting scene node
class ESceneNodeVisitor {
public:

    //! constructor
    ESceneNodeVisitor() {
    }

    //! destructor
    virtual ~ESceneNodeVisitor() {
    }

    //! pre-order trarvers. If returns false, visiting will be stopped
    virtual bool onPreOrder(ESceneNode* _scene_node) = 0;

    //! post-order travers
    virtual void onPostOrder(ESceneNode* _scene_node) = 0;
};

//! Vistor for clear childern scene nodes
class ESceneNodeClearVisitor: public ESceneNodeVisitor {
private:
    std::vector<ESceneNode*> nodes_to_clear_;
    ESceneNode* root_node_;

public:

    //! constructor
    ESceneNodeClearVisitor(ESceneNode* _root_node) : root_node_(_root_node) {
    }

    //! destructor
    virtual ~ESceneNodeClearVisitor() {
    }

    //! ESceneNodeClearVisitor does not use pre-order
    virtual bool onPreOrder(ESceneNode* _scene_node) {
        return true;
    }

    //! called on post-order, collects scene nodes to delete
    virtual void onPostOrder(ESceneNode* _scene_node);

    //! clears scene nodes
    void clearSceneNodes();

    //! checks for collection
    bool isEmpty() {
        return nodes_to_clear_.empty();
    }
};

}

#endif //_ESCENE_NODE_VISITOR_H__

// vim: ts=4:sw=4
