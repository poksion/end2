// Copyright (C) 2005-2014 The END Authors. All rights reserved.
//
// This file is part of the "END" (Engine for Dimensions).
// You can use this source code under the New BSD license
// that can be found in the LICENSE file.
// 이 파일은 "END" 의 일부분입니다.
// 소스코드는 New BSD license 에따라 사용이 가능합니다.

#include "EGeometryBufferValidator.h"
#include "../main/system/ESystem.h"
#include "../main/modules/ELogModule.h"

namespace end2 {

bool EGeometryBufferValidator::checkValidation() {
    EStringUtil string_util;

    bool is_ok = true;
    for(int i = 0; i < EGeometryBuffer::E_FORMAT_NUM; ++i) {
        std::vector<int>& vbuffer_flag = formatFlags_[i];
        int count = (int) vbuffer_flag.size();
        for(int j = 0; j != count; ++j) {
            if(vbuffer_flag[j] == 1)
                continue;

            string_util.clearString();
            string_util.formatStr(
                    "in vertex buffer at format index {0}, not assigned at {1}",
                    i, j);
            ELOG_SAFE(string_util.getString());

            is_ok = false;
        }
    }

    int count = (int) ibufferFlag_.size();
    for(int i = 0; i < count; ++i) {
        if(ibufferFlag_[i] == 1) {
            continue;
        }

        string_util.clearString();
        string_util.formatStr("in index buffer, not assigned at {0}", i);
        ELOG_SAFE(string_util.getString());

        is_ok = false;
    }

    return is_ok;
}

}

// vim: ts=4:sw=4
