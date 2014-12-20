// Copyright (C) 2005-2014 The END Authors. All rights reserved.
//
// This file is part of the "END" (Engine for Dimensions).
// You can use this source code under the New BSD license
// that can be found in the LICENSE file.
// 이 파일은 "END" 의 일부분입니다.
// 소스코드는 New BSD license 에따라 사용이 가능합니다.

#include "EGraphicContextOpenGL.h"

#include "EGeometryBuffer.h"
#include "EImageBuffer.h"
#include "EGraphicCmdBuffer.h"

#ifdef __APPLE__
#include "GLee/GLee.h"

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

// for gluBuild2DMipmaps
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#endif // __APPLE__

#ifdef __ANDROID_API__
#include <GLES/gl.h>
#endif

namespace end2 {

enum E_MATRIX4_INDEX {
    _11=0,  _12=4,  _13=8,  _14=12,
    _21=1,  _22=5,  _23=9,  _24=13,
    _31=2,  _32=6,  _33=10, _34=14,
    _41=3,  _42=7,  _43=11, _44=15,

    _MAX=16
};

EGraphicContextOpenGL::EGraphicContextOpenGL()
: delegate_(0)
, display_width_(-1)
, display_height_(-1)
, activated_texture_stage_(-1) {

    // build GL image format index
    gl_image_format_indices_.push_back(0);
    gl_image_format_indices_.push_back(GL_LUMINANCE);
    gl_image_format_indices_.push_back(GL_LUMINANCE_ALPHA);
    gl_image_format_indices_.push_back(GL_RGB);
    gl_image_format_indices_.push_back(GL_RGBA);

    // build GL ligth index
    gl_light_indices_.push_back(GL_LIGHT0);
    gl_light_indices_.push_back(GL_LIGHT1);
    gl_light_indices_.push_back(GL_LIGHT2);
    gl_light_indices_.push_back(GL_LIGHT3);

    // build GL texture index
    gl_texture_indices_.push_back(GL_TEXTURE0);
    gl_texture_indices_.push_back(GL_TEXTURE1);
    gl_texture_indices_.push_back(GL_TEXTURE2);
    gl_texture_indices_.push_back(GL_TEXTURE3);
}

EGraphicContextOpenGL::~EGraphicContextOpenGL() {
}

void EGraphicContextOpenGL::init() {

#ifndef __ANDROID_API__
      // init GLee for extentions
      GLeeInit();
#endif

      // default depth test
      glDepthFunc(GL_LESS);
      glEnable(GL_DEPTH_TEST);
      glEnable(GL_CULL_FACE);
      glFrontFace(GL_CCW);
      //glCullFace(GL_BACK);

      // default color shading
      glShadeModel(GL_SMOOTH);

      // default color material
      glEnable( GL_COLOR_MATERIAL );
#ifndef __ANDROID_API__
      // not support in OpenGLES
      // http://www.idevgames.com/forums/thread-744.html
      // (only support diffuse color)
      glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
#endif
}

void EGraphicContextOpenGL::halt() {
    std::vector<EOpenGLTextureInfo*> handle_values;
    texture_handle_mgr_.getValidHandleValues(handle_values);

    if(!handle_values.empty()) {
        // abnormal status
        size_t cnt = handle_values.size();
        for(size_t i = 0; i < cnt; ++i) {
            EOpenGLTextureInfo* texture_info = handle_values[i];
            glDeleteTextures(1, &(texture_info->textureId));
        }
        texture_handle_mgr_.clearHandles();
    }
}

void EGraphicContextOpenGL::invalidate() {

}

void EGraphicContextOpenGL::setDisplaySize(int _width, int _height) {
    display_width_ = _width;
    display_height_ = _height;

    glViewport(0,0,display_width_,display_height_);
}

void EGraphicContextOpenGL::getDisplaySize(int& _width, int& _height) {
    _width = display_width_;
    _height = display_height_;
}

void EGraphicContextOpenGL::setViewPort(int _upper_left_x, int _upper_left_y, int _lower_right_x, int _lower_right_y) {
    glViewport(_upper_left_x,_upper_left_y,_lower_right_x,_lower_right_y);
}

void EGraphicContextOpenGL::setViewProjectionTransform(const float* _4x4ViewMatrix, const float* _4x4ProjectionMatrix) {
    if(_4x4ViewMatrix != 0){
        for(int i = 0; i < 16; ++i){
            view_tm_[i] = _4x4ViewMatrix[i];
        }
    }

    if(_4x4ProjectionMatrix != 0){
        for(int i = 0; i < 16; ++i){
            projection_tm_[i] = _4x4ProjectionMatrix[i];
        }

        // from irrichit, flip z to compensate OpenGLs right-hand coordinate system
        projection_tm_[_14] *= -1.f;

        glMatrixMode(GL_PROJECTION);
        glLoadMatrixf(projection_tm_);
    }
}

void EGraphicContextOpenGL::setWorldTransform(const float* _4x4WorldMatrix) {
    float model_view[16];

    model_view[_11] = view_tm_[_11]*_4x4WorldMatrix[_11] + view_tm_[_12]*_4x4WorldMatrix[_21] + view_tm_[_13]*_4x4WorldMatrix[_31] + view_tm_[_14]*_4x4WorldMatrix[_41];
    model_view[_21] = view_tm_[_21]*_4x4WorldMatrix[_11] + view_tm_[_22]*_4x4WorldMatrix[_21] + view_tm_[_23]*_4x4WorldMatrix[_31] + view_tm_[_24]*_4x4WorldMatrix[_41];
    model_view[_31] = view_tm_[_31]*_4x4WorldMatrix[_11] + view_tm_[_32]*_4x4WorldMatrix[_21] + view_tm_[_33]*_4x4WorldMatrix[_31] + view_tm_[_34]*_4x4WorldMatrix[_41];
    model_view[_41] = view_tm_[_41]*_4x4WorldMatrix[_11] + view_tm_[_42]*_4x4WorldMatrix[_21] + view_tm_[_43]*_4x4WorldMatrix[_31] + view_tm_[_44]*_4x4WorldMatrix[_41];

    model_view[_12] = view_tm_[_11]*_4x4WorldMatrix[_12] + view_tm_[_12]*_4x4WorldMatrix[_22] + view_tm_[_13]*_4x4WorldMatrix[_32] + view_tm_[_14]*_4x4WorldMatrix[_42];
    model_view[_22] = view_tm_[_21]*_4x4WorldMatrix[_12] + view_tm_[_22]*_4x4WorldMatrix[_22] + view_tm_[_23]*_4x4WorldMatrix[_32] + view_tm_[_24]*_4x4WorldMatrix[_42];
    model_view[_32] = view_tm_[_31]*_4x4WorldMatrix[_12] + view_tm_[_32]*_4x4WorldMatrix[_22] + view_tm_[_33]*_4x4WorldMatrix[_32] + view_tm_[_34]*_4x4WorldMatrix[_42];
    model_view[_42] = view_tm_[_41]*_4x4WorldMatrix[_12] + view_tm_[_42]*_4x4WorldMatrix[_22] + view_tm_[_43]*_4x4WorldMatrix[_32] + view_tm_[_44]*_4x4WorldMatrix[_42];

    model_view[_13] = view_tm_[_11]*_4x4WorldMatrix[_13] + view_tm_[_12]*_4x4WorldMatrix[_23] + view_tm_[_13]*_4x4WorldMatrix[_33] + view_tm_[_14]*_4x4WorldMatrix[_43];
    model_view[_23] = view_tm_[_21]*_4x4WorldMatrix[_13] + view_tm_[_22]*_4x4WorldMatrix[_23] + view_tm_[_23]*_4x4WorldMatrix[_33] + view_tm_[_24]*_4x4WorldMatrix[_43];
    model_view[_33] = view_tm_[_31]*_4x4WorldMatrix[_13] + view_tm_[_32]*_4x4WorldMatrix[_23] + view_tm_[_33]*_4x4WorldMatrix[_33] + view_tm_[_34]*_4x4WorldMatrix[_43];
    model_view[_43] = view_tm_[_41]*_4x4WorldMatrix[_13] + view_tm_[_42]*_4x4WorldMatrix[_23] + view_tm_[_43]*_4x4WorldMatrix[_33] + view_tm_[_44]*_4x4WorldMatrix[_43];

    model_view[_14] = view_tm_[_11]*_4x4WorldMatrix[_14] + view_tm_[_12]*_4x4WorldMatrix[_24] + view_tm_[_13]*_4x4WorldMatrix[_34] + view_tm_[_14]*_4x4WorldMatrix[_44];
    model_view[_24] = view_tm_[_21]*_4x4WorldMatrix[_14] + view_tm_[_22]*_4x4WorldMatrix[_24] + view_tm_[_23]*_4x4WorldMatrix[_34] + view_tm_[_24]*_4x4WorldMatrix[_44];
    model_view[_34] = view_tm_[_31]*_4x4WorldMatrix[_14] + view_tm_[_32]*_4x4WorldMatrix[_24] + view_tm_[_33]*_4x4WorldMatrix[_34] + view_tm_[_34]*_4x4WorldMatrix[_44];
    model_view[_44] = view_tm_[_41]*_4x4WorldMatrix[_14] + view_tm_[_42]*_4x4WorldMatrix[_24] + view_tm_[_43]*_4x4WorldMatrix[_34] + view_tm_[_44]*_4x4WorldMatrix[_44];

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(model_view);
}

void EGraphicContextOpenGL::clearBuffers() {
    // Clear The Screen And The Depth Buffer
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
#ifdef __ANDROID_API__
    glClearDepthf(1.0);
#else
    glClearDepth(1.0);
#endif

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool EGraphicContextOpenGL::beginDrawing() {
    return true;
}

void EGraphicContextOpenGL::endDrawing() {
}

void EGraphicContextOpenGL::flip() {
    if(delegate_ != 0){
        delegate_->flip();
    }
}

//////////////////////////////////////////////////////////////////////

void EGraphicContextOpenGL::drawGeometryBuffer(const EGeometryBuffer& _geometry_buffer) {
    // for rendering device state restore
    bool enabled_alpha_blending = false;

    // Texture Factor
    if(_geometry_buffer.hasFormat(EGeometryBuffer::E_TFACTOR)) {
        const int* color4 = _geometry_buffer.getTFactorAsRGBA();

#ifdef __ANDROID_API__
        glColor4f(
            float(color4[0]) / float(255),
            float(color4[1]) / float(255),
            float(color4[2]) / float(255),
            color4[3] == -1? 1.0f : float(color4[3]) / float(255));
#else
        glColor3f(
            float(color4[0]) / float(255),
            float(color4[1]) / float(255),
            float(color4[2]) / float(255));
#endif

        if(color4[3] != -1) {
            enabled_alpha_blending = true;

            glEnable(GL_BLEND);
#ifdef __ANDROID_API__
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#else
            glBlendColor(1.f, 1.f, 1.f, float(color4[3]) / float(255));
            glBlendFunc(GL_CONSTANT_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA);
#endif

            glDisable(GL_DEPTH_TEST);
            glDisable(GL_CULL_FACE);
        }
    }

    // Draw Type
    GLenum eDrawType = GL_TRIANGLES;
    if(_geometry_buffer.getType() == EGeometryBuffer::E_LINE_LIST) {
        eDrawType = GL_LINES;
    }

    // Get Buffer Info
    size_t vertices_count, voffset_size, indices_count, ioffset_size;
    const void *vb, *ib;
    _geometry_buffer.getBufferInfo(
        &vertices_count, &voffset_size, &vb,
        &indices_count, &ioffset_size, &ib);

    // Set Vertex Format And Draw
    if(_geometry_buffer.hasFormat(EGeometryBuffer::E_XYZ)) {
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, voffset_size, vb);
    }

    if(_geometry_buffer.hasFormat(EGeometryBuffer::E_NORMAL)) {
        glEnableClientState(GL_NORMAL_ARRAY);
        glNormalPointer(
            GL_FLOAT,
            voffset_size,
            (const void*)((const char*)vb+_geometry_buffer.getFormatOffset(EGeometryBuffer::E_NORMAL)));
    }

    if(_geometry_buffer.hasFormat(EGeometryBuffer::E_UV)) {
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glTexCoordPointer(
            2,
            GL_FLOAT,
            voffset_size,
            (const void*)((const char*)vb+_geometry_buffer.getFormatOffset(EGeometryBuffer::E_UV)));
    }

    if(ib != 0) {
        GLenum eIndexType = GL_UNSIGNED_SHORT;
        if(false == _geometry_buffer.isShortIndexBuffer()) {
#ifndef __ANDROID_API__
            eIndexType = GL_UNSIGNED_INT;
#endif
        }

        const EIndexBufferGroups& ibuffer_groups = _geometry_buffer.getIndexBufferGroups();
        if(ibuffer_groups.empty()) {
            //glDrawRangeElements(eDrawType, 0, indices_count - 1, indices_count, eIndexType, ib);
            glDrawElements(eDrawType, indices_count, eIndexType, ib);
        } else {
            size_t i_start, i_count, i_end;
            const void* i_start_ptr;
            for(EIndexBufferGroups::const_iterator itr = ibuffer_groups.begin(); itr != ibuffer_groups.end(); ++itr) {
                i_start = itr->first;
                i_count = itr->second;
                i_end = i_count + i_start - 1;
                i_start_ptr = (const void*)((const char*) ib + ioffset_size * i_start);
                //glDrawRangeElements(eDrawType, i_start, i_end, i_count, eIndexType, i_start_ptr);
                glDrawElements(eDrawType, i_count, eIndexType, i_start_ptr);
            }
        }
    } else {
        glDrawArrays(eDrawType, 0, vertices_count);
    }

    // rendering device state restore
    if(enabled_alpha_blending) {
        glDisable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
    }
}

//////////////////////////////////////////////////////////////////////

void EGraphicContextOpenGL::setGraphicCmdBuffer(const EGraphicCmdBuffer& _graphic_cmd_buffer) {
    const EGraphicCmdBuffer::EGraphicCmdList& cmd_list = _graphic_cmd_buffer.getCmdList();
    EGraphicCmdBuffer::EGraphicCmdList::const_iterator itr = cmd_list.begin();
    while (itr != cmd_list.end()) {
        EGraphicCmdBuffer::E_CMD_TYPE cmd_type = itr->getType();
        switch (cmd_type) {
        case EGraphicCmdBuffer::E_LIGHT_ACTIVATE_AS_DIRECTIONAL: {
            int light_index;
            float dir[3];
            int ambient[4];
            int diffuse[4];
            EGraphicCmdBuffer::seekCmdLightActivateAsDirectional(itr, light_index, dir, ambient, diffuse);

            if(light_index < gl_light_indices_.size()) {
                unsigned int gl_light_index = gl_light_indices_[light_index];
                GLfloat light_values[4];

                glEnable(GL_LIGHTING);
                glEnable(gl_light_index);

                // set direction
                light_values[0] = dir[0];
                light_values[1] = dir[1];
                light_values[2] = dir[2];
                light_values[3] = 0.f;
                glLightfv(gl_light_index, GL_POSITION, light_values);

                // set ambient
                light_values[0] = float(ambient[0]) / float(255);
                light_values[1] = float(ambient[1]) / float(255);
                light_values[2] = float(ambient[2]) / float(255);
                light_values[3] = float(ambient[3]) / float(255);
                glLightfv(gl_light_index, GL_AMBIENT, light_values);

                // set diffuse
                light_values[0] = float(diffuse[0]) / float(255);
                light_values[1] = float(diffuse[1]) / float(255);
                light_values[2] = float(diffuse[2]) / float(255);
                light_values[3] = float(diffuse[3]) / float(255);
                glLightfv(gl_light_index, GL_DIFFUSE, light_values);
            }
            break;
        }
        default:
            // not defined command
            ++itr;
        }
    }
}

//////////////////////////////////////////////////////////////////////

EVertexHandle EGraphicContextOpenGL::createVertex(const EGeometryBuffer& _geometry_buffer) {
    return EVertexHandle(-1, 0);
}

bool EGraphicContextOpenGL::destroyVertex(const EVertexHandle& _vertex_handle){
    return false;
}

//////////////////////////////////////////////////////////////////////

ETextureHandle EGraphicContextOpenGL::createTexture(const EImageBuffer& _image_buffer, bool _building_mipmap) {

    // 2d texture. level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image
    unsigned char* image_data;
    size_t image_size;
    int width, height, image_channel_cnt;
    if(!_image_buffer.getBufferInfo(&image_data, &image_size, &width, &height, &image_channel_cnt)) {
        return ETextureHandle(-1, 0);
    }

    GLenum image_format = gl_image_format_indices_[image_channel_cnt];

    unsigned int texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    // check mipmap
    if(_building_mipmap) {
#ifdef __ANDROID_API__
        glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
        glTexImage2D(GL_TEXTURE_2D, 0, image_channel_cnt, width, height, 0, image_format, GL_UNSIGNED_BYTE, image_data);
#else
        // make texture with mipmap
        if(GLEE_VERSION_1_4) {
            glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
            glTexImage2D(GL_TEXTURE_2D, 0, image_channel_cnt, width, height, 0, image_format, GL_UNSIGNED_BYTE, image_data);
        } else {
            gluBuild2DMipmaps(GL_TEXTURE_2D, image_channel_cnt, width, height, image_format, GL_UNSIGNED_BYTE, image_data);
        }
#endif
    } else {
#ifdef __ANDROID_API__
        glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_FALSE);
#else
        if(GLEE_VERSION_1_4) {
            glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_FALSE);
        }
        glTexImage2D(GL_TEXTURE_2D, 0, image_channel_cnt, width, height, 0, image_format, GL_UNSIGNED_BYTE, image_data);
#endif
    }

    // generate texture handle and return it
    EOpenGLTextureInfo texture_info(texture_id, _building_mipmap);
    return texture_handle_mgr_.createHandle(texture_info);
}

bool EGraphicContextOpenGL::setTexture(int _stage, const ETextureHandle& _texture_handle, bool _using_default_filter) {
    if(false == texture_handle_mgr_.isValidHandle(_texture_handle)) {
        return false;
    }

    if(_stage < 0 || _stage >= (int) gl_texture_indices_.size())
        return false;

    if(activated_texture_stage_ != _stage) {
        activated_texture_stage_ = _stage;

        glDisable(GL_TEXTURE_2D);
        glActiveTexture(gl_texture_indices_[activated_texture_stage_]);
        glEnable(GL_TEXTURE_2D);
    }

    EOpenGLTextureInfo* texture_info = texture_handle_mgr_.getHandleValuePtr(_texture_handle);
    if(_using_default_filter) {
        if(texture_info->isUsingMipmap) {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        } else {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        }
    }

    glBindTexture(GL_TEXTURE_2D, texture_info->textureId);
    return true;
}

void EGraphicContextOpenGL::destroyTexture(const ETextureHandle& _texture_handle) {
    if(!texture_handle_mgr_.isValidHandle(_texture_handle)) {
        return;
    }

    EOpenGLTextureInfo* texture_info = texture_handle_mgr_.getHandleValuePtr(_texture_handle);
    glDeleteTextures(1, &(texture_info->textureId));

    texture_handle_mgr_.destroyHandle(_texture_handle);
}

}


// vim: ts=4:sw=4
