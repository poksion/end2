// Copyright (C) 2005-2014 The END Authors. All rights reserved.
//
// This file is part of the "END" (Engine for Dimensions).
// You can use this source code under the New BSD license
// that can be found in the LICENSE file.
// 이 파일은 "END" 의 일부분입니다.
// 소스코드는 New BSD license 에따라 사용이 가능합니다.

#ifndef _EMEMORY_BUFFER_H__
#define _EMEMORY_BUFFER_H__

#include <stdlib.h>	//for malloc#include <string.h>	//for memeset, memcpy ...
namespace end2 {

// The Memory Buffer
class EMemoryBuffer {

private:
    size_t size_;
    char* buffer_;

public:

    //! constructor
    EMemoryBuffer(size_t _size = 0, bool _is_using_memset_0 = false) {
        size_ = _size;
        buffer_ = 0;
        if (size_ > 0) {
            assign(_size, _is_using_memset_0);
        }
    }

    //! constructor
    EMemoryBuffer(const EMemoryBuffer& _src) {
        assign(_src.size_);
        memcpy(buffer_, _src.buffer_, _src.size_);
    }

    //! destructor
    virtual ~EMemoryBuffer() {
        clear();
    }

    //! assigns memories
    bool assign(size_t _size, bool _is_using_memset_0 = false) {
        if (buffer_) {
            clear();
        }

        size_ = _size;
        buffer_ = (char*) malloc(size_);
        if (0 == buffer_) {
            return false;
        }

        if (_is_using_memset_0) {
            memset(buffer_, 0, _size);
        }

        return true;
    }

    //! gets buffer size
    size_t getSize() {
        return size_;
    }

    //! gets raw memory pointer
    char* getPtr(size_t _offset) {
        if(size_ <= _offset){
            return 0;
        }
        return (buffer_ + _offset);
    }

    //! gets raw memory pointer
    const void* getPtr() const {
        return ((const void*) buffer_);
    }

    //! clears a buffer
    void clear() {
        delete buffer_;
        buffer_ = 0;
        size_ = 0;
    }
};

}

#endif	//_EMEMORY_BUFFER_H__
// vim: ts=4:sw=4
