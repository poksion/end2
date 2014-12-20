// Copyright (C) 2005-2014 The END Authors. All rights reserved.
//
// This file is part of the "END" (Engine for Dimensions).
// You can use this source code under the New BSD license
// that can be found in the LICENSE file.
// 이 파일은 "END" 의 일부분입니다.
// 소스코드는 New BSD license 에따라 사용이 가능합니다.

#ifndef _EASSERT_H__
#define _EASSERT_H__

#include <typeinfo>	//for typeid

// Assertion Macors
/*
	EASSERT : assert. If you develop in win32, it is _ASSERT. if not, assert ( standard C lib )
	EAASERT_TYPE : checks type
	EASSERT_CASTABLE : checks castable
*/

#ifdef _MSC_VER
#include <crtdbg.h>
#define EASSERT( assertion ) _ASSERT(assertion)
#else
#include <assert.h>
#define EASSERT( assertion ) assert(assertion)
#endif

#ifdef _DEBUG
#define EASSERT_TYPE( instance, type ) { if(instance) { EASSERT( typeid(*instance) == typeid(type) ); } }
#define EASSERT_CASTABLE(instance, type) { EASSERT( dynamic_cast<type*>(instance) != 0 ); }
#else
#define EASSERT_TYPE( instance, type )
#define EASSERT_CASTABLE(instance, type)
#endif // _DEBUG

#endif //_EASSERT_H__

// vim: ts=4:sw=4
