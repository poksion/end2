// Copyright (C) 2005-2014 The END Authors. All rights reserved.
//
// This file is part of the "END" (Engine for Dimensions).
// You can use this source code under the New BSD license
// that can be found in the LICENSE file.
// 이 파일은 "END" 의 일부분입니다.
// 소스코드는 New BSD license 에따라 사용이 가능합니다.

#ifndef _EFLAG_PROPERTY_H__
#define _EFLAG_PROPERTY_H__

#include <bitset>

////////////////////////////////////////////////////////////////////////////////

#define EFLAG_PROPERTIES_1(P1)  \
    enum E_FLAG_PROPERTY { P1 = 1 << 1 }

#define EFLAG_PROPERTIES_2(P1, P2)	\
	enum E_FLAG_PROPERTY { P1 = 1 << 1, P2 = 1 << 2 }

#define EFLAG_PROPERTIES_3(P1, P2, P3)	\
	enum E_FLAG_PROPERTY { P1 = 1 << 1, P2 = 1 << 2, P3 = 1 << 3 }

#define EFLAG_PROPERTIES_4(P1, P2, P3, P4)	\
	enum E_FLAG_PROPERTY { P1 = 1 << 1, P2 = 1 << 2, P3 = 1 << 3, P4 = 1 << 4 }

#define EFLAG_PROPERTIES_5(P1, P2, P3, P4, P5)	\
	enum E_FLAG_PROPERTY { P1 = 1 << 1, P2 = 1 << 2, P3 = 1 << 3, P4 = 1 << 4, P5 = 1 << 5 }

#define EFLAG_PROPERTIES_6(P1, P2, P3, P4, P5, P6)	\
	enum E_FLAG_PROPERTY { P1 = 1 << 1, P2 = 1 << 2, P3 = 1 << 3, P4 = 1 << 4,	\
	P5 = 1 << 5, P6 = 1 << 6 }

#define EFLAG_PROPERTIES_7(P1, P2, P3, P4, P5, P6, P7)	\
	enum E_FLAG_PROPERTY { P1 = 1 << 1, P2 = 1 << 2, P3 = 1 << 3, P4 = 1 << 4,	\
	P5 = 1 << 5, P6 = 1 << 6, P7 = 1 << 7 }

#define EFLAG_PROPERTIES_8(P1, P2, P3, P4, P5, P6, P7, P8)	\
	enum E_FLAG_PROPERTY { P1 = 1 << 1, P2 = 1 << 2, P3 = 1 << 3, P4 = 1 << 4,	\
	P5 = 1 << 5, P6 = 1 << 6, P7 = 1 << 7, P8 = 1 << 8 }

#define EFLAG_PROPERTIES_9(P1, P2, P3, P4, P5, P6, P7, P8, P9)	\
	enum E_FLAG_PROPERTY { P1 = 1 << 1, P2 = 1 << 2, P3 = 1 << 3, P4 = 1 << 4,	\
	P5 = 1 << 5, P6 = 1 << 6, P7 = 1 << 7, P8 = 1 << 8, P9 = 1 << 9 }

#define EFLAG_PROPERTIES_10(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10)	\
	enum E_FLAG_PROPERTY { P1 = 1 << 1, P2 = 1 << 2, P3 = 1 << 3, P4 = 1 << 4,	\
	P5 = 1 << 5, P6 = 1 << 6, P7 = 1 << 7, P8 = 1 << 8, P9 = 1 << 9, P10 = 1 << 10 }

#define EFLAG_PROPERTIES_11(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11)	\
	enum E_FLAG_PROPERTY { P1 = 1 << 1, P2 = 1 << 2, P3 = 1 << 3, P4 = 1 << 4,	\
	P5 = 1 << 5, P6 = 1 << 6, P7 = 1 << 7, P8 = 1 << 8, P9 = 1 << 9, P10 = 1 << 10, P11 = 1 << 11 }

#define EFLAG_PROPERTIES_12(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12)	\
	enum E_FLAG_PROPERTY { P1 = 1 << 1, P2 = 1 << 2, P3 = 1 << 3, P4 = 1 << 4,		\
	P5 = 1 << 5, P6 = 1 << 6, P7 = 1 << 7, P8 = 1 << 8, P9 = 1 << 9, P10 = 1 << 10,	\
	P11 = 1 << 11, P12 = 1 << 12 }

#define EFLAG_PROPERTIES_13(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13)	\
	enum E_FLAG_PROPERTY { P1 = 1 << 1, P2 = 1 << 2, P3 = 1 << 3, P4 = 1 << 4,		\
	P5 = 1 << 5, P6 = 1 << 6, P7 = 1 << 7, P8 = 1 << 8, P9 = 1 << 9, P10 = 1 << 10,	\
	P11 = 1 << 11, P12 = 1 << 12, P13 = 1 << 13 }

#define EFLAG_PROPERTIES_14(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14)	\
	enum E_FLAG_PROPERTY { P1 = 1 << 1, P2 = 1 << 2, P3 = 1 << 3, P4 = 1 << 4,		\
	P5 = 1 << 5, P6 = 1 << 6, P7 = 1 << 7, P8 = 1 << 8, P9 = 1 << 9, P10 = 1 << 10,	\
	P11 = 1 << 11, P12 = 1 << 12, P13 = 1 << 13, P14 = 1 << 14 }

#define EFLAG_PROPERTIES_15(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15)	\
	enum E_FLAG_PROPERTY { P1 = 1 << 1, P2 = 1 << 2, P3 = 1 << 3, P4 = 1 << 4,		\
	P5 = 1 << 5, P6 = 1 << 6, P7 = 1 << 7, P8 = 1 << 8, P9 = 1 << 9, P10 = 1 << 10,	\
	P11 = 1 << 11, P12 = 1 << 12, P13 = 1 << 13, P14 = 1 << 14, P15 = 1 << 15 }

////////////////////////////////////////////////////////////////////////////////

namespace end2 {

//! Sturct holding the property informations with bit flag
template< typename T_HasFlags, typename T_FlagProperty = typename T_HasFlags::E_FLAG_PROPERTY >
class EFlagProperty {
private:
	unsigned int properties_;

public:

	//! constructor
	EFlagProperty() : properties_(0) {}

	//! destructor
	~EFlagProperty() {}

	//! adds property
	void addProperty(T_FlagProperty _eProperty){ properties_ |= _eProperty; }

	//! removes property
	void removeProperty(T_FlagProperty _eProperty){ properties_ &= ~_eProperty; }

	//! queries property
	bool queryProperty(T_FlagProperty _eProperty){ return (properties_ & _eProperty) ? true : false; }
};


//! Flag property, none size limited version
template < typename T_FlagProperty, unsigned int T_Size >
class EFlagPropertyEx {
private:
	std::bitset< T_Size > bitset_;

public:

	//! constructor
	EFlagPropertyEx(){}

	//! destructor
	~EFlagPropertyEx(){}

	//! sets property value (true or false)
	void set(T_FlagProperty _enum, bool _flag) {
		bitset_.set( (size_t)_enum, _flag);
	}

	//! tests property value
	bool test(T_FlagProperty _enum) {
		return bitset_.test( (size_t)_enum );
	}
};

}

#endif // _EFLAG_PROPERTY_H__

// vim: ts=4:sw=4
