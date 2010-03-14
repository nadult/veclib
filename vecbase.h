#ifndef VECLIB_VECBASE_H
#define VECLIB_VECBASE_H

#include "veclib_conf.h"
//#include <boost/static_assert.hpp>

union UValue32
{
	UValue32(u32 v) :u(v) { }
	UValue32(i32 v) :i(v) { }
	UValue32(f32 v) :f(v) { }

	f32 f;
	i32 i;
	u32 u;
};

union UValue64 {
	UValue64(u64 v) :u(v) { }
	UValue64(i64 v) :i(v) { }
	UValue64(f64 v) :f(v) { }

	f64 f;
	i64 i;
	u64 u;
};

typedef UValue32 UValue;

template <class Dst,class Src>
Dst BitCast(const Src &src) {
	union { Dst d; Src s; } u;
	u.s=src;
	return u.d;
}
template <class Base,int m,int n> struct CConst { static Base Value() { return Base(m)/Base(n); } };
template <class Base,bool v> struct CBConst { static Base Value() { return Base(v); } };

// Returns constant of value m/n of type Base
// Works only for floating point types
template <class Base,int m,int n>	Base Const() { return CConst<Base,m,n>::Value(); }

// Returns constant of value m/n of type Base
// Works for both floating point and integral types
template <class Base,int m>			Base Const() { return CConst<Base,m,1>::Value(); }

// Returns constant boolean value of type Base
template <class Base,bool v>		Base BConst() { return CBConst<Base,v>::Value(); }


// Full double precision
template <class Base> Base ConstPI() { return Const<Base,		245850922	,78256779>(); };
template <class Base> Base Const2PI() { return Const<Base,		2*245850922	,78256779>(); };
template <class Base> Base ConstInvPI() { return Const<Base,	78256779	,245850922>(); };
template <class Base> Base ConstInv2PI() { return Const<Base,	78256779	,2*245850922>(); };
template <class Base> Base ConstEpsilon() { return Const<Base,	1			,10000>(); };

/*!

*/
template <class T>
struct ScalarInfo {
	enum { multiplicity=1, floatingPoint=1 };
	typedef bool TBool;

	// n must be < multiplicity
	INLINE static bool ElementMask(int n) {
		return 1;
	}
};

INLINE float Sqrt(float v)							{ return sqrtf(v); }
INLINE float Inv(float v)							{ return 1.0f/v; }
INLINE float RSqrt(float v)							{ return 1.0f/Sqrt(v); }
INLINE float FastInv(float v)						{ return Inv(v); }
INLINE float FastRSqrt(float v)						{ return RSqrt(v); }
INLINE float Condition(bool expr,float a,float b)	{ return expr?a:b; }
INLINE float Condition(bool expr,float v)			{ return expr?v:0.0f; }
INLINE int SignMask(float v)						{ return v<0.0f?1:0; }
INLINE float Abs(float v)							{ return v < 0.0f ? -v : v; }
INLINE int Round(float f)							{ return int(f+0.5f); }
INLINE int Trunc(float f)							{ return int(f); }

INLINE float Sin(float rad)							{ return sin(rad); }
INLINE float Cos(float rad)							{ return cos(rad); }

INLINE float FRand() { return float(rand())/float(RAND_MAX); }


INLINE bool ForAny(bool expr) { return expr; }
INLINE bool ForAll(bool expr) { return expr; }

/// Returns bit mask, bit n is set if expression is true for element n
INLINE int ForWhich(bool expr) { return expr?1:0; }

template <class T,class T1> INLINE T Max(const T &a,const T1 &b) { return a>b?a:b; }
template <class T,class T1> INLINE T Min(const T &a,const T1 &b) { return a<b?a:b; }
template <class T> INLINE T Clamp(const T &obj,const T &min,const T &max) { return Min(Max(obj,min),max); }
template <class T> INLINE T VClamp(const T &obj,const T &min,const T &max) { return VMin(VMax(obj,min),max); }
template <class Obj,class Scl> INLINE Obj Lerp(const Obj &a,const Obj &b,const Scl &x) { return a+(b-a)*x; }
template <class Obj,class Scl> INLINE Obj VLerp(const Obj &a,const Obj &b,const Scl &x) { return a+(b-a)*x; }

template <class T> INLINE void Swap(T &a,T &b) { T temp(a); a=b; b=temp; }
template <class T> INLINE void Convert(const T &in,T &out) { out=in; }

#endif

