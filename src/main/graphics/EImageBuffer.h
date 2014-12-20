// Copyright (C) 2005-2014 The END Authors. All rights reserved.
//
// This file is part of the "END" (Engine for Dimensions).
// You can use this source code under the New BSD license
// that can be found in the LICENSE file.
// 이 파일은 "END" 의 일부분입니다.
// 소스코드는 New BSD license 에따라 사용이 가능합니다.

#ifndef _EIMAGE_BUFFER_H__
#define _EIMAGE_BUFFER_H__

#include <stdlib.h>

namespace end2 {

//! Memory buffer for Image
class EImageBuffer {

private:
    unsigned char* buffer_;
    size_t size_;

    int width_;
    int height_;
    int image_channel_cnt_;

    bool verifyBuffer_() const {
        if(0 == buffer_ || width_ <= 0 || height_ <= 0 || image_channel_cnt_ <= 0) {
            return false;
        }
        return true;
    }

public:

    //! constructor
    EImageBuffer() {
        resetBufferInfo();
    }

    //! constructor
    EImageBuffer(const EImageBuffer& _rSrc) {
        size_ = _rSrc.size_;
        width_ = _rSrc.width_;
        height_ = _rSrc.height_;
        image_channel_cnt_ = _rSrc.image_channel_cnt_;

        buffer_ = (unsigned char*) malloc(size_);
        memcpy(buffer_, _rSrc.buffer_, size_);
    }

    //! destructor
    virtual ~EImageBuffer() {
        free(buffer_);
    }

    //! gets the image buffer information
    bool getBufferInfo(
            unsigned char** _raw_buffer,
            size_t* _buffer_size,
            int* _width, int* _height,
            int* _image_channel_cnt) const {

        *_raw_buffer = buffer_;
        *_buffer_size = size_;

        *_width = width_;
        *_height = height_;
        *_image_channel_cnt = image_channel_cnt_;

        return verifyBuffer_();
    }

    //! sets the image buffer information
    bool setBufferInfo(
            unsigned char* _raw_buffer,
            int _width,
            int _height,
            int _image_channel_cnt) {

        if(0 != buffer_ || width_ != 0 || height_ != 0 || image_channel_cnt_ != 0) {
            return false;
        }

        buffer_ = _raw_buffer;
        width_ = _width;
        height_ = _height;
        image_channel_cnt_ = _image_channel_cnt;

        if(!verifyBuffer_()) {
            return false;
        }
        size_ = (size_t) (width_ * height_ * image_channel_cnt_);
        return true;
    }

    //! resets the image buffer information
    void resetBufferInfo() {
        buffer_ = 0;
        size_ = 0;

        width_ = 0;
        height_ = 0;
        image_channel_cnt_ = 0;
    }

    //! clears the image buffer
    void clear() {
        free(buffer_);
        resetBufferInfo();
    }

};

}

#endif //_EIMAGE_BUFFER_H__

// vim: ts=4:sw=4
