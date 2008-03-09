#ifndef VECLIB_VECBASE_H
#define VECLIB_VECBASE_H

#include "veclib_conf.h"
//#include <boost/static_assert.hpp>

namespace basetypes
{
	typedef unsigned char		u8;
	typedef char				i8;
	typedef short				i16;
	typedef unsigned short		u16;
	typedef int					i32;
	typedef unsigned int		u32;
	typedef long long			i64;
	typedef unsigned long long	u64;
	
	typedef float				f32;
	typedef double				f64;
	
	typedef unsigned int		uint;
}

using namespace basetypes;
	
union UValue
{
	UValue(u32 v) :u(v) { }
	UValue(i32 v) :i(v) { }
	UValue(f32 v) :f(v) { }

	f32 f;
	i32 i;
	u32 u;
};

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

template <class Base> Base ConstPI() { return Const<Base,		75948	,24175>(); };
template <class Base> Base Const2PI() { return Const<Base,		2*75948	,24175>(); };
template <class Base> Base ConstInvPI() { return Const<Base,	24175	,75948>(); };
template <class Base> Base ConstInv2PI() { return Const<Base,	24175	,2*75948>(); };
template <class Base> Base ConstEpsilon() { return Const<Base,	1		,10000>(); };

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

#if VECLIB_SSE_VER>=0x10

INLINE float Sqrt(float v)
{
	__m128 t=_mm_sqrt_ss(_mm_load_ss(&v));
	return ((float*)&t)[0];
}
INLINE float Inv(float v)
{
	__m128 tv=_mm_load_ss(&v);
	__m128 t=_mm_rcp_ss(tv);
	t=_mm_sub_ss(_mm_add_ss(t,t),_mm_mul_ss(_mm_mul_ss(tv,t),t));
	return ((float*)&t)[0];
}
INLINE float RSqrt(float v)
{
	static const __m128 coeff=_mm_set_ps(0,0,3.0f,0.5f);

	__m128 tv=_mm_load_ss(&v);
	__m128 t=_mm_rsqrt_ps(tv);
    t= _mm_mul_ss(	_mm_mul_ss(coeff,t),
					_mm_sub_ss(_mm_shuffle_ps(coeff,coeff,1),_mm_mul_ss(_mm_mul_ps(tv,t),t)) );

	return ((float*)&t)[0];
}
INLINE float FastInv(float v)						{ __m128 t=_mm_rcp_ss(_mm_load_ss(&v)); return ((float*)&t)[0]; }
INLINE float FastRSqrt(float v)						{ __m128 t=_mm_rsqrt_ss(_mm_load_ss(&v)); return ((float*)&t)[0]; }
INLINE float Abs(float v) {
	static const __m128 coeff=_mm_set1_ps(UValue(0x7fffffff).f);
	__m128 t=_mm_and_ps(_mm_load_ss(&v),coeff); return ((float*)&t)[0];
}
INLINE float Min(float a,float b)					{ __m128 t=_mm_min_ss(_mm_load_ss(&a),_mm_load_ss(&b)); return ((float*)&t)[0]; }
INLINE float Max(float a,float b)					{ __m128 t=_mm_max_ss(_mm_load_ss(&a),_mm_load_ss(&b)); return ((float*)&t)[0]; }
INLINE float Condition(bool expr,float a,float b)	{ return expr?a:b; }
INLINE float Condition(bool expr,float v)			{ return expr?v:0.0f; }
INLINE int SignMask(float v)						{ return _mm_movemask_ps(_mm_load_ss(&v))&1; }

#else

INLINE float Sqrt(float v)							{ return sqrtf(v); }
INLINE float Inv(float v)							{ return 1.0f/v; }
INLINE float RSqrt(float v)							{ return 1.0f/Sqrt(v); }
INLINE float FastInv(float v)						{ return Inv(v); }
INLINE float FastRSqrt(float v)						{ return RSqrt(v); }
INLINE float Abs(float v)							{ return v < 0.0f ? -v : v; }
INLINE float Min(float a,float b)					{ return a < b ? a : b; }
INLINE float Max(float a,float b)					{ return a > b ? a : b; }
INLINE float Condition(bool expr,float a,float b)	{ return expr?a:b; }
INLINE float Condition(bool expr,float v)			{ return expr?v:0.0f; }
INLINE int SignMask(float v)						{ return v<0.0f?1:0; }

#endif

INLINE float Sin(float rad)							{ return sin(rad); }
INLINE float Cos(float rad)							{ return cos(rad); }

INLINE float FRand() { return float(rand())/float(RAND_MAX); }

INLINE bool ForAny(bool expr) { return expr; }
INLINE bool ForAll(bool expr) { return expr; }

/// Returns bit mask, bit n is set if expression is true for element n
INLINE int ForWhich(bool expr) { return expr?1:0; }

template <class T> INLINE T Clamp(const T &obj,const T &min,const T &max) { return Min(Max(obj,min),max); }
template <class Obj,class Scl> INLINE Obj Lerp(const Obj &a,const Obj &b,const Scl &x) { return a+(b-a)*x; }

template <class T> INLINE void Swap(T &a,T &b) { T temp(a); a=b; b=temp; }
template <class T> INLINE void Convert(const T &in,T &out) { out=in; }

#endif

