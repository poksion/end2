// Copyright (C) 2005-2014 The END Authors. All rights reserved.
//
// This file is part of the "END" (Engine for Dimensions).
// You can use this source code under the New BSD license
// that can be found in the LICENSE file.
// 이 파일은 "END" 의 일부분입니다.
// 소스코드는 New BSD license 에따라 사용이 가능합니다.

#ifndef _ESCENE_NODE_H__
#define _ESCENE_NODE_H__

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
class ESceneNode {
public:
    // scene node properties
    EFLAG_PROPERTIES_1 (
        E_WORLD_FRAME
    );

private:
    EFlagProperty<ESceneNode> flag_property_;

    ESceneNode* parent_;
    ESceneNodeList children_list_;

    std::string node_name_;
    EMatrix4 local_tm_;

protected:

    //! called on attached to parent
    virtual void onAttachedToParent_() = 0;

    //! called on dettached to parent
    virtual void onDetachedFromParent_() = 0;

    //! called on transformed
    virtual void onTransformed_() = 0;

public:

    //! constructor
    ESceneNode() : parent_(0) {
        EMatrix4::makeIdentity(local_tm_);
        flag_property_.addProperty(E_WORLD_FRAME);
    }

    //! destructor
    virtual ~ESceneNode() {
    }

    //! gets parent scene node
    ESceneNode* getParent() {
        return parent_;
    }

    //! creates child scene node
    template<typename T_SceneNode>
    T_SceneNode* createChild(const char* _child_name) {
        ESceneNode* child_scene_node = new T_SceneNode;
        child_scene_node->node_name_ = _child_name;
        child_scene_node->flag_property_.removeProperty(E_WORLD_FRAME);
        child_scene_node->parent_ = this;

        children_list_.push_back(child_scene_node);
        child_scene_node->onAttachedToParent_();

        return static_cast<T_SceneNode*>(child_scene_node);
    }

    //! destroys child scene node
    void destroyChild(ESceneNode* _child_scene_node) {
        if(_child_scene_node->parent_ != this){
            return;
        }

        _child_scene_node->parent_ = 0;

        children_list_.remove(_child_scene_node);
        _child_scene_node->onDetachedFromParent_();
        delete _child_scene_node;
    }

    void destroyAllChildren(){
        ESceneNodeClearVisitor visitor(this);
        traverse(&visitor);
        visitor.clearSceneNodes();
    }

    //! the method that can be made the vistor vists this scene node
    void traverse(ESceneNodeVisitor* _visitor) {
        if(_visitor->onPreOrder(this)) {
            for(ESceneNodeList::iterator itr = children_list_.begin(); itr != children_list_.end(); ++itr) {
                (*itr)->traverse(_visitor);
            }
        }

        _visitor->onPostOrder(this);
    }

    //! sets transform with the scene node which is relatvie to this
    void setTransform(const EMatrix4& _mat, ESceneNode* _the_scene_node_relative_to) {

        if(0 == _the_scene_node_relative_to || parent_ == _the_scene_node_relative_to) {
            local_tm_.set(_mat);
            onTransformed_();
        } else {
            EMatrix4 mat_relative_to, mat_result;
            _the_scene_node_relative_to->getTransformRelativeToWorld(mat_relative_to);
            EMatrix4::multiply(mat_result, mat_relative_to, _mat);
            setTransformRelativeToWorld(mat_result);
        }
    }

    //! sets transform relative to world scene node
    void setTransformRelativeToWorld(const EMatrix4& _mat) {
        if(parent_ == 0 || parent_->flag_property_.queryProperty(E_WORLD_FRAME)) {
            setTransform(_mat, 0);
        } else {
            EMatrix4 mat_relative_to;
            parent_->getTransform(mat_relative_to, _mat);
            setTransformRelativeToParent(mat_relative_to);
        }
    }

    //! sets transform relative to parent scene node
    void setTransformRelativeToParent(const EMatrix4& _mat) {
        setTransform(_mat, parent_);
    }

    //! gets transform with matrix which is relative to its transform
    void getTransform(EMatrix4& _out_mat, const EMatrix4& _relative_to_mat) const {
        EMatrix4 mat;
        getTransformRelativeToWorld(mat);

        EMatrix4 mat_relative_inv;
        EMatrix4::inverse(mat_relative_inv, _relative_to_mat);

        EMatrix4::multiply(_out_mat, mat, mat_relative_inv);
    }

    //! gets transform relative to world
    void getTransformRelativeToWorld(EMatrix4& _out_mat) const {

        _out_mat.set(getTransformRelativeToParent());
        if(parent_ == 0 || parent_->flag_property_.queryProperty(E_WORLD_FRAME)) {
            return;
        }

        ESceneNode* pParent = parent_->getParent();
        while (pParent != 0 && !pParent->flag_property_.queryProperty(E_WORLD_FRAME)) {
            EMatrix4 mat_accumed(_out_mat);
            EMatrix4::multiply(_out_mat, mat_accumed, pParent->getTransformRelativeToParent());
            pParent = pParent->getParent();
        }
    }

    //! gets transform relatvie to parent
    const EMatrix4& getTransformRelativeToParent() const {
        return local_tm_;
    }
};

}

#endif	//_ESCENE_NODE_H__

// vim: ts=4:sw=4
