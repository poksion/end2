// Copyright (C) 2005-2014 The END Authors. All rights reserved.
//
// This file is part of the "END" (Engine for Dimensions).
// You can use this source code under the New BSD license
// that can be found in the LICENSE file.
// 이 파일은 "END" 의 일부분입니다.
// 소스코드는 New BSD license 에따라 사용이 가능합니다.

#ifndef _ECOLOR4_H__
#define _ECOLOR4_H__

namespace end2 {

class EColor4 {

private:
    int nR_;
    int nG_;
    int nB_;
    int nA_;

public:
    EColor4() : nR_(0), nG_(0), nB_(0), nA_(-1) {
    }

    EColor4(int _nR, int _nG, int _nB, int _nA) {
        set(_nR, _nG, _nB, _nA);
    }

    EColor4(const EColor4& _rSrc) {
        set(_rSrc);
    }

    inline int getR() const {
        return nR_;
    }
    inline int getG() const {
        return nG_;
    }
    inline int getB() const {
        return nB_;
    }
    inline int getA() const {
        return nA_;
    }

    inline float getClampR() const {
        return (float(nR_) / float(255));
    }
    inline float getClampG() const {
        return (float(nG_) / float(255));
    }
    inline float getClampB() const {
        return (float(nB_) / float(255));
    }
    inline float getClampA() const {
        return (float(nA_) / float(255));
    }

    inline EColor4& set(int _nR, int _nG, int _nB, int _nA = -1) {
        nR_ = _nR;
        nG_ = _nG;
        nB_ = _nB;
        nA_ = _nA;

        return *this;
    }

    inline EColor4& set(const EColor4& _rSrc) {
        return set(_rSrc.getR(), _rSrc.getG(), _rSrc.getB(), _rSrc.getA());
    }

    inline bool hasAlpha() const {
        return (nA_ != -1);
    }
};

}

#endif	//_ECOLOR4_H__
