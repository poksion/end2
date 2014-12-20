// Copyright (C) 2005-2014 The END Authors. All rights reserved.
//
// This file is part of the "END" (Engine for Dimensions).
// You can use this source code under the New BSD license
// that can be found in the LICENSE file.
// 이 파일은 "END" 의 일부분입니다.
// 소스코드는 New BSD license 에따라 사용이 가능합니다.

#ifndef _EGEOMETRY_BUFFER_UTIL_H__
#define _EGEOMETRY_BUFFER_UTIL_H__

#include "EGeometryBufferUtil.h"

namespace end2 {

class EGeometryBufferUtil {
public:
    static void buildCube(EGeometryBuffer& _geometry_buffer, float _size){
        _geometry_buffer.assign(8, 24, EGeometryBuffer::E_LINE_LIST, true, false, false, true);

        float half_size = _size * 0.5f;

        _geometry_buffer.setXYZ(0, -half_size, +half_size, +half_size);
        _geometry_buffer.setXYZ(1, +half_size, +half_size, +half_size);
        _geometry_buffer.setXYZ(2, +half_size, -half_size, +half_size);
        _geometry_buffer.setXYZ(3, -half_size, -half_size, +half_size);
        _geometry_buffer.setXYZ(4, -half_size, +half_size, -half_size);
        _geometry_buffer.setXYZ(5, +half_size, +half_size, -half_size);
        _geometry_buffer.setXYZ(6, +half_size, -half_size, -half_size);
        _geometry_buffer.setXYZ(7, -half_size, -half_size, -half_size);

        _geometry_buffer.setIndexBuffer(0, 0);
        _geometry_buffer.setIndexBuffer(1, 1);
        _geometry_buffer.setIndexBuffer(2, 1);
        _geometry_buffer.setIndexBuffer(3, 2);
        _geometry_buffer.setIndexBuffer(4, 2);
        _geometry_buffer.setIndexBuffer(5, 3);
        _geometry_buffer.setIndexBuffer(6, 3);
        _geometry_buffer.setIndexBuffer(7, 0);
        _geometry_buffer.setIndexBuffer(8, 4);
        _geometry_buffer.setIndexBuffer(9, 5);
        _geometry_buffer.setIndexBuffer(10, 5);
        _geometry_buffer.setIndexBuffer(11, 6);
        _geometry_buffer.setIndexBuffer(12, 6);
        _geometry_buffer.setIndexBuffer(13, 7);
        _geometry_buffer.setIndexBuffer(14, 7);
        _geometry_buffer.setIndexBuffer(15, 4);
        _geometry_buffer.setIndexBuffer(16, 0);
        _geometry_buffer.setIndexBuffer(17, 4);
        _geometry_buffer.setIndexBuffer(18, 1);
        _geometry_buffer.setIndexBuffer(19, 5);
        _geometry_buffer.setIndexBuffer(20, 2);
        _geometry_buffer.setIndexBuffer(21, 6);
        _geometry_buffer.setIndexBuffer(22, 3);
        _geometry_buffer.setIndexBuffer(23, 7);
        _geometry_buffer.setTFactor(255, 255, 255);
    }
};

}

#endif	//_EGEOMETRY_BUFFER_UTIL_H__// vim: ts=4:sw=4
