// Copyright (C) 2005-2009 The END Authors. All rights reserved.
//
// This file is part of the "END" (Engine for Dimensions).
// You can use this source code under the New BSD license
// that can be found in the LICENSE file.
// 이 파일은 "END" 의 일부분입니다.
// 소스코드는 New BSD license 에따라 사용이 가능합니다.
//
// $LastChangedBy: pok $
// $LastChangedDate: 2009-12-11 19:25:50 +0900 (금, 11 12 2009) $
// $Rev: 707 $

#ifndef _ETEXCOORD2_H__
#define _ETEXCOORD2_H__

namespace end1
{

class ETexCoord2
{
public:
	ETexCoord2()
	{
	}

	ETexCoord2(float _u, float _v)
	{
		set(_u, _v);
	}

	ETexCoord2(const ETexCoord2& _from_coord)
	{
		set(_from_coord);
	}

	inline float getU() const { return u_; }
	inline float getV() const { return v_; }

	inline ETexCoord2& set(float _u, float _v)
	{
		u_ = _u;
		v_ = _v;

		return *this;
	}

	inline ETexCoord2& set(const ETexCoord2& _from_coord)
	{
		return set(_from_coord.getU(), _from_coord.getV());
	}

private:
	float u_;
	float v_;
};

}

#endif	//_ETEXCOORD2_H__

// vim: ts=4:sw=4
