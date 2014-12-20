// Copyright (C) 2005-2014 The END Authors. All rights reserved.
//
// This file is part of the "END" (Engine for Dimensions).
// You can use this source code under the New BSD license
// that can be found in the LICENSE file.
// 이 파일은 "END" 의 일부분입니다.
// 소스코드는 New BSD license 에따라 사용이 가능합니다.

#ifndef _ECHUNK_ARRAY_H__
#define _ECHUNK_ARRAY_H__

#include <vector>

#include <new>
#include <stdlib.h>

namespace end2 {

//! Chunk Array
template<typename T_ContentType>
class EChunkArray {

private:

    std::vector<char*> chunked_;
    unsigned int next_element_idx_;
    unsigned int chunk_size_;

public:

    //! constructor
    EChunkArray(unsigned int _chunk_element_cnt = 10) :
        next_element_idx_(0), chunk_size_(_chunk_element_cnt) {
    }

    ~EChunkArray() {
        clear();
    }

    unsigned int getSize() {
        return next_element_idx_;
    }

    char* allocateBuffer() {
        if(chunk_size_ == 0){
            return 0;
        }

        unsigned int available_element_size = chunked_.size() * chunk_size_;
        if(next_element_idx_ >= available_element_size) {
            chunked_.push_back((char*) malloc(sizeof(T_ContentType) * chunk_size_));
        }
        char* buf_ptr = getBufferPtr(next_element_idx_);
        next_element_idx_++;
        return buf_ptr;
    }

    char* getBufferPtr(unsigned int _idx) {
        if(_idx > next_element_idx_ || chunk_size_ == 0){
            return 0;
        }

        unsigned int chunk_idx = _idx / chunk_size_;
        if(chunk_idx >= chunked_.size()){
            return 0;
        }

        unsigned int element_idx = _idx - chunk_idx * chunk_size_;
        char* selected_chunk = chunked_[chunk_idx];

        return (selected_chunk + sizeof(T_ContentType) * element_idx);
    }

    T_ContentType* getDataPtr(unsigned int _idx) {
        return ((T_ContentType*) getBufferPtr(_idx));
    }

    void* constructData(const T_ContentType& _content, char* _buf_ptr = 0) {
        if(!_buf_ptr) {
            _buf_ptr = allocateBuffer();
        }
        return (void*) (new (_buf_ptr) T_ContentType(_content));
    }

    char* destructData(unsigned int _idx) {
        T_ContentType* content = getDataPtr(_idx);
        content->~T_ContentType();

        return (char*) (content);
    }

    void clear() {
        // free memory buffer
        for(typename std::vector<char*>::iterator itr = chunked_.begin(); itr != chunked_.end(); ++itr) {
            free(*itr);
        }

        chunked_.clear();
        next_element_idx_ = 0;
    }
};

}

#endif	//_ECHUNK_ARRAY_H__

// vim: ts=4:sw=4
