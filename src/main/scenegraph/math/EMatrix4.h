// Copyright (C) 2005-2014 The END Authors. All rights reserved.
//
// This file is part of the "END" (Engine for Dimensions).
// You can use this source code under the New BSD license
// that can be found in the LICENSE file.
// 이 파일은 "END" 의 일부분입니다.
// 소스코드는 New BSD license 에따라 사용이 가능합니다.

#ifndef _EMATRIX4_H__
#define _EMATRIX4_H__

#include "EVector3.h"

#include <string.h> //for memcpy#include <float.h>
#include <math.h>

namespace end2 {

class EMatrix4 {
public:
    enum E_MATRIX4_INDEX {
        _11 = 0, _12 = 4, _13 = 8,  _14 = 12,
        _21 = 1, _22 = 5, _23 = 9,  _24 = 13,
        _31 = 2, _32 = 6, _33 = 10, _34 = 14,
        _41 = 3, _42 = 7, _43 = 11, _44 = 15,

        _MAX = 16
    };

private:
    float fMat_[_MAX];

public:

    /////////////////////////////////////////////////////////////////////
    //
    // EMatrix4 identity-matrix / constructors, setter / getters
    //
    //////////////////////////////////////////////////////////////////////

    static const EMatrix4 IDENTITY;

    EMatrix4() {
    }

    EMatrix4(float _f11, float _f12, float _f13, float _f14,
             float _f21, float _f22, float _f23, float _f24,
             float _f31, float _f32, float _f33, float _f34,
             float _f41, float _f42, float _f43, float _f44) {

        fMat_[_11] = _f11;
        fMat_[_12] = _f12;
        fMat_[_13] = _f13;
        fMat_[_14] = _f14;

        fMat_[_21] = _f21;
        fMat_[_22] = _f22;
        fMat_[_23] = _f23;
        fMat_[_24] = _f24;

        fMat_[_31] = _f31;
        fMat_[_32] = _f32;
        fMat_[_33] = _f33;
        fMat_[_34] = _f34;

        fMat_[_41] = _f41;
        fMat_[_42] = _f42;
        fMat_[_43] = _f43;
        fMat_[_44] = _f44;
    }

    EMatrix4(const EMatrix4& _rSrc) {
        set(_rSrc);
    }

    inline EMatrix4& set(const EMatrix4& _rSrc) {
        memcpy(fMat_, _rSrc.fMat_, sizeof(fMat_));
        return *this;
    }

    inline float& get(E_MATRIX4_INDEX _index) {
        return fMat_[_index];
    }

    inline const float* get() const {
        return fMat_;
    }

    inline EVector3* getFrameAxisX() {
        // _11, _21, _31
        return (EVector3*) (&fMat_[_11]);
    }

    inline EVector3* getFrameAxisY() {
        // _12, _22, _32
        return (EVector3*) (&fMat_[_12]);
    }

    inline EVector3* getFrameAxisZ() {
        // _13, _23, _33
        return (EVector3*) (&fMat_[_13]);
    }

    inline EVector3* getFramePosition() {
        // _14, _24, _34
        return (EVector3*) (&fMat_[_14]);
    }

    //////////////////////////////////////////////////////////////////////
    //
    // EMatrix4 diagonal related operations
    //
    //////////////////////////////////////////////////////////////////////

    inline EMatrix4& setDiagonal(float _f11, float _f22, float _f33, float _f44 = 1.f) {
        fMat_[_11] = _f11;
        fMat_[_22] = _f22;
        fMat_[_33] = _f33;
        fMat_[_44] = _f44;
        return *this;
    }

    inline void getDiagonal(EVector3& _daigonal, float* _f44 = 0) {
        _daigonal.set(fMat_[_11], fMat_[_22], fMat_[_33]);
        if(_f44) {
            *_f44 = fMat_[_44];
        }
    }

    //////////////////////////////////////////////////////////////////////
    //
    // EMatrix4 apply-functions (member functions)
    //
    //////////////////////////////////////////////////////////////////////

    inline EMatrix4& applyAddition(const EMatrix4& _rOther, bool _as3x3 = false) {
        fMat_[0] += _rOther.fMat_[0];
        fMat_[1] += _rOther.fMat_[1];
        fMat_[2] += _rOther.fMat_[2];
        fMat_[3] += _rOther.fMat_[3];
        fMat_[4] += _rOther.fMat_[4];
        fMat_[5] += _rOther.fMat_[5];
        fMat_[6] += _rOther.fMat_[6];
        fMat_[7] += _rOther.fMat_[7];
        fMat_[8] += _rOther.fMat_[8];
        fMat_[9] += _rOther.fMat_[9];
        fMat_[10] += _rOther.fMat_[10];
        fMat_[11] += _rOther.fMat_[11];

        if(false == _as3x3) {
            fMat_[12] += _rOther.fMat_[12];
            fMat_[13] += _rOther.fMat_[13];
            fMat_[14] += _rOther.fMat_[14];
            fMat_[15] += _rOther.fMat_[15];
        }

        return *this;
    }

    inline EMatrix4& applyScale(const float _fScale, bool _as3x3 = false) {
        fMat_[0] *= _fScale;
        fMat_[1] *= _fScale;
        fMat_[2] *= _fScale;
        fMat_[3] *= _fScale;
        fMat_[4] *= _fScale;
        fMat_[5] *= _fScale;
        fMat_[6] *= _fScale;
        fMat_[7] *= _fScale;
        fMat_[8] *= _fScale;
        fMat_[9] *= _fScale;
        fMat_[10] *= _fScale;
        fMat_[11] *= _fScale;

        if(false == _as3x3) {
            fMat_[12] *= _fScale;
            fMat_[13] *= _fScale;
            fMat_[14] *= _fScale;
            fMat_[15] *= _fScale;
        }

        return *this;
    }

    //////////////////////////////////////////////////////////////////////
    //
    // EMatrix4 make-functions
    //
    //////////////////////////////////////////////////////////////////////

    inline static void makeIdentity(EMatrix4& _rOut) {
        memset(_rOut.fMat_, 0, sizeof(_rOut.fMat_));
        _rOut.fMat_[_11] = _rOut.fMat_[_22] = _rOut.fMat_[_33] = _rOut.fMat_[_44] = 1.f;
    }

    inline static void makeFrame(
            EMatrix4& _rOut,
            const EVector3& _rPos,
            const EVector3& _rDir,
            const EVector3& _rUp) {

        float* out = _rOut.fMat_;
        EVector3 vDir(_rDir), vRight, vUp;
        vDir.applyNormalization();

        EVector3::crossProduct(vRight, vDir, _rUp);
        vRight.applyNormalization();

        EVector3::crossProduct(vUp, vRight, vDir);
        vUp.applyNormalization();

        out[_11] = vRight.x;
        out[_21] = vRight.y;
        out[_31] = vRight.z;
        out[_41] = 0.f;

        out[_12] = vDir.x;
        out[_22] = vDir.y;
        out[_32] = vDir.z;
        out[_42] = 0.f;

        out[_13] = vUp.x;
        out[_23] = vUp.y;
        out[_33] = vUp.z;
        out[_43] = 0.f;

        out[_14] = _rPos.x;
        out[_24] = _rPos.y;
        out[_34] = _rPos.z;
        out[_44] = 1.f;
    }

    inline static void makeScaleTM(
            EMatrix4& _rOut,
            const EVector3& _scale) {

        _rOut.fMat_[_11] = _scale.x;
        _rOut.fMat_[_12] = 0.f;
        _rOut.fMat_[_13] = 0.f;
        _rOut.fMat_[_14] = 0.f;

        _rOut.fMat_[_21] = 0.f;
        _rOut.fMat_[_22] = _scale.y;
        _rOut.fMat_[_23] = 0.f;
        _rOut.fMat_[_24] = 0.f;

        _rOut.fMat_[_31] = 0.f;
        _rOut.fMat_[_32] = 0.f;
        _rOut.fMat_[_33] = _scale.z;
        _rOut.fMat_[_34] = 0.f;

        _rOut.fMat_[_41] = 0.f;
        _rOut.fMat_[_42] = 0.f;
        _rOut.fMat_[_43] = 0.f;
        _rOut.fMat_[_44] = 1.f;
    }

    inline static void makeTransTM(
            EMatrix4& _rOut,
            const EVector3& _translate) {

        _rOut.fMat_[_11] = 1.f;
        _rOut.fMat_[_12] = 0.f;
        _rOut.fMat_[_13] = 0.f;
        _rOut.fMat_[_14] = _translate.x;

        _rOut.fMat_[_21] = 0.f;
        _rOut.fMat_[_22] = 1.f;
        _rOut.fMat_[_23] = 0.f;
        _rOut.fMat_[_24] = _translate.y;

        _rOut.fMat_[_31] = 0.f;
        _rOut.fMat_[_32] = 0.f;
        _rOut.fMat_[_33] = 1.f;
        _rOut.fMat_[_34] = _translate.z;

        _rOut.fMat_[_41] = 0.f;
        _rOut.fMat_[_42] = 0.f;
        _rOut.fMat_[_43] = 0.f;
        _rOut.fMat_[_44] = 1.f;
    }

    inline static void makeRotTM(
            EMatrix4& _rOut,
            const EVector3& _rAxis,
            float _fAngleRadian) {

        float fCos = cos(_fAngleRadian);
        float fSin = sin(_fAngleRadian);
        float fOneMinusCos = 1.f - fCos;

        float fX2 = _rAxis.x * _rAxis.x;
        float fY2 = _rAxis.y * _rAxis.y;
        float fZ2 = _rAxis.z * _rAxis.z;

        float fXYM = _rAxis.x * _rAxis.y * fOneMinusCos;
        float fXZM = _rAxis.x * _rAxis.z * fOneMinusCos;
        float fYZM = _rAxis.y * _rAxis.z * fOneMinusCos;
        float fXSin = _rAxis.x * fSin;
        float fYSin = _rAxis.y * fSin;
        float fZSin = _rAxis.z * fSin;

        _rOut.fMat_[_11] = fX2 * fOneMinusCos + fCos;
        _rOut.fMat_[_12] = fXYM - fZSin;
        _rOut.fMat_[_13] = fXZM + fYSin;
        _rOut.fMat_[_14] = 0.f;

        _rOut.fMat_[_21] = fXYM + fZSin;
        _rOut.fMat_[_22] = fY2 * fOneMinusCos + fCos;
        _rOut.fMat_[_23] = fYZM - fXSin;
        _rOut.fMat_[_24] = 0.f;

        _rOut.fMat_[_31] = fXZM - fYSin;
        _rOut.fMat_[_32] = fYZM + fXSin;
        _rOut.fMat_[_33] = fZ2 * fOneMinusCos + fCos;
        _rOut.fMat_[_34] = 0.f;

        _rOut.fMat_[_41] = 0.f;
        _rOut.fMat_[_42] = 0.f;
        _rOut.fMat_[_43] = 0.f;
        _rOut.fMat_[_44] = 1.f;
    }

    inline static void makeViewTM(
            EMatrix4& _rOut,
            const EMatrix4& _rInputFrame) {

        const float* in = _rInputFrame.fMat_;
        float* out = _rOut.fMat_;

        out[_11] = in[_11];
        out[_12] = in[_21];
        out[_13] = in[_31];

        out[_21] = in[_13];
        out[_22] = in[_23];
        out[_23] = in[_33];

        out[_31] = -in[_12];
        out[_32] = -in[_22];
        out[_33] = -in[_32];

        out[_41] = 0.f;
        out[_42] = 0.f;
        out[_43] = 0.f;

        out[_14] = -(out[_11] * in[_14] + out[_12] * in[_24] + out[_13] * in[_34]);
        out[_24] = -(out[_21] * in[_14] + out[_22] * in[_24] + out[_23] * in[_34]);
        out[_34] = -(out[_31] * in[_14] + out[_32] * in[_24] + out[_33] * in[_34]);
        out[_44] = 1.f;
    }

    inline static void makeProjectionTM(
            EMatrix4& _rOut,
            float _fov_y, float _aspect_ratio,
            float _near_z, float _far_z) {

        float h = 1.f / tan(_fov_y / 2.f);
        float w = h / _aspect_ratio;
        float* out = _rOut.fMat_;

        out[_11] = w;
        out[_21] = 0.f;
        out[_31] = 0.f;
        out[_41] = 0.f;

        out[_12] = 0.f;
        out[_22] = h;
        out[_32] = 0.f;
        out[_42] = 0.f;

        out[_13] = 0.f;
        out[_23] = 0.f;
        out[_33] = _far_z / (_near_z - _far_z);				// DirectX version
        //out[_33] = _far_z+_near_z/(_near_z-_far_z);		// OpenGL version
        out[_43] = -1.f;

        out[_14] = 0.f;
        out[_24] = 0.f;
        out[_34] = _near_z * _far_z / (_near_z - _far_z);	// DirectX version
        //out[_34] = 2.0f*_near_z*_far_z/(_near_z-_far_z);	// OpenGL version
        out[_44] = 0.f;
    }

    //////////////////////////////////////////////////////////////////////
    //
    // EMatrix4 operations
    //
    //////////////////////////////////////////////////////////////////////

    inline static void multiply(
            EVector3& _pOut,
            const EMatrix4& _rApplierTransform,
            const EVector3& _rInput) {

        _pOut.set(
                _rInput.x * _rApplierTransform.fMat_[_11] +
                _rInput.y * _rApplierTransform.fMat_[_12] +
                _rInput.z * _rApplierTransform.fMat_[_13] +
                _rApplierTransform.fMat_[_14],

                _rInput.x * _rApplierTransform.fMat_[_21] +
                _rInput.y * _rApplierTransform.fMat_[_22] +
                _rInput.z * _rApplierTransform.fMat_[_23] +
                _rApplierTransform.fMat_[_24],

                _rInput.x * _rApplierTransform.fMat_[_31] +
                _rInput.y * _rApplierTransform.fMat_[_32] +
                _rInput.z * _rApplierTransform.fMat_[_33] +
                _rApplierTransform.fMat_[_34]);
    }

    inline static void multiply(
            EMatrix4& _pOut,
            const EMatrix4& _rApplierTransform,
            const EMatrix4& _rInputTransform) {

        const float* in1 = _rApplierTransform.fMat_;
        const float* in2 = _rInputTransform.fMat_;
        float* out = _pOut.fMat_;

        out[_11] = in1[_11] * in2[_11] + in1[_12] * in2[_21] + in1[_13] * in2[_31] + in1[_14] * in2[_41];
        out[_21] = in1[_21] * in2[_11] + in1[_22] * in2[_21] + in1[_23] * in2[_31] + in1[_24] * in2[_41];
        out[_31] = in1[_31] * in2[_11] + in1[_32] * in2[_21] + in1[_33] * in2[_31] + in1[_34] * in2[_41];
        out[_41] = in1[_41] * in2[_11] + in1[_42] * in2[_21] + in1[_43] * in2[_31] + in1[_44] * in2[_41];

        out[_12] = in1[_11] * in2[_12] + in1[_12] * in2[_22] + in1[_13] * in2[_32] + in1[_14] * in2[_42];
        out[_22] = in1[_21] * in2[_12] + in1[_22] * in2[_22] + in1[_23] * in2[_32] + in1[_24] * in2[_42];
        out[_32] = in1[_31] * in2[_12] + in1[_32] * in2[_22] + in1[_33] * in2[_32] + in1[_34] * in2[_42];
        out[_42] = in1[_41] * in2[_12] + in1[_42] * in2[_22] + in1[_43] * in2[_32] + in1[_44] * in2[_42];

        out[_13] = in1[_11] * in2[_13] + in1[_12] * in2[_23] + in1[_13] * in2[_33] + in1[_14] * in2[_43];
        out[_23] = in1[_21] * in2[_13] + in1[_22] * in2[_23] + in1[_23] * in2[_33] + in1[_24] * in2[_43];
        out[_33] = in1[_31] * in2[_13] + in1[_32] * in2[_23] + in1[_33] * in2[_33] + in1[_34] * in2[_43];
        out[_43] = in1[_41] * in2[_13] + in1[_42] * in2[_23] + in1[_43] * in2[_33] + in1[_44] * in2[_43];

        out[_14] = in1[_11] * in2[_14] + in1[_12] * in2[_24] + in1[_13] * in2[_34] + in1[_14] * in2[_44];
        out[_24] = in1[_21] * in2[_14] + in1[_22] * in2[_24] + in1[_23] * in2[_34] + in1[_24] * in2[_44];
        out[_34] = in1[_31] * in2[_14] + in1[_32] * in2[_24] + in1[_33] * in2[_34] + in1[_34] * in2[_44];
        out[_44] = in1[_41] * in2[_14] + in1[_42] * in2[_24] + in1[_43] * in2[_34] + in1[_44] * in2[_44];
    }

    inline static bool inverse(EMatrix4& _rOutput, const EMatrix4& _rInput) {
        float* out = _rOutput.fMat_;
        const float* in = _rInput.fMat_;

        float d = (in[_11] * in[_22] - in[_12] * in[_21]) * (in[_33] * in[_44] - in[_34] * in[_43])
                - (in[_11] * in[_23] - in[_13] * in[_21]) * (in[_32] * in[_44] - in[_34] * in[_42])
                + (in[_11] * in[_24] - in[_14] * in[_21]) * (in[_32] * in[_43] - in[_33] * in[_42])
                + (in[_12] * in[_23] - in[_13] * in[_22]) * (in[_31] * in[_44] - in[_34] * in[_41])
                - (in[_12] * in[_24] - in[_14] * in[_22]) * (in[_31] * in[_43] - in[_33] * in[_41])
                + (in[_13] * in[_24] - in[_14] * in[_23]) * (in[_31] * in[_42] - in[_32] * in[_41]);

        if(fabsf(d) < FLT_EPSILON) {
            return false;
        }

        d = 1.f / d;

        out[_11] = d * (  in[_22] * (in[_33] * in[_44] - in[_34] * in[_43])
                        + in[_23] * (in[_34] * in[_42] - in[_32] * in[_44])
                        + in[_24] * (in[_32] * in[_43] - in[_33] * in[_42]));

        out[_12] = d * (  in[_32] * (in[_13] * in[_44] - in[_14] * in[_43])
                        + in[_33] * (in[_14] * in[_42] - in[_12] * in[_44])
                        + in[_34] * (in[_12] * in[_43] - in[_13] * in[_42]));

        out[_13] = d * (  in[_42] * (in[_13] * in[_24] - in[_14] * in[_23])
                        + in[_43] * (in[_14] * in[_22] - in[_12] * in[_24])
                        + in[_44] * (in[_12] * in[_23] - in[_13] * in[_22]));

        out[_14] = d * (  in[_12] * (in[_24] * in[_33] - in[_23] * in[_34])
                        + in[_13] * (in[_22] * in[_34] - in[_24] * in[_32])
                        + in[_14] * (in[_23] * in[_32] - in[_22] * in[_33]));

        out[_21] = d * (  in[_23] * (in[_31] * in[_44] - in[_34] * in[_41])
                        + in[_24] * (in[_33] * in[_41] - in[_31] * in[_43])
                        + in[_21] * (in[_34] * in[_43] - in[_33] * in[_44]));

        out[_22] = d * (  in[_33] * (in[_11] * in[_44] - in[_14] * in[_41])
                        + in[_34] * (in[_13] * in[_41] - in[_11] * in[_43])
                        + in[_31] * (in[_14] * in[_43] - in[_13] * in[_44]));

        out[_23] = d * (  in[_43] * (in[_11] * in[_24] - in[_14] * in[_21])
                        + in[_44] * (in[_13] * in[_21] - in[_11] * in[_23])
                        + in[_41] * (in[_14] * in[_23] - in[_13] * in[_24]));

        out[_24] = d * (  in[_13] * (in[_24] * in[_31] - in[_21] * in[_34])
                        + in[_14] * (in[_21] * in[_33] - in[_23] * in[_31])
                        + in[_11] * (in[_23] * in[_34] - in[_24] * in[_33]));

        out[_31] = d * (  in[_24] * (in[_31] * in[_42] - in[_32] * in[_41])
                        + in[_21] * (in[_32] * in[_44] - in[_34] * in[_42])
                        + in[_22] * (in[_34] * in[_41] - in[_31] * in[_44]));

        out[_32] = d * (  in[_34] * (in[_11] * in[_42] - in[_12] * in[_41])
                        + in[_31] * (in[_12] * in[_44] - in[_14] * in[_42])
                        + in[_32] * (in[_14] * in[_41] - in[_11] * in[_44]));

        out[_33] = d * (  in[_44] * (in[_11] * in[_22] - in[_12] * in[_21])
                        + in[_41] * (in[_12] * in[_24] - in[_14] * in[_22])
                        + in[_42] * (in[_14] * in[_21] - in[_11] * in[_24]));

        out[_34] = d * (  in[_14] * (in[_22] * in[_31] - in[_21] * in[_32])
                        + in[_11] * (in[_24] * in[_32] - in[_22] * in[_34])
                        + in[_12] * (in[_21] * in[_34] - in[_24] * in[_31]));

        out[_41] = d * (  in[_21] * (in[_33] * in[_42] - in[_32] * in[_43])
                        + in[_22] * (in[_31] * in[_43] - in[_33] * in[_41])
                        + in[_23] * (in[_32] * in[_41] - in[_31] * in[_42]));

        out[_42] = d * (  in[_31] * (in[_13] * in[_42] - in[_12] * in[_43])
                        + in[_32] * (in[_11] * in[_43] - in[_13] * in[_41])
                        + in[_33] * (in[_12] * in[_41] - in[_11] * in[_42]));

        out[_43] = d * (  in[_41] * (in[_13] * in[_22] - in[_12] * in[_23])
                        + in[_42] * (in[_11] * in[_23] - in[_13] * in[_21])
                        + in[_43] * (in[_12] * in[_21] - in[_11] * in[_22]));

        out[_44] = d * (  in[_11] * (in[_22] * in[_33] - in[_23] * in[_32])
                        + in[_12] * (in[_23] * in[_31] - in[_21] * in[_33])
                        + in[_13] * (in[_21] * in[_32] - in[_22] * in[_31]));

        return true;
    }

    inline static void inverseFrame(EMatrix4& _rOutput, const EMatrix4& _rInput) {
        const float* in = _rInput.fMat_;
        float* out = _rOutput.fMat_;

        out[_11] = in[_11];
        out[_21] = in[_12];
        out[_31] = in[_13];
        out[_41] = 0.f;

        out[_12] = in[_21];
        out[_22] = in[_22];
        out[_32] = in[_23];
        out[_42] = 0.f;

        out[_13] = in[_31];
        out[_23] = in[_32];
        out[_33] = in[_33];
        out[_43] = 0.f;

        out[_14] = -(in[_14] * in[_11] + in[_24] * in[_21] + in[_34] * in[_31]);
        out[_24] = -(in[_14] * in[_12] + in[_24] * in[_22] + in[_34] * in[_32]);
        out[_34] = -(in[_14] * in[_13] + in[_24] * in[_23] + in[_34] * in[_33]);
        out[_44] = 1.f;
    }

    inline static void transpose(EMatrix4& _out, const EMatrix4& _in) {
        _out.fMat_[_11] = _in.fMat_[_11];
        _out.fMat_[_21] = _in.fMat_[_12];
        _out.fMat_[_31] = _in.fMat_[_13];
        _out.fMat_[_41] = _in.fMat_[_14];

        _out.fMat_[_12] = _in.fMat_[_21];
        _out.fMat_[_22] = _in.fMat_[_22];
        _out.fMat_[_32] = _in.fMat_[_23];
        _out.fMat_[_42] = _in.fMat_[_24];

        _out.fMat_[_13] = _in.fMat_[_31];
        _out.fMat_[_23] = _in.fMat_[_32];
        _out.fMat_[_33] = _in.fMat_[_33];
        _out.fMat_[_43] = _in.fMat_[_34];

        _out.fMat_[_14] = _in.fMat_[_41];
        _out.fMat_[_24] = _in.fMat_[_42];
        _out.fMat_[_34] = _in.fMat_[_43];
        _out.fMat_[_44] = _in.fMat_[_44];
    }
};

}

#endif	//_EMATRIX4_H__

// vim: ts=4:sw=4
