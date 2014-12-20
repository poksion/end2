// Copyright (C) 2005-2014 The END Authors. All rights reserved.
//
// This file is part of the "END" (Engine for Dimensions).
// You can use this source code under the New BSD license
// that can be found in the LICENSE file.
// 이 파일은 "END" 의 일부분입니다.
// 소스코드는 New BSD license 에따라 사용이 가능합니다.

#ifndef _EGEOMETRY_BUFFER_VALIDATOR_H__
#define _EGEOMETRY_BUFFER_VALIDATOR_H__

#include "../main/system/EAssert.h"
#include "../main/graphics/EGeometryBuffer.h"

namespace end2 {

//! Validator for EGeometryBuffer
class EGeometryBufferValidator {
public:

    //! constructor
    EGeometryBufferValidator() {
    }

    //! constructor
    EGeometryBufferValidator(const EGeometryBuffer& _buffer) {
        setAssignedGeometryBufferToCheck(_buffer);
    }

    //! destructor
    virtual ~EGeometryBufferValidator() {
    }

    //! sets the geometry buffer
    void setAssignedGeometryBufferToCheck(const EGeometryBuffer& _buffer) {
        size_t vcount, voffset, icount, ioffset;
        const void* buf_ptr;
        _buffer.getBufferInfo(&vcount, &voffset, &buf_ptr, &icount, &ioffset, &buf_ptr);

        for(int i = 0; i < EGeometryBuffer::E_FORMAT_NUM; ++i) {
            if(false == _buffer.hasFormat((EGeometryBuffer::FORMAT) i)) {
                continue;
            }

            if(EGeometryBuffer::E_TFACTOR == i) {
                continue;
            }

            formatFlags_[i].resize(vcount, 0);
        }

        if(icount > 0) {
            ibufferFlag_.resize(icount, 0);
        }
    }

    //! sets a flag for vertex buffer
    void setFlagVertexBuffer(EGeometryBuffer::FORMAT _format, size_t _vbuffer_index) {
        EASSERT(formatFlags_[_format].size() > _vbuffer_index);
        formatFlags_[_format][_vbuffer_index] = 1;
    }

    //! sets a flag for index buffer
    void setFlagIndexBuffer(size_t _ibuffer_index) {
        EASSERT(ibufferFlag_.size() > _ibuffer_index);
        ibufferFlag_[_ibuffer_index] = 1;
    }

    //! checks whether related geometry buffer is valid
    bool checkValidation();

    //! clear flags
    void clearFlags() {
        for(int i = 0; i < EGeometryBuffer::E_FORMAT_NUM; ++i) {
            formatFlags_[i].clear();
        }

        ibufferFlag_.clear();
    }

private:

    std::vector<int> formatFlags_[EGeometryBuffer::E_FORMAT_NUM];
    std::vector<int> ibufferFlag_;
};

}

#endif	//_EGEOMETRY_BUFFER_VALIDATOR_H__

// vim: ts=4:sw=4
