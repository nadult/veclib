#ifndef VECLIB_SSE_F32_H
#define VECLIB_SSE_F32_H

#include "sse/base.h"


class f32x4b;
class f32x4bn;

class f32x4 
{
public:
	f32x4() { }
	f32x4(__m128 m) :m(m) { }
	f32x4(const f32x4 &rhs) :m(rhs.m) { }
    f32x4(float a,float b,float c,float d) :m(_mm_set_ps(d,c,b,a)) { }
	f32x4(float v) :m(_mm_set1_ps(v)) { }
	const f32x4 operator=(const f32x4 &rhs) { m = rhs.m; return *this; }
	operator __m128() const { return m; }

	const f32x4 operator+=(f32x4 v) { m=_mm_add_ps(m,v.m); return *this; }
	const f32x4 operator-=(f32x4 v) { m=_mm_sub_ps(m,v.m); return *this; }
	const f32x4 operator*=(f32x4 v) { m=_mm_mul_ps(m,v.m); return *this; }
	const f32x4 operator/=(f32x4 v) { m=_mm_div_ps(m,v.m); return *this; }

	const f32x4 operator-() const { return _mm_sub_ps(_mm_setzero_ps(),m); }
	operator f32*() { return f; }
	operator const f32*() const { return f; }

	union {
		__m128 m;
		float f[4];
	};
};

class f32x4b
{
public:
	f32x4b() { }
	//TODO: explicit?
	f32x4b(__m128 v) :m(v) { }
	f32x4b(bool v) :m(_mm_set1_ps(BitCast<float, u32>(v?0xffffffff : 0))) { }

	const f32x4b operator^(f32x4b v) const	{ return _mm_xor_ps(m,v.m); }
	const f32x4b operator&&(f32x4b v) const	{ return _mm_and_ps(m,v.m); }
	const f32x4b operator||(f32x4b v) const	{ return _mm_or_ps(m,v.m); }

	__m128 m;
};

class f32x4bn
{
public:
	const f32x4bn operator^(f32x4b v) const		{ return _mm_xor_ps(m,v.m); }
	const f32x4b operator^(f32x4bn v) const		{ return _mm_xor_ps(m,v.m); }
	const f32x4b operator!() const				{ return f32x4b(m); }

	const f32x4b operator&&(f32x4b v) const		{ return _mm_andnot_ps(m,v.m); }
	const f32x4bn operator&&(f32x4bn v) const	{ return _mm_or_ps(m,v.m); }

	const f32x4bn operator||(f32x4bn v) const	{ return _mm_and_ps(m,v.m); }
	const f32x4b operator||(f32x4b v) const		{ return _mm_or_ps(_mm_andnot_ps(m,_mm_set1_ps(BitCast<float,u32>(~0))),v.m); }
	operator f32x4b() const						{ return _mm_andnot_ps(m,_mm_set1_ps(BitCast<float,u32>(~0))); }

	const __m128 &NegM() const { return m; }
private:
	f32x4bn(__m128 v) :m(v) { }
	friend const f32x4bn operator!(f32x4b);
	friend const f32x4bn operator^(f32x4b,f32x4bn);

	// To access it you have to
	// convert to f32x4b first
	__m128 m;
};

inline const f32x4bn operator!(f32x4b v)				{ return f32x4bn(v.m); }
inline const f32x4bn operator^(f32x4b a,f32x4bn b)		{ return f32x4bn(_mm_xor_ps(a.m,b.NegM())); }
inline const f32x4b operator&&(f32x4b a,f32x4bn b)		{ return _mm_andnot_ps(b.NegM(),a.m); }
inline const f32x4b operator||(f32x4b a,f32x4bn b)
	{ return _mm_or_ps(a.m, _mm_andnot_ps(b.NegM(), _mm_set1_ps(BitCast<float,u32>(~0)))); }

inline bool ForAny(f32x4b v)	{ return _mm_movemask_ps(v.m)?1:0; }
inline bool ForAll(f32x4b v)	{ return _mm_movemask_ps(v.m)==15; }
inline int ForWhich(f32x4b v)	{ return _mm_movemask_ps(v.m); }

inline const f32x4b operator ==(f32x4 a,f32x4 b) { return _mm_cmpeq_ps(a.m,b.m); }
inline const f32x4b operator !=(f32x4 a,f32x4 b) { return _mm_cmpneq_ps(a.m,b.m); }
inline const f32x4b operator <=(f32x4 a,f32x4 b) { return _mm_cmple_ps(a.m,b.m); }
inline const f32x4b operator >=(f32x4 a,f32x4 b) { return _mm_cmpge_ps(a.m,b.m); }
inline const f32x4b operator < (f32x4 a,f32x4 b) { return _mm_cmplt_ps(a.m,b.m); }
inline const f32x4b operator > (f32x4 a,f32x4 b) { return _mm_cmpgt_ps(a.m,b.m); }

inline const f32x4 operator+(f32x4 a,f32x4 b) { return _mm_add_ps(a.m, b.m); }
inline const f32x4 operator-(f32x4 a,f32x4 b) { return _mm_sub_ps(a.m, b.m); }
inline const f32x4 operator*(f32x4 a,f32x4 b) { return _mm_mul_ps(a.m, b.m); }
inline const f32x4 operator/(f32x4 a,f32x4 b) { return _mm_div_ps(a.m, b.m); }

inline const f32x4 Sqrt(f32x4 v)		{ return _mm_sqrt_ps(v.m); }
inline const f32x4 Inv(f32x4 v)			{ return _mm_nrrcp_ps(v.m); }
inline const f32x4 RSqrt(f32x4 v)		{ return _mm_nrrsqrt_ps(v.m); }
inline const f32x4 FastInv(f32x4 v)		{ return _mm_rcp_ps(v.m); }
inline const f32x4 FastRSqrt(f32x4 v)	{ return _mm_rsqrt_ps(v.m); }


inline const f32x4 Abs(f32x4 v)			{ return _mm_and_ps(_mm_set1_ps(BitCast<float,u32>(0x7fffffff)),v.m); }
inline const f32x4 Min(f32x4 a,f32x4 b)	{ return _mm_min_ps(a.m,b.m); }
inline const f32x4 Max(f32x4 a,f32x4 b)	{ return _mm_max_ps(a.m,b.m); }
inline int SignMask(f32x4 v)			{ return _mm_movemask_ps(v.m); }

inline const f32x4 Condition(f32x4b test,f32x4 v1,f32x4 v2) __attribute__((always_inline));
inline const f32x4 Condition(f32x4b test,f32x4 v1,f32x4 v2) {
	return _mm_or_ps(_mm_and_ps(test.m,v1.m),_mm_andnot_ps(test.m,v2.m));
}
inline const f32x4 Condition(f32x4bn test,f32x4 v1,f32x4 v2) __attribute__((always_inline));
inline const f32x4 Condition(f32x4bn test,f32x4 v1,f32x4 v2) {
	return _mm_or_ps(_mm_andnot_ps(test.NegM(),v1.m),_mm_and_ps(test.NegM(),v2.m));
}
inline const f32x4 Condition(f32x4b test,f32x4 v1)		{ return _mm_and_ps(test.m,v1.m); }
inline const f32x4 Condition(f32x4bn test,f32x4 v1)		{ return _mm_andnot_ps(test.NegM(),v1.m); }

template <>
struct ScalarInfo<f32x4> {
	enum { multiplicity=4, floatingPoint=1 };
	typedef f32x4b TBool;

	static f32x4b ElementMask(int n) {
		static f32x4b elems[4]={
			_mm_set_ps(UValue(0).f,UValue(0).f,UValue(0).f,UValue(0xffffffff).f),
			_mm_set_ps(UValue(0).f,UValue(0).f,UValue(0xffffffff).f,UValue(0).f),
			_mm_set_ps(UValue(0).f,UValue(0xffffffff).f,UValue(0).f,UValue(0).f),
			_mm_set_ps(UValue(0xffffffff).f,UValue(0).f,UValue(0).f,UValue(0).f),
		};

		return elems[n];
	}
};

inline void Broadcast(float in, f32x4 &out) { out=_mm_load1(in); }
inline void Convert(const float in[4], f32x4 &out) { out=_mm_load4(in); }
inline void Convert(f32x4 in, float out[4]) { _mm_store4(in.m,out); }

inline void Convert(float x,float y,float z,float w,f32x4 &out) { out=_mm_set_ps(w,z,y,x); }
inline void Convert(f32x4 in,float &outX,float &outY,float &outZ,float &outW) {
	_mm_store_ss(&outX,in.m);
	_mm_store_ss(&outY,_mm_shuffle(1,in.m));
	_mm_store_ss(&outZ,_mm_shuffle(2,in.m));
	_mm_store_ss(&outW,_mm_shuffle(3,in.m));
}


#endif

