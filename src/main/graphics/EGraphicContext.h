// Copyright (C) 2005-2014 The END Authors. All rights reserved.
//
// This file is part of the "END" (Engine for Dimensions).
// You can use this source code under the New BSD license
// that can be found in the LICENSE file.
// 이 파일은 "END" 의 일부분입니다.
// 소스코드는 New BSD license 에따라 사용이 가능합니다.

#ifndef _EGRAPHIC_CONTEXT_H__
#define _EGRAPHIC_CONTEXT_H__

#include "EHandle.h"

namespace end2 {

class EGraphicCmdBuffer;

class EGeometryBuffer;
class EImageBuffer;

typedef EHandle<EGeometryBuffer> EVertexHandle;
typedef EHandle<EImageBuffer> ETextureHandle;

class EGraphicContext {
public:

    //! constructor
    EGraphicContext() {
    }

    //! destructor
    virtual ~EGraphicContext() {
    }

    //! called on graphic context life cycle
    virtual void init() = 0;
    virtual void halt() = 0;
    virtual void invalidate() = 0;

    //! gets the device description (OpenGL, D3D9, ...)
    virtual const char* getDeviceDesc() const = 0;

    //! gets the device raw pointer
    virtual void* getDeviceRawPtr() const = 0;

    //! sets display size
    virtual void setDisplaySize(int _width, int _height) = 0;

    //! gets display size
    virtual void getDisplaySize(int& _width, int& _height) = 0;

    //! sets view port
    virtual void setViewPort(
            int _upper_left_x,
            int _upper_left_y,
            int _lower_right_x,
            int _lower_right_y) = 0;

    //////////////////////////////////////////////////////////////////////

    //! clears buffers
    virtual void clearBuffers() = 0;

    //! before drawing
    virtual bool beginDrawing() = 0;

    //! after drawing
    virtual void endDrawing() = 0;

    //! flps to current display
    virtual void flip() = 0;

    //////////////////////////////////////////////////////////////////////

    //! sets view projection transform (from camera)
    virtual void setViewProjectionTransform(const float* _4x4ViewMatrix, const float* _4x4ProjectionMatrix) = 0;

    //! sets world transform
    virtual void setWorldTransform(const float* _4x4WorldMatrix) = 0;

    //////////////////////////////////////////////////////////////////////

    //! draws geometry buffer
    virtual void drawGeometryBuffer(const EGeometryBuffer& _geometry_buffer) = 0;

    //////////////////////////////////////////////////////////////////////

    //! sets graphic command buffer
    virtual void setGraphicCmdBuffer(const EGraphicCmdBuffer& _graphic_cmd_buffer) = 0;

    //////////////////////////////////////////////////////////////////////

    //! creates vertex buffer resource
    virtual EVertexHandle createVertex(const EGeometryBuffer& _geometry_buffer) = 0;
    virtual bool destroyVertex(const EVertexHandle& _vertex_handle) = 0;

    //! create texture resource
    virtual ETextureHandle createTexture(const EImageBuffer& _image_buffer, bool _building_mipmap) = 0;
    virtual bool setTexture(int _stage, const ETextureHandle& _texture_handle, bool _using_default_filter) = 0;
    virtual void destroyTexture(const ETextureHandle& _texture_handle) = 0;
};

}

#endif //_EGRAPHIC_CONTEXT_H__

// vim: ts=4:sw=4
