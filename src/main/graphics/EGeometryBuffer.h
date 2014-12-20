// Copyright (C) 2005-2014 The END Authors. All rights reserved.
//
// This file is part of the "END" (Engine for Dimensions).
// You can use this source code under the New BSD license
// that can be found in the LICENSE file.
// 이 파일은 "END" 의 일부분입니다.
// 소스코드는 New BSD license 에따라 사용이 가능합니다.

#ifndef _EGEOMETRY_BUFFER_H__
#define _EGEOMETRY_BUFFER_H__

#include <limits.h>
#include <vector>
#include "EMemoryBuffer.h"

namespace end2 {

typedef std::pair<size_t, size_t> EIndexBufferGroupPair;
typedef std::vector<EIndexBufferGroupPair> EIndexBufferGroups;

//! Memory buffer for Geometry
class EGeometryBuffer {
public:

    //////////////////////////////////////////////////////////////////////

    //! Geometry Type
    enum TYPE {
        E_LINE_LIST,
        E_TRIANGLE_LIST,

        E_TYPE_NUM
    };

    //! Geometry format. Geometry can have more than one format
    enum FORMAT {
        E_XYZ = 0,
        E_NORMAL,
        E_UV,
        E_TFACTOR,

        E_FORMAT_NUM
    };

private:

    bool is_assignable_;
    EMemoryBuffer vertex_buffer_;
    EMemoryBuffer index_buffer_;
    EIndexBufferGroups index_buffer_groups_;
    int tfactor_color_[4];

    // type and format
    TYPE geometry_type_;
    int format_offset_[E_FORMAT_NUM];

    // vertex and index information
    size_t vertices_count_;
    size_t vbuffer_offset_size_;
    size_t indices_count_;
    size_t ibuffer_offset_size_;

    bool setValue_(
            FORMAT format, size_t _vbuffer_index,
            float _v1, float _v2, float _v3) {

        if(!hasFormat(format)){
            return false;
        }

        if(!(format == E_XYZ || format == E_NORMAL || format == E_UV)) {
            return false;
        }

        const size_t offset = _vbuffer_index * vbuffer_offset_size_ + format_offset_[format];
        float* value_ptr = (float*) (vertex_buffer_.getPtr(offset));
        if(format == E_UV) {
            value_ptr[0] = _v1;
            value_ptr[1] = _v2;
        } else {
            value_ptr[0] = _v1;
            value_ptr[1] = _v2;
            value_ptr[2] = _v3;
        }
        return true;
    }

    void initBufferInfo_() {
        is_assignable_ = true;
        geometry_type_ = E_TYPE_NUM;
        vertices_count_ = 0;
        vbuffer_offset_size_ = 0;
        indices_count_ = 0;
        ibuffer_offset_size_ = 0;

        for (int i = 0; i < E_FORMAT_NUM; ++i) {
            // -1 means null value
            format_offset_[i] = -1;
        }
    }

public:

    //////////////////////////////////////////////////////////////////////

    //! constructor
    EGeometryBuffer() {
        initBufferInfo_();
    }

    //! constructor
    EGeometryBuffer(const EGeometryBuffer& _rSrc) {
        is_assignable_ = false;
        vertex_buffer_ = _rSrc.vertex_buffer_;
        index_buffer_ = _rSrc.index_buffer_;
        index_buffer_groups_ = _rSrc.index_buffer_groups_;
        for(int i = 0; i < 4; ++i) {
            tfactor_color_[i] = _rSrc.tfactor_color_[i];
        }
        geometry_type_ = _rSrc.geometry_type_;
        for(int i = 0; i < E_FORMAT_NUM; ++i) {
            format_offset_[i] = _rSrc.format_offset_[i];
        }

        vertices_count_ = _rSrc.vertices_count_;
        vbuffer_offset_size_ = _rSrc.vbuffer_offset_size_;
        indices_count_ = _rSrc.indices_count_;
        ibuffer_offset_size_ = _rSrc.ibuffer_offset_size_;
    }

    //! destructor
    virtual ~EGeometryBuffer() {
    }

    //////////////////////////////////////////////////////////////////////

    //! gets type
    TYPE getType() const {
        return geometry_type_;
    }

    //! queries having the format
    bool hasFormat(FORMAT _format) const {
        return (format_offset_[_format] != -1);
    }

    //! gets format offset.
    int getFormatOffset(FORMAT _format) const {
        return format_offset_[_format];
    }

    //////////////////////////////////////////////////////////////////////

    //! queries assignable
    bool isAssignable() const {
        return is_assignable_;
    }

    //! assigns
    bool assign(
            size_t _vertices_count,
            size_t _indices_count = 0,
            TYPE _type = E_TRIANGLE_LIST,
            bool _xyz = true,
            bool _normal = true,
            bool _uv = true,
            bool _tfactor = true) {

        if(!is_assignable_) {
            return false;
        }

        // set type
        geometry_type_ = _type;

        // set format
        if(_xyz) {
            format_offset_[E_XYZ] = vbuffer_offset_size_;
            vbuffer_offset_size_ += (sizeof(float)*3);
        }
        if(_tfactor) {
            format_offset_[E_TFACTOR] = 0;
        }
        if(_normal) {
            format_offset_[E_NORMAL] = vbuffer_offset_size_;
            vbuffer_offset_size_ += (sizeof(float)*3);
        }
        if(_uv) {
            format_offset_[E_UV] = vbuffer_offset_size_;
            vbuffer_offset_size_ += (sizeof(float)*2);
        }

        if(vbuffer_offset_size_ == 0) {
            return false;
        }
        // for vertices
        vertices_count_ = _vertices_count;
        if(!vertex_buffer_.assign(vertices_count_ * vbuffer_offset_size_,true)) {
            return false;
        }

        // for indices
        indices_count_ = _indices_count;
        if(_indices_count > 0) {
            if(USHRT_MAX != 65535){
                return false;
            }
            // since ibuffer has vertex buffer index,
            // ibuffer data type depends on vertices count
            if(_vertices_count > USHRT_MAX) {
                ibuffer_offset_size_ = sizeof(unsigned int);
            } else {
                ibuffer_offset_size_ = sizeof(unsigned short);
            }

            if(!index_buffer_.assign(_indices_count * ibuffer_offset_size_, true)) {
                return false;
            }
        }

        is_assignable_ = false;
        return true;
    }

    //////////////////////////////////////////////////////////////////////

    //! sets the TFactor value
    bool setTFactor(int _r, int _g, int _b, int _a = -1) {
        if(!hasFormat(E_TFACTOR)){
            return false;
        }
        tfactor_color_[0] = _r;
        tfactor_color_[1] = _g;
        tfactor_color_[2] = _b;
        tfactor_color_[3] = _a;

        return true;
    }

    //! gets the TFactor value
    const int* getTFactorAsRGBA() const {
        return tfactor_color_;
    }

    //! sets the XYZ value
    bool setXYZ(size_t _vbuffer_index, float _x, float _y, float _z) {
        return setValue_(E_XYZ, _vbuffer_index, _x, _y, _z);
    }

    //! gets the XYZ value
    float* getXYZ(size_t _vbuffer_index) {
        if(!hasFormat(E_XYZ) || format_offset_[E_XYZ] != 0){
            return 0;
        }
        const size_t offset = _vbuffer_index * vbuffer_offset_size_;
        return ((float*) (vertex_buffer_.getPtr(offset)));
    }

    //! sets the normal value
    bool setNormal(size_t _vbuffer_index, float _x, float _y, float _z) {
        return setValue_(E_NORMAL, _vbuffer_index, _x, _y, _z);
    }

    //! sets the UV value
    bool setUV(size_t _vbuffer_index, float _u, float _v) {
        return setValue_(E_UV, _vbuffer_index, _u, _v, 0.f);
    }

    //////////////////////////////////////////////////////////////////////

    //! sets index buffer
    bool setIndexBuffer(size_t _ibuffer_index, size_t _vbuffer_index) {
        if(_ibuffer_index >= indices_count_){
            return false;
        }
        if(isShortIndexBuffer()) {
            ((unsigned short*) index_buffer_.getPtr())[_ibuffer_index] =
                    (unsigned short) _vbuffer_index;
        } else {
            ((unsigned int*) index_buffer_.getPtr())[_ibuffer_index] =
                    (unsigned int) _vbuffer_index;
        }
        return false;
    }

    //! gets index buffer value ( = vbuffer index number)
    unsigned int getIndexBufferValue(size_t _ibuffer_index) const {
        if(_ibuffer_index >= indices_count_){
            return 0;
        }
        if(isShortIndexBuffer()) {
            unsigned short idx =
                    ((unsigned short*) index_buffer_.getPtr())[_ibuffer_index];
            return (unsigned int) idx;
        }
        return ((unsigned int*) index_buffer_.getPtr())[_ibuffer_index];
    }

    //! queries whether
    bool isShortIndexBuffer() const {
        return (ibuffer_offset_size_ == sizeof(unsigned short));
    }

    //////////////////////////////////////////////////////////////////////

    //! adds index buffer group
    void addIndexBufferGroup(size_t _start_ibuffer_index, size_t _draw_count) {
        index_buffer_groups_.push_back(
                EIndexBufferGroupPair(_start_ibuffer_index, _draw_count));
    }

    //! gets index buffer group
    const EIndexBufferGroups& getIndexBufferGroups() const {
        return index_buffer_groups_;
    }

    //////////////////////////////////////////////////////////////////////

    //! gets buffer info
    void getBufferInfo(size_t* _vcount, size_t* _voffset_size, const void** _vb,
            size_t* _icount, size_t* _ioffset_size, const void** _ib) const {
        *_vcount = vertices_count_;
        *_voffset_size = vbuffer_offset_size_;
        *_vb = vertex_buffer_.getPtr();

        *_icount = indices_count_;
        *_ioffset_size = ibuffer_offset_size_;
        *_ib = index_buffer_.getPtr();
    }

    //! clears buffer
    void clear() {
        initBufferInfo_();

        index_buffer_groups_.clear();
        vertex_buffer_.clear();
        index_buffer_.clear();
    }

    //////////////////////////////////////////////////////////////////////

};

}

#endif	//_EGEOMETRY_BUFFER_H__// vim: ts=4:sw=4
