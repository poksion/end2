// Copyright (C) 2005-2009 The END Authors. All rights reserved.
//
// This file is part of the "END" (Engine for Dimensions).
// You can use this source code under the New BSD license
// that can be found in the LICENSE file.
// 이 파일은 "END" 의 일부분입니다.
// 소스코드는 New BSD license 에따라 사용이 가능합니다.

#ifndef _EVECTOR3_H__
#define _EVECTOR3_H__

#include <float.h>
#include <math.h>

namespace end2 {

class EVector3 {
public:

    /////////////////////////////////////////////////////////////////////
    //
    // EVector3 getters / unit vectors / zero vector
    //
    //////////////////////////////////////////////////////////////////////

    float x, y, z;
    inline const float* get() const {
        return &x;
    }

    static const EVector3 UNIT_X;
    static const EVector3 UNIT_Y;
    static const EVector3 UNIT_Z;
    static const EVector3 ZERO;

    /////////////////////////////////////////////////////////////////////
    //
    // EVector3 constructors / setters
    //
    //////////////////////////////////////////////////////////////////////

    EVector3() : x(0.f), y(0.f), z(0.f) {
    }

    explicit EVector3(const float* _f) : x(_f[0]), y(_f[1]), z(_f[2]) {
    }

    EVector3(float _fX, float _fY, float _fZ) : x(_fX), y(_fY), z(_fZ) {
    }

    EVector3(const EVector3& _rSrc) : x(_rSrc.x), y(_rSrc.y), z(_rSrc.z) {
    }

    inline EVector3& set(float _fX, float _fY, float _fZ) {
        x = _fX;
        y = _fY;
        z = _fZ;
        return *this;
    }

    inline EVector3& set(const EVector3& _rSrc) {
        return set(_rSrc.get());
    }

    inline EVector3& set(const float* _f) {
        x = _f[0];
        y = _f[1];
        z = _f[2];
        return *this;
    }

    //////////////////////////////////////////////////////////////////////
    //
    // EVector3 make-functions
    //
    //////////////////////////////////////////////////////////////////////

    inline static void makeUnitX(EVector3& _rOut) {
        _rOut.set(UNIT_X);
    }

    inline static void makeUnitY(EVector3& _rOut) {
        _rOut.set(UNIT_Y);
    }

    inline static void makeUnitZ(EVector3& _rOut) {
        _rOut.set(UNIT_Z);
    }

    inline static void makeZero(EVector3& _rOut) {
        _rOut.set(ZERO);
    }

    //////////////////////////////////////////////////////////////////////
    //
    // EVector3 operations
    //
    //////////////////////////////////////////////////////////////////////

    inline static void add(
            EVector3& _rOut,
            const EVector3& _rRhs,
            const EVector3& _rLhs) {

        _rOut.x = _rRhs.x + _rLhs.x;
        _rOut.y = _rRhs.y + _rLhs.y;
        _rOut.z = _rRhs.z + _rLhs.z;
    }

    inline static void subtract(
            EVector3& _rOut,
            const EVector3& _rRhs,
            const EVector3& _rLhs) {

        _rOut.x = _rRhs.x - _rLhs.x;
        _rOut.y = _rRhs.y - _rLhs.y;
        _rOut.z = _rRhs.z - _rLhs.z;
    }

    inline static void crossProduct(
            EVector3& _rOut,
            const EVector3& _rLhs,
            const EVector3& _rRhs) {

        _rOut.x = _rLhs.y * _rRhs.z - _rLhs.z * _rRhs.y;
        _rOut.y = _rLhs.z * _rRhs.x - _rLhs.x * _rRhs.z;
        _rOut.z = _rLhs.x * _rRhs.y - _rLhs.y * _rRhs.x;
    }

    inline static float dotProduct(
            const EVector3& _rLhs,
            const EVector3& _rRhs) {

        return _rLhs.x * _rRhs.x + _rLhs.y * _rRhs.y + _rLhs.z * _rRhs.z;
    }

    inline static float length(const EVector3& _in) {
        return sqrt(lengthSq(_in));
    }

    inline static float lengthSq(const EVector3& _in) {
        return _in.x * _in.x + _in.y * _in.y + _in.z * _in.z;
    }

    //////////////////////////////////////////////////////////////////////
    //
    // EVector3 compare-functions
    //
    //////////////////////////////////////////////////////////////////////

    inline static bool isEqualNoEpsilon(const EVector3& _rRhs, const EVector3& _rLhs) {
        if((_rRhs.x == _rLhs.x) && (_rRhs.y == _rLhs.y) && (_rRhs.z == _rLhs.z)) {
            return true;
        }
        return false;
    }

    //////////////////////////////////////////////////////////////////////
    //
    // EVector3 apply-functions (member functions)
    //
    //////////////////////////////////////////////////////////////////////

    inline EVector3& applyNormalization() {
        float length = x * x + y * y + z * z;
        if(length < FLT_EPSILON){
            return *this;
        }

        length = 1.f / sqrtf(length);
        x = x * length;
        y = y * length;
        z = z * length;

        return *this;
    }

    inline EVector3& applySymmetry(const EVector3* _pRespectTo_But_Null_Then_Origin = 0) {
        if(_pRespectTo_But_Null_Then_Origin == 0) {
            x = -x;
            y = -y;
            z = -z;
        } else {
            x = 2.f * _pRespectTo_But_Null_Then_Origin->x - x;
            y = 2.f * _pRespectTo_But_Null_Then_Origin->y - y;
            z = 2.f * _pRespectTo_But_Null_Then_Origin->z - z;
        }
        return *this;
    }

    inline EVector3& applyScale(const float _fScale) {
        x *= _fScale;
        y *= _fScale;
        z *= _fScale;
        return *this;
    }

    inline EVector3& applyAddition(const EVector3& _rOther) {
        x += _rOther.x;
        y += _rOther.y;
        z += _rOther.z;
        return *this;
    }

    inline EVector3& applySubtraction(const EVector3& _rOther) {
        x -= _rOther.x;
        y -= _rOther.y;
        z -= _rOther.z;
        return *this;
    }
};

}

#endif	//_EVECTOR3_H__

// vim: ts=4:sw=4
