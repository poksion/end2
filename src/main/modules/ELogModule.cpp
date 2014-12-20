// Copyright (C) 2005-2014 The END Authors. All rights reserved.
//
// This file is part of the "END" (Engine for Dimensions).
// You can use this source code under the New BSD license
// that can be found in the LICENSE file.
// 이 파일은 "END" 의 일부분입니다.
// 소스코드는 New BSD license 에따라 사용이 가능합니다.

#include "ELogModule.h"

#ifdef _WIN32
#include "windows.h"
#include "mmsystem.h"
#endif

#ifdef __ANDROID_API__
#include <android/log.h>
#define LOG_TAG "end2"
#define LOG_D(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOG_I(...) __android_log_print(ANDROID_LOG_INFO,  LOG_TAG, __VA_ARGS__)
#define LOG_W(...) __android_log_print(ANDROID_LOG_WARN,  LOG_TAG, __VA_ARGS__)
#define LOG_E(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#endif

namespace end2 {

void ELogModule::onPostSetMessage_() {
    std::string& log_message = string_util_.getString();

    if(log_listener_) {
        log_listener_->onLog(log_message);
    }

    if(is_enable_console_out_) {
        size_t length = log_message.length();
        if((length > 0) && (log_message[length - 1] == '\n')) {
#ifdef __ANDROID_API__
            switch(log_level_){
                case(E_LV_DEBUG) : {
                    LOG_D( log_message.c_str() );
                }
                break;
                case(E_LV_INFO) : {
                    LOG_I( log_message.c_str() );
                }
                break;
                case(E_LV_WARN) : {
                    LOG_W( log_message.c_str() );
                }
                break;
                case(E_LV_ERROR) : {
                    LOG_E( log_message.c_str() );
                }
                break;
            }
#else
            std::cout << log_message;
            std::cout.flush();
#endif

#ifdef _MSC_VER
            OutputDebugString( log_message.c_str() );
#endif
        } else {
#ifdef __ANDROID_API__
            switch(log_level_){
                case(E_LV_DEBUG) : {
                    LOG_D( log_message.c_str() );
                }
                break;
                case(E_LV_INFO) : {
                    LOG_I( log_message.c_str() );
                }
                break;
                case(E_LV_WARN) : {
                    LOG_W( log_message.c_str() );
                }
                break;
                case(E_LV_ERROR) : {
                    LOG_E( log_message.c_str() );
                }
                break;
            }
#else
            std::cout << log_message << std::endl;
#endif

#ifdef _MSC_VER
            OutputDebugString( (log_message + '\n').c_str() );
#endif
        }
    }
}

}

// vim: ts=4:sw=4
