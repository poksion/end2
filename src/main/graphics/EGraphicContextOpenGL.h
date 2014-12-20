// Copyright (C) 2005-2014 The END Authors. All rights reserved.
//
// This file is part of the "END" (Engine for Dimensions).
// You can use this source code under the New BSD license
// that can be found in the LICENSE file.
// 이 파일은 "END" 의 일부분입니다.
// 소스코드는 New BSD license 에따라 사용이 가능합니다.

#ifndef _EGRAPHIC_CONTEXT_OPENGL_H__
#define _EGRAPHIC_CONTEXT_OPENGL_H__

#include <vector>

#include "EGraphicContext.h"
#include "EHandle.h"
#include "EImageBuffer.h"

namespace end2 {

class EGraphicContextOpenGL : public EGraphicContext {

//! Dependency Injection
public:
    class Delegate {
    public:
        virtual void flip() = 0;
    };

    void setDelegate(Delegate* _delegate){
        delegate_ = _delegate;
    }

private:
    Delegate* delegate_;

private:
    int display_width_;
    int display_height_;
    float projection_tm_[16];
    float view_tm_[16];

    class EOpenGLTextureInfo {
    public:
        EOpenGLTextureInfo(int _textureId, bool _usingMipmap) {
            textureId = _textureId;
            isUsingMipmap = _usingMipmap;
        }

        unsigned int textureId;
        bool isUsingMipmap;
    };
    EHandleManager<ETextureHandle, EOpenGLTextureInfo> texture_handle_mgr_;
    EImageBuffer locked_texture_;
    int activated_texture_stage_;

    std::vector<unsigned int> gl_image_format_indices_;
    std::vector<unsigned int> gl_light_indices_;
    std::vector<unsigned int> gl_texture_indices_;

public:

    //! constructor
    EGraphicContextOpenGL();

    //! destructor
    virtual ~EGraphicContextOpenGL();

    //! called on device life cycle
    virtual void init();
    virtual void halt();
    virtual void invalidate();

    //! gets the device description (OpenGL)
    virtual const char* getDeviceDesc() const {
        return "OpenGL";
    }

    //! gets the device raw pointer
    virtual void* getDeviceRawPtr() const {
        return 0;
    }

    //! sets display size
    virtual void setDisplaySize(int _width, int _height);

    //! gets display size
    virtual void getDisplaySize(int& _width, int& _height);

    //! sets view port
    virtual void setViewPort(
            int _upper_left_x,
            int _upper_left_y,
            int _lower_right_x,
            int _lower_right_y);

    //////////////////////////////////////////////////////////////////////

    //! clears buffers
    virtual void clearBuffers();

    //! before drawing
    virtual bool beginDrawing();

    //! after drawing
    virtual void endDrawing();

    //! flps to current display
    virtual void flip();

    //////////////////////////////////////////////////////////////////////

    //! sets view projection transform (from camera)
    virtual void setViewProjectionTransform(const float* _4x4ViewMatrix, const float* _4x4ProjectionMatrix);

    //! sets world transform
    virtual void setWorldTransform(const float* _4x4WorldMatrix);

    //////////////////////////////////////////////////////////////////////

    //! draws geometry buffer
    virtual void drawGeometryBuffer(const EGeometryBuffer& _geometry_buffer);

    //////////////////////////////////////////////////////////////////////

    //! sets graphic command buffer
    virtual void setGraphicCmdBuffer(const EGraphicCmdBuffer& _graphic_cmd_buffer);

    //////////////////////////////////////////////////////////////////////

    //! creates vertex buffer resource
    virtual EVertexHandle createVertex(const EGeometryBuffer& _geometry_buffer);
    virtual bool destroyVertex(const EVertexHandle& _vertex_handle);

    //! create texture resource
    virtual ETextureHandle createTexture(const EImageBuffer& _image_buffer, bool _building_mipmap);
    virtual bool setTexture(int _stage, const ETextureHandle& _texture_handle, bool _using_default_filter);
    virtual void destroyTexture(const ETextureHandle& _texture_handle);
};

}

#endif //_EGRAPHIC_CONTEXT_OPENGL_H__

// vim: ts=4:sw=4
