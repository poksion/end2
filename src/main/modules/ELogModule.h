// Copyright (C) 2005-2014 The END Authors. All rights reserved.
//
// This file is part of the "END" (Engine for Dimensions).
// You can use this source code under the New BSD license
// that can be found in the LICENSE file.
// 이 파일은 "END" 의 일부분입니다.
// 소스코드는 New BSD license 에따라 사용이 가능합니다.

#ifndef _ELOG_MODULE_H__
#define _ELOG_MODULE_H__

#include "third_party/EStringUtil.h"

#define ELOG end2::ESystem::getSystem().getModule<end2::ELogModule>()->log
#define ELOG_SAFE if(end2::ESystem::getSystem().getModule<end2::ELogModule>()) end2::ESystem::getSystem().getModule<end2::ELogModule>()->log

#ifdef _DEBUG
#define ELOG_DEBUG ELOG_SAFE
#else
#define ELOG_DEBUG end2::ELogModule::logNull
#endif

namespace end2 {

//! Log Listener. It is called when logging
class ELogListener {
public:

    //! constructor
    ELogListener() {
    }

    //! destructor
    virtual ~ELogListener() {
    }

    //! called on logged
    virtual void onLog(const std::string& _rStrMessage) = 0;
};

//! Logger
class ELogModule {
public:

    enum E_LOG_LEVEL {
        E_LV_DEBUG = 0,
        E_LV_INFO,
        E_LV_WARN,
        E_LV_ERROR
    };

    //! constructor
    ELogModule() : log_listener_(0), is_enable_console_out_(true), log_level_(E_LV_DEBUG) {
    }

    //! destructor
    virtual ~ELogModule() {
    }

    //! logger setter
    void setLogger(bool _is_enable_console_out = true, E_LOG_LEVEL _log_level = E_LV_DEBUG, ELogListener* _log_listener = 0) {
        is_enable_console_out_ = _is_enable_console_out;
        log_level_ = _log_level;
        log_listener_ = _log_listener;
    }

    //! null logging
    static void logNull(...) {
    }

    //! log
    template<typename T0>
    void log(T0 _t0) {
        log("{0}", _t0);
    }

    //! log
    void log(const char* _log_message) {
        onPreSetMessage_();
        string_util_.setStringFromCStr(_log_message);
        onPostSetMessage_();
    }

    //! log
    void log(const std::string& _log_message) {
        onPreSetMessage_();
        string_util_.setString(_log_message);
        onPostSetMessage_();
    }

    //! log
    template<typename T0>
    void log(const char* _log_message, T0 _t0) {
        onPreSetMessage_();
        string_util_.formatStr(_log_message, _t0);
        onPostSetMessage_();
    }

    //! log
    template<typename T0, typename T1>
    void log(const char* _log_message, T0 _t0, T1 _t1) {
        onPreSetMessage_();
        string_util_.formatStr(_log_message, _t0, _t1);
        onPostSetMessage_();
    }

    //! log
    template<typename T0, typename T1, typename T2>
    void log(const char* _log_message, T0 _t0, T1 _t1, T2 _t2) {
        onPreSetMessage_();
        string_util_.formatStr(_log_message, _t0, _t1, _t2);
        onPostSetMessage_();
    }

    //! log
    template<typename T0, typename T1, typename T2, typename T3>
    void log(const char* _log_message, T0 _t0, T1 _t1, T2 _t2, T3 _t3) {
        onPreSetMessage_();
        string_util_.formatStr(_log_message, _t0, _t1, _t2, _t3);
        onPostSetMessage_();
    }

    //! log
    template<typename T0, typename T1, typename T2, typename T3, typename T4>
    void log(const char* _log_message, T0 _t0, T1 _t1, T2 _t2, T3 _t3, T4 _t4) {
        onPreSetMessage_();
        string_util_.formatStr(_log_message, _t0, _t1, _t2, _t3, _t4);
        onPostSetMessage_();
    }

    //! log
    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
    void log(const char* _log_message, T0 _t0, T1 _t1, T2 _t2, T3 _t3, T4 _t4, T5 _t5) {
        onPreSetMessage_();
        string_util_.formatStr(_log_message, _t0, _t1, _t2, _t3, _t4, _t5);
        onPostSetMessage_();
    }

    //! log
    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
    void log(const char* _log_message, T0 _t0, T1 _t1, T2 _t2, T3 _t3, T4 _t4, T5 _t5, T6 _t6) {
        onPreSetMessage_();
        string_util_.formatStr(_log_message, _t0, _t1, _t2, _t3, _t4, _t5, _t6);
        onPostSetMessage_();
    }

    //! log
    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
    void log(const char* _log_message, T0 _t0, T1 _t1, T2 _t2, T3 _t3, T4 _t4, T5 _t5, T6 _t6, T7 _t7) {
        onPreSetMessage_();
        string_util_.formatStr(_log_message, _t0, _t1, _t2, _t3, _t4, _t5, _t6, _t7);
        onPostSetMessage_();
    }

    //! log
    void assertLog(bool _bAssertion, const char* _log_message) {
        if(_bAssertion) {
            return;
        }

        #ifndef _DEBUG
        log(_log_message);
        #endif
    }

private:

    // logger member
    ELogListener* log_listener_;
    bool is_enable_console_out_;
    E_LOG_LEVEL log_level_;

    // string util instance for log message
    EStringUtil string_util_;

    // before setting message
    void onPreSetMessage_() {
        string_util_.clearString();
    }

    // after setting message
    void onPostSetMessage_();
};

}

#endif	//_ELOG_MODULE_H__

// vim: ts=4:sw=4
