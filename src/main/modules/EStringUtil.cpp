// Copyright (C) 2005-2014 The END Authors. All rights reserved.
//
// This file is part of the "END" (Engine for Dimensions).
// You can use this source code under the New BSD license
// that can be found in the LICENSE file.
// 이 파일은 "END" 의 일부분입니다.
// 소스코드는 New BSD license 에따라 사용이 가능합니다.

#include "EStringUtil.h"

extern "C" {
#include "third_party/trex/trex.h"
}

#include "third_party/utfcpp/utf8.h"

namespace end2 {

const char* EStringUtil::FORMAT_INDEX_ERROR = "##_INDEX_ERROR_##";

void EStringUtil::split_(std::vector<std::string>& _out, const char* _contents, const char* _pattern, bool _for_formatting) {
#ifdef _DEBUG
    if(_for_formatting) {
        EASSERT(_out.empty());
    }
#endif

    const char* contents_cstr = _contents;
    const char* error_cstr = 0;
    TRex* rex_ptr = trex_compile(_pattern, &error_cstr);
    if(rex_ptr) {
        const char *begin_cstr, *end_cstr;
        while (trex_search(rex_ptr, contents_cstr, &begin_cstr, &end_cstr)) {
            TRexMatch match;
            trex_getsubexp(rex_ptr, 0, &match);

            if(contents_cstr != match.begin) {
                size_t length = (match.begin - contents_cstr) / sizeof(char);
                _out.push_back(std::string(contents_cstr, length));
            }

            if(_for_formatting)
                _out.push_back(std::string(match.begin, match.len));

            contents_cstr = end_cstr;
        }

        _out.push_back(contents_cstr);
    }
    trex_free(rex_ptr);
}

bool EStringUtil::getWStringFromUTF8(std::wstring& _out, const std::string& _in) {
    bool result = true;
    std::string& in_str = const_cast<std::string&>(_in);
    std::string::iterator end_it = utf8::find_invalid(in_str.begin(), in_str.end());
    if(end_it != in_str.end()) {
        result = false;
    }

    if(sizeof(wchar_t) == 4) {
#ifdef __ANDROID_API__
        utf8::unchecked::utf8to32(in_str.begin(), end_it, back_inserter(_out));
#else
        utf8::utf8to32(in_str.begin(), end_it, back_inserter(_out));
#endif
    } else {
#ifdef __ANDROID_API__
        utf8::unchecked::utf8to16(in_str.begin(), end_it, back_inserter(_out));
#else
        utf8::utf8to16(in_str.begin(), end_it, back_inserter(_out));
#endif
    }
    return result;
}

void EStringUtil::getDotPrePostCount_(int& _pre_dot, int& _post_dot, const char* _contents) {
    const char* contents_cstr = _contents;
    const char* error_cstr = 0;
    const char* _pattern = "0+";
    TRex* rex_ptr = trex_compile(_pattern, &error_cstr);
    if(rex_ptr) {
        const char *begin_cstr, *end_cstr;
        while (trex_search(rex_ptr, contents_cstr, &begin_cstr, &end_cstr)) {
            TRexMatch match;
            trex_getsubexp(rex_ptr, 0, &match);
            if(contents_cstr == _contents)
                _pre_dot = match.len;
            else
                _post_dot = match.len;

            contents_cstr = end_cstr;
        }
    }
    trex_free(rex_ptr);
}

}

// vim: ts=4:sw=4
