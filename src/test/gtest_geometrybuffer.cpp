// Copyright (C) 2005-2014 The END Authors. All rights reserved.
//
// This file is part of the "END" (Engine for Dimensions).
// You can use this source code under the New BSD license
// that can be found in the LICENSE file.
// 이 파일은 "END" 의 일부분입니다.
// 소스코드는 New BSD license 에따라 사용이 가능합니다.

#include <cute_end.h>

#include "../main/graphics/EGraphicContext.h"
#include "../main/graphics/EGeometryBuffer.h"

#include "../main/scenegraph/math/EMatrix4.h"
#include "../main/scenegraph/math/EVector3.h"
#include "../main/scenegraph/ECameraSceneNode.h"
#include "../main/scenegraph/ECameraUtil.h"
#include "../main/scenegraph/EDataSceneNode.h"

#include "../main/system/ESystem.h"

#include "../main/modules/EKeyboardModule.h"

#include "EGeometryBufferValidator.h"

using namespace end2;

class gtest_geometrybuffer: public CuteGraphicTest {
    ECameraSceneNode camera_;
    EDataSceneNode<EGeometryBuffer> geometrySceneNode_;

public:

    virtual void onCreate() {

        /*
            0------1
           /      /|   z
          /      / |   | / y
         3------2  5   |/
         |  4   | /    ----- x
         |      |/
         7------6

         */

        EGeometryBuffer& test_box_buffer = geometrySceneNode_.getData();
        bool is_ok = test_box_buffer.assign(8, 24, EGeometryBuffer::E_LINE_LIST, true, false, false, true);
        EASSERT(is_ok);
        EGeometryBufferValidator validator(test_box_buffer);
        // or
        // EGeometryBufferValidator validator;
        // validator.setAssignedGeometryBufferToCheck(test_box_buffer);
        // and to reset, validator.clearFlags();

        test_box_buffer.setXYZ(0, -1.f, +1.f, +1.f);
        validator.setFlagVertexBuffer(EGeometryBuffer::E_XYZ, 0);

        test_box_buffer.setXYZ(1, +1.f, +1.f, +1.f);
        validator.setFlagVertexBuffer(EGeometryBuffer::E_XYZ, 1);

        test_box_buffer.setXYZ(2, +1.f, -1.f, +1.f);
        validator.setFlagVertexBuffer(EGeometryBuffer::E_XYZ, 2);

        test_box_buffer.setXYZ(3, -1.f, -1.f, +1.f);
        validator.setFlagVertexBuffer(EGeometryBuffer::E_XYZ, 3);

        test_box_buffer.setXYZ(4, -1.f, +1.f, -1.f);
        validator.setFlagVertexBuffer(EGeometryBuffer::E_XYZ, 4);

        test_box_buffer.setXYZ(5, +1.f, +1.f, -1.f);
        validator.setFlagVertexBuffer(EGeometryBuffer::E_XYZ, 5);

        test_box_buffer.setXYZ(6, +1.f, -1.f, -1.f);
        validator.setFlagVertexBuffer(EGeometryBuffer::E_XYZ, 6);

        test_box_buffer.setXYZ(7, -1.f, -1.f, -1.f);
        validator.setFlagVertexBuffer(EGeometryBuffer::E_XYZ, 7);

        //////////////////////////////////////////////////////////////////////

        test_box_buffer.setIndexBuffer(0, 0);
        validator.setFlagIndexBuffer(0);

        test_box_buffer.setIndexBuffer(1, 1);
        validator.setFlagIndexBuffer(1);

        test_box_buffer.setIndexBuffer(2, 1);
        validator.setFlagIndexBuffer(2);

        test_box_buffer.setIndexBuffer(3, 2);
        validator.setFlagIndexBuffer(3);

        test_box_buffer.setIndexBuffer(4, 2);
        validator.setFlagIndexBuffer(4);

        test_box_buffer.setIndexBuffer(5, 3);
        validator.setFlagIndexBuffer(5);

        test_box_buffer.setIndexBuffer(6, 3);
        validator.setFlagIndexBuffer(6);

        test_box_buffer.setIndexBuffer(7, 0);
        validator.setFlagIndexBuffer(7);

        //////////////////////////////////////////////////////////////////////

        test_box_buffer.setIndexBuffer(8, 4);
        validator.setFlagIndexBuffer(8);

        test_box_buffer.setIndexBuffer(9, 5);
        validator.setFlagIndexBuffer(9);

        test_box_buffer.setIndexBuffer(10, 5);
        validator.setFlagIndexBuffer(10);

        test_box_buffer.setIndexBuffer(11, 6);
        validator.setFlagIndexBuffer(11);

        //////////////////////////////////////////////////////////////////////

        test_box_buffer.setIndexBuffer(12, 6);
        validator.setFlagIndexBuffer(12);

        test_box_buffer.setIndexBuffer(13, 7);
        validator.setFlagIndexBuffer(13);

        test_box_buffer.setIndexBuffer(14, 7);
        validator.setFlagIndexBuffer(14);

        test_box_buffer.setIndexBuffer(15, 4);
        validator.setFlagIndexBuffer(15);

        //////////////////////////////////////////////////////////////////////

        test_box_buffer.setIndexBuffer(16, 0);
        validator.setFlagIndexBuffer(16);

        test_box_buffer.setIndexBuffer(17, 4);
        validator.setFlagIndexBuffer(17);

        test_box_buffer.setIndexBuffer(18, 1);
        validator.setFlagIndexBuffer(18);

        test_box_buffer.setIndexBuffer(19, 5);
        validator.setFlagIndexBuffer(19);

        test_box_buffer.setIndexBuffer(20, 2);
        validator.setFlagIndexBuffer(20);

        test_box_buffer.setIndexBuffer(21, 6);
        validator.setFlagIndexBuffer(21);

        test_box_buffer.setIndexBuffer(22, 3);
        validator.setFlagIndexBuffer(22);

        test_box_buffer.setIndexBuffer(23, 7);
        validator.setFlagIndexBuffer(23);

        is_ok = validator.checkValidation();
        EASSERT(is_ok);

        test_box_buffer.setTFactor(255, 255, 255);

        // setup camera
        end2::EMatrix4 tempMatrix;

        // position
        end2::EVector3 pos(10, 0, 0);
        end2::EVector3 dir(-1, 0, 0);
        end2::EVector3 up(0, 0, 1);
        end2::EMatrix4::makeFrame(tempMatrix, pos, dir, up);
        camera_.setTransformRelativeToWorld(tempMatrix);

        // projection
        EGraphicContext* gc = end2::ESystem::getSystem().getModule<EGraphicContext>();
        int width, height;
        gc->getDisplaySize(width, height);
        camera_.updateProjection(width, height);

        // setup from camera
        gc->setViewProjectionTransform(camera_.getViewTransform().get(), camera_.getProjectionTransform().get());

        // setup data scene node
        geometrySceneNode_.setTransformRelativeToWorld(EMatrix4::IDENTITY);
    }

    virtual void onRender() {
        EKeyboardModule* km = ESystem::getSystem().getModule<EKeyboardModule>();
        EGraphicContext* gc = ESystem::getSystem().getModule<EGraphicContext>();

        if(km->isKeyDown(EKeyboardModule::E_KC_LEFT) ||
           km->isKeyDown(EKeyboardModule::E_KC_RIGHT) ||
           km->isKeyDown(EKeyboardModule::E_KC_UP) ||
           km->isKeyDown(EKeyboardModule::E_KC_DOWN) ){

            float horizontal_move = 0.f;
            if(km->isKeyDown(EKeyboardModule::E_KC_LEFT)){
                horizontal_move = 0.01f;
            }else if(km->isKeyDown(EKeyboardModule::E_KC_RIGHT)){
                horizontal_move = -0.01f;
            }
            float vertical_move = 0.f;
            if(km->isKeyDown(EKeyboardModule::E_KC_UP)){
                vertical_move = 0.01f;
            }else if(km->isKeyDown(EKeyboardModule::E_KC_DOWN)){
                vertical_move = -0.01f;
            }
            ECameraUtil::rotate(camera_, horizontal_move, vertical_move);
            gc->setViewProjectionTransform(camera_.getViewTransform().get(), 0);
        }
        gc->setWorldTransform(geometrySceneNode_.getTransformRelativeToParent().get());
        gc->drawGeometryBuffer(geometrySceneNode_.getData());
    }

    virtual void onDestroy() {
    }
};

CUTE_GRAPHIC_TEST(gtest_geometrybuffer);

// vim: ts=4:sw=4
