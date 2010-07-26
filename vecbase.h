#ifndef VECLIB_VECBASE_H
#define VECLIB_VECBASE_H

#include "veclib_conf.h"

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

template <class Dst, class Src>
const Dst BitCast(const Src src) {
	union { Dst d; Src s; } u;
	u.s = src;
	return u.d;
}

namespace constant {
    static const float pi       = 3.14159265358979;
    static const float e        = 2.71828182845905;
    static const float inf      = 1.0f / 0.0f;
    static const float epsilon  = 0.0001f;
}

template <class T>
struct ScalarInfo {
	enum { multiplicity=1, floatingPoint=1 };
	typedef bool TBool;

	// n must be < multiplicity
	inline static bool ElementMask(int n) {
		return 1;
	}
};

inline float Sqrt(float v)							{ return sqrtf(v); }
inline float Inv(float v)							{ return 1.0f/v; }
inline float RSqrt(float v)							{ return 1.0f/Sqrt(v); }
inline float FastInv(float v)						{ return Inv(v); }
inline float FastRSqrt(float v)						{ return RSqrt(v); }
inline float Condition(bool expr, float a, float b)	{ return expr?a:b; }
inline float Condition(bool expr, float v)			{ return expr?v:0.0f; }
inline int SignMask(float v)						{ return v<0.0f?1:0; }
inline float Abs(float v)							{ return v < 0.0f ? -v : v; }
inline int Round(float f)							{ return int(f+0.5f); }
inline int Trunc(float f)							{ return int(f); }

inline float Sin(float rad)							{ return sin(rad); }
inline float Cos(float rad)							{ return cos(rad); }

inline bool ForAny(bool expr) { return expr; }
inline bool ForAll(bool expr) { return expr; }

/// Returns bit mask, bit n is set if expression is true for element n
inline int ForWhich(bool expr) { return expr?1 : 0; }

template <class T,class T1> inline T Max(T a, T1 b) { return a>b?a:b; }
template <class T,class T1> inline T Min(T a, T1 b) { return a<b?a:b; }
template <class T> inline const T Clamp(T obj, T min, T max) { return Min(Max(obj, min), max); }
template <class T> inline const T VClamp(T obj, T min, T max) { return VMin(VMax(obj, min), max); }

template <class Obj, class Scl> inline const Obj  Lerp(Obj a, Obj b, Scl x) { return a + (b - a) * x; }
template <class Obj, class Scl> inline const Obj VLerp(Obj a, Obj b, Scl x) { return a + (b - a) * x; }

template <class T> inline void Swap(T &a, T &b) { T temp(a); a = b; b = temp; }
template <class T> inline void Convert(T in, T &out) { out = in; }

#endif

