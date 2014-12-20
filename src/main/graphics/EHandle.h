// Copyright (C) 2005-2014 The END Authors. All rights reserved.
//
// This file is part of the "END" (Engine for Dimensions).
// You can use this source code under the New BSD license
// that can be found in the LICENSE file.
// 이 파일은 "END" 의 일부분입니다.
// 소스코드는 New BSD license 에따라 사용이 가능합니다.

#ifndef _EHANDLE_H__
#define _EHANDLE_H__

#include <string>
#include <map>
#include <vector>

#include "EChunkArray.h"

namespace end2 {

//! Handle Class
template<typename T_HandleIdentifyType>
class EHandle {

private:
    // key and object id
    int key_;
    unsigned int object_id_;

public:

    typedef T_HandleIdentifyType HANDLE_IDENTIFY_TYPE;

    //! constructor
    explicit EHandle() :
            key_(-1), object_id_(0) {
    }

    //! constructor
    explicit EHandle(int _key, unsigned int _object_id) :
            key_(_key), object_id_(_object_id) {
    }

    //! constructor
    EHandle(const EHandle& _rhs) :
            key_(_rhs.key_), object_id_(_rhs.object_id_) {
    }

    //! destructor
    ~EHandle() {
    }

    //! gets handle key
    int getKey() const {
        return key_;
    }

    //! queries whether a valid key or not
    bool hasValidKey() const {
        return (key_ != -1);
    }

    //! gets a handle object id
    unsigned int getObjectId() const {
        return object_id_;
    }

    //! resets handle
    void reset(int _key, unsigned int _object_id) {
        key_ = _key;
        object_id_ = _object_id;
    }
};

//! Handle Management Class
template<typename T_Handle, typename T_HandleValueClassType>
class EHandleManager {
public:

    //! constructor
    EHandleManager(unsigned int _handle_value_chunck_element_size = 10) :
            handle_values_(_handle_value_chunck_element_size), handle_value_id_index_(0) {
    }

    //! creates a handle
    const T_Handle& createHandle(T_HandleValueClassType& _handle_value) {
        return createHandle_(&_handle_value);
    }

    //! gets extra infomations
    T_HandleValueClassType* getHandleValuePtr(const T_Handle& _handle) {
        if(!isValidHandle(_handle)){
            return 0;
        }
        return used_handles_[_handle.getKey()].second;
    }

    //! destroy a handle
    bool destroyHandle(const T_Handle& _handle) {
        if(!isValidHandle(_handle)) {
            return false;
        }

        int handle_key = _handle.getKey();

        used_handles_[handle_key].first.reset(-1, 0);
        handle_values_.destructData(handle_key);

        unused_handles_.push_back(handle_key);
        return true;
    }

    //! checks the validation
    bool isValidHandle(const T_Handle& _handle) {
        int handle_key = _handle.getKey();
        if(handle_key < 0) {
            return false;
        }

        if(handle_key >= (int) used_handles_.size()) {
            return false;
        }

        T_Handle& used_handle = used_handles_[handle_key].first;
        if(used_handle.getKey() < 0) {
            return false;
        }

        if(_handle.getObjectId() != used_handle.getObjectId()) {
            return false;
        }

        return true;
    }

    //! clears the handle
    void getValidHandleValues(
            std::vector<T_HandleValueClassType*>& _out_valid_handle_values) {
        unsigned int used_handle_size = used_handles_.size();
        for(unsigned int i = 0; i < used_handle_size; ++i) {
            if(false == isValidHandle(used_handles_[i].first)) {
                continue;
            }
            _out_valid_handle_values.push_back(used_handles_[i].second);
        }
    }

    void clearHandles() {
        unsigned int used_handle_size = used_handles_.size();
        for(unsigned int i = 0; i < used_handle_size; ++i) {
            T_Handle& handle = used_handles_[i].first;
            if(isValidHandle(handle)) {
                handle_values_.destructData(handle.getKey());
            }
        }

        used_handles_.clear();
        unused_handles_.clear();
        handle_values_.clear();
    }

protected:

    //! handle-value pair
    typedef std::pair<T_Handle, T_HandleValueClassType*> T_HandleValuePair;

    //! used handles
    std::vector<T_HandleValuePair> used_handles_;

    //! unused handles
    std::vector<int> unused_handles_;

    //! handle values
    EChunkArray<T_HandleValueClassType> handle_values_;

    //! the handle value id index
    unsigned int handle_value_id_index_;

    //! creates a handle
    const T_Handle& createHandle_(T_HandleValueClassType* _handle_value) {
        if(unused_handles_.empty()) {
            int cnt = (int) used_handles_.size();

            T_HandleValueClassType* assigned_handle_value_ptr = _handle_value ?
                (T_HandleValueClassType*) (handle_values_.constructData(*_handle_value)) :
                (T_HandleValueClassType*) (handle_values_.allocateBuffer());

            used_handles_.push_back(T_HandleValuePair(T_Handle(cnt, handle_value_id_index_),assigned_handle_value_ptr));

            ++handle_value_id_index_;
            return used_handles_[cnt].first;
        } else {
            int idx = *unused_handles_.rbegin();
            unused_handles_.pop_back();

            char* buf_ptr = handle_values_.getBufferPtr(idx);
            T_HandleValueClassType* assigned_handle_value_ptr = _handle_value ?
                (T_HandleValueClassType*) (handle_values_.constructData(*_handle_value, buf_ptr)) :
                (T_HandleValueClassType*) (buf_ptr);

            T_HandleValuePair& handle_value_pair = used_handles_[idx];
            handle_value_pair.first.reset(idx, handle_value_id_index_);
            handle_value_pair.second = assigned_handle_value_ptr;

            ++handle_value_id_index_;
            return handle_value_pair.first;
        }
    }
};

}

#endif //_EHANDLE_H__

// vim: ts=4:sw=4
