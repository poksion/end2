// Copyright (C) 2005-2014 The END Authors. All rights reserved.
//
// This file is part of the "END" (Engine for Dimensions).
// You can use this source code under the New BSD license
// that can be found in the LICENSE file.
// 이 파일은 "END" 의 일부분입니다.
// 소스코드는 New BSD license 에따라 사용이 가능합니다.

#ifndef _ESTRING_UTIL_H__
#define _ESTRING_UTIL_H__

#include <stdlib.h> // for atoi#include <vector>
#include <string>

#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <cctype>

namespace std {
typedef basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> > wstring;
}

namespace end2 {

//! Utility class for string
class EStringUtil {
public:

    //! constructor
    EStringUtil() {
    }

    //! constructor
    EStringUtil(const std::string& _contents) : contents_(_contents) {
    }

    //! destructor
    virtual ~EStringUtil() {
    }

    //! error message for format index
    static const char* FORMAT_INDEX_ERROR;

    //! gets contents
    std::string& getString() {
        return contents_;
    }

    //! sets contents
    void setString(const std::string& _contents) {
        contents_ = _contents;
    }

    //! sets contents form c-string
    void setStringFromCStr(const char* _contents_cstr) {
        contents_ = _contents_cstr;
    }

    //! clears contents
    void clearString() {
        contents_.clear();
    }

    //! replaces string
    EStringUtil& replace(const std::string& _old, const std::string& _new) {
        size_t old_count = _old.length();
        size_t i = contents_.find(_old);
        while (i != std::string::npos) {
            contents_.replace(i, old_count, _new);
            i = contents_.find(_old);
        }

        return *this;
    }

    //! string formatting
    template<typename T0>
    std::string& formatStr(const char* _contents, T0 _t0) {
        return formatStr(_contents, _t0, FORMAT_INDEX_ERROR);
    }

    //! string formatting
    template<typename T0, typename T1>
    std::string& formatStr(const char* _contents, T0 _t0, T1 _t1) {
        return formatStr(_contents, _t0, _t1, FORMAT_INDEX_ERROR);
    }

    //! string formatting
    template<typename T0, typename T1, typename T2>
    std::string& formatStr(const char* _contents, T0 _t0, T1 _t1, T2 _t2) {
        return formatStr(_contents, _t0, _t1, _t2, FORMAT_INDEX_ERROR);
    }

    //! string formatting
    template<typename T0, typename T1, typename T2, typename T3>
    std::string& formatStr(const char* _contents, T0 _t0, T1 _t1, T2 _t2,
            T3 _t3) {
        return formatStr(_contents, _t0, _t1, _t2, _t3, FORMAT_INDEX_ERROR);
    }

    //! string formatting
    template<typename T0, typename T1, typename T2, typename T3, typename T4>
    std::string& formatStr(const char* _contents, T0 _t0, T1 _t1, T2 _t2, T3 _t3, T4 _t4) {
        return formatStr(_contents, _t0, _t1, _t2, _t3, _t4, FORMAT_INDEX_ERROR);
    }

    //! string formatting
    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
    std::string& formatStr(const char* _contents, T0 _t0, T1 _t1, T2 _t2, T3 _t3, T4 _t4, T5 _t5) {
        return formatStr(_contents, _t0, _t1, _t2, _t3, _t4, _t5, FORMAT_INDEX_ERROR);
    }

    //! string formatting
    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
    std::string& formatStr(const char* _contents, T0 _t0, T1 _t1, T2 _t2, T3 _t3, T4 _t4, T5 _t5, T6 _t6) {
        return formatStr(_contents, _t0, _t1, _t2, _t3, _t4, _t5, _t6, FORMAT_INDEX_ERROR);
    }

    //! string formatting
    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
    std::string& formatStr(const char* _contents, T0 _t0, T1 _t1, T2 _t2, T3 _t3, T4 _t4, T5 _t5, T6 _t6, T7 _t7) {
        buffers_.clear();

        split_(buffers_, _contents);

        std::ostringstream oss;
        oss.precision(10);

        for(std::vector<std::string>::iterator itr = buffers_.begin(); itr != buffers_.end(); ++itr) {
            std::string& buff = *itr;
            size_t tSize = buff.size();
            if(tSize > 2 && buff[0] == '{' && buff[tSize - 1] == '}') {
                size_t current_pos = buff.find_first_not_of(" ", 1);
                if(std::string::npos == current_pos) {
                    continue;
                }

                int current_index = atoi(&buff[current_pos]);
                int pre_dot = -1;
                int post_dot = -1;

                current_pos = buff.find(":", current_pos + 1);
                if(std::string::npos != current_pos) {
                    getDotPrePostCount_(pre_dot, post_dot, buff.substr(current_pos, tSize - current_pos).c_str());
                }

                switch (current_index) {
                    case 0: {
                        fillDotFormat_(buff, oss, pre_dot, post_dot, _t0);
                    }
                    break;

                    case 1: {
                        fillDotFormat_(buff, oss, pre_dot, post_dot, _t1);
                    }
                    break;

                    case 2: {
                        fillDotFormat_(buff, oss, pre_dot, post_dot, _t2);
                    }
                    break;

                    case 3: {
                        fillDotFormat_(buff, oss, pre_dot, post_dot, _t3);
                    }
                    break;

                    case 4: {
                        fillDotFormat_(buff, oss, pre_dot, post_dot, _t4);
                    }
                    break;

                    case 5: {
                        fillDotFormat_(buff, oss, pre_dot, post_dot, _t5);
                    }
                    break;

                    case 6: {
                        fillDotFormat_(buff, oss, pre_dot, post_dot, _t6);
                    }
                    break;

                    case 7: {
                        fillDotFormat_(buff, oss, pre_dot, post_dot, _t7);
                    }
                    break;
                }
            }

            contents_ += buff;
        }

        return contents_;
    }

    //! splits string
    static void split(std::vector<std::string>& _out, const char* _contents, const char* delimiter = " ") {
        split_(_out, _contents, delimiter, false);
    }

    //! splits current contents
    std::vector<std::string>& split(const char* delimiter = " ") {
        buffers_.clear();
        split_(buffers_, getString().c_str(), delimiter, false);
        return buffers_;
    }

    //! changes utf8 string to wstring
    static bool getWStringFromUTF8(std::wstring& _out, const std::string& _in);

    //! get changed result wstring from utf contents
    std::wstring getWStringFromUTF8() {
        std::wstring result;
        getWStringFromUTF8(result, getString());
        return result;
    }

    static bool isSpace(const char _c) {
        return _c == ' ' || _c == '\f' || _c == '\n' || _c == '\r' || _c == '\t' || _c == '\v';
    }

    static bool isDigit(const char _c) {
        return _c >= '0' && _c <= '9';
    }

    static void tolower(std::string& _str) {
        std::transform(_str.begin(), _str.end(), _str.begin(), static_cast<int (*)(int)>(std::tolower));
    }

    static void toupper(std::string& _str) {
        std::transform(_str.begin(), _str.end(), _str.begin(), static_cast<int(*)(int)>(std::toupper));
    }

private:

    std::string contents_;
    std::vector< std::string > buffers_;

    static void split_(std::vector< std::string >& _out, const char* _contents, const char* _pattern = "{.*}", bool _for_formatting = true);
    static void getDotPrePostCount_(int& _pre_dot, int& _post_dot, const char* _contents);

    template< typename T>
    static void fillDotFormat_(std::string& _out_buff, std::ostringstream& _oss, int _pre_dot, int _post_dot, T _t) {
        // some formatting like '0000'
        if( _pre_dot != -1 && _post_dot == -1) {
            _oss << std::setw(_pre_dot) << std::setfill('0') << std::fixed << _t;
            _out_buff = _oss.str();
        }
        // some formatting like '0.0000'
        else if(_pre_dot != -1 && _post_dot != -1) {
            _oss << std::fixed << _t;
            _out_buff = _oss.str();

            const size_t buff_length = _out_buff.length();
            size_t dot_pos = _out_buff.find(".");

            // check parts of post dot
            if( std::string::npos == dot_pos ) {
                // case that no dot
                std::string post_dot_str(".", _post_dot + 1);
                for(int i = 1; i <= _post_dot; ++i)
                post_dot_str[i] = '0';

                // how about it?
                // std::string post_dot_str(_post_dot, '0');
                // _out_buff = _out_buff + '0' + post_dot_str;

                _out_buff += post_dot_str;

                // new dot pos
                dot_pos = buff_length;
            } else {
                // case that has dot
                int dot_size = (int)( buff_length - dot_pos) - 1;
                int count = dot_size - _post_dot;
                if(count < 0 ) {
                    count = -count;
                    for(int i = 0; i < count; ++i)
                    _out_buff.push_back('0');
                } else {
                    _out_buff.resize(buff_length - count);
                }
            }

            // check parts of front dot
            int count = _pre_dot - dot_pos;
            if(count > 0 )
            _out_buff.insert(_out_buff.begin(), count, '0');
        }
        // others, just assign
        else {
            _oss << _t;
            _out_buff = _oss.str();
        }

        // init ostringstream
        _oss.str("");
    }
};

}

#endif	//_ESTRING_UTIL_H__

// vim: ts=4:sw=4
