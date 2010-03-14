#if !defined(VECLIB_SSEREAL_H) && VECLIB_SSE_VER>=0x10
#define VECLIB_SSEREAL_H

#include "ssebase.h"


class f32x4b;
class f32x4bn;

class f32x4 
{
public:
	INLINE f32x4() { }
	INLINE f32x4(const __m128 &v) :m(v) { }
	INLINE f32x4(const f32x4 &rhs) :m(rhs.m) { }
    INLINE f32x4(float a,float b,float c,float d) :m(_mm_set_ps(d,c,b,a)) { }
	INLINE f32x4(float v) :m(_mm_set1_ps(v)) { }
	INLINE const f32x4 &operator=(const f32x4 &rhs) { m=rhs.m; return *this; }

	INLINE const f32x4 &operator+=(const f32x4 &v) { m=_mm_add_ps(m,v.m); return *this; }
	INLINE const f32x4 &operator-=(const f32x4 &v) { m=_mm_sub_ps(m,v.m); return *this; }
	INLINE const f32x4 &operator*=(const f32x4 &v) { m=_mm_mul_ps(m,v.m); return *this; }
	INLINE const f32x4 &operator/=(const f32x4 &v) { m=_mm_div_ps(m,v.m); return *this; }

	INLINE f32x4 operator-() const { return _mm_sub_ps(_mm_setzero_ps(),m); }
	operator f32*() { return f; }
	operator const f32*() const { return f; }

	union {
		__m128 m;
		float f[4];
	};
};

template <int m,int n>
struct CConst<f32x4,m,n> { static f32x4 Value() { const float v=((float)m)/((float)n); return f32x4(v); } };

class f32x4b
{
public:
	INLINE f32x4b() { }
	INLINE f32x4b(const __m128 &v) :m(v) { }

	INLINE f32x4b operator^(const f32x4b &v) const	{ return _mm_xor_ps(m,v.m); }
	INLINE f32x4b operator&&(const f32x4b &v) const	{ return _mm_and_ps(m,v.m); }
	INLINE f32x4b operator||(const f32x4b &v) const	{ return _mm_or_ps(m,v.m); }

	__m128 m;
};

template <bool v>
struct CBConst<f32x4b,v> { static f32x4b Value() { return f32x4b(BitCast<float,u32>(v?0xffffffff:0)); } };

class f32x4bn
{
public:
	INLINE f32x4bn operator^(const f32x4b &v) const		{ return _mm_xor_ps(m,v.m); }
	INLINE f32x4b operator^(const f32x4bn &v) const		{ return _mm_xor_ps(m,v.m); }
	INLINE f32x4b operator!() const							{ return f32x4b(m); }

	INLINE f32x4b operator&&(const f32x4b &v) const		{ return _mm_andnot_ps(m,v.m); }
	INLINE f32x4bn operator&&(const f32x4bn &v) const	{ return _mm_or_ps(m,v.m); }

	INLINE f32x4bn operator||(const f32x4bn &v) const	{ return _mm_and_ps(m,v.m); }
	INLINE f32x4b operator||(const f32x4b &v) const		{ return _mm_or_ps(_mm_andnot_ps(m,_mm_set1_ps(BitCast<float,u32>(~0))),v.m); }
	operator f32x4b() const								{ return _mm_andnot_ps(m,_mm_set1_ps(BitCast<float,u32>(~0))); }

	const __m128 &NegM() const { return m; }
private:
	INLINE f32x4bn(const __m128 &v) :m(v) { }
	friend f32x4bn operator!(const f32x4b&);
	friend f32x4bn operator^(const f32x4b&,const f32x4bn&);

	// To access it you have to
	// convert to f32x4b first
	__m128 m;
};

INLINE f32x4bn operator!(const f32x4b &v)						{ return f32x4bn(v.m); }
INLINE f32x4bn operator^(const f32x4b &a,const f32x4bn &b)		{ return f32x4bn(_mm_xor_ps(a.m,b.NegM())); }
INLINE f32x4b operator&&(const f32x4b &a,const f32x4bn &b)		{ return _mm_andnot_ps(b.NegM(),a.m); }
INLINE f32x4b operator||(const f32x4b &a,const f32x4bn &b)
	{ return _mm_or_ps(a.m,_mm_andnot_ps(b.NegM(),_mm_set1_ps(BitCast<float,u32>(~0)))); }

INLINE bool ForAny(const f32x4b &v) { return _mm_movemask_ps(v.m)?1:0; }
INLINE bool ForAll(const f32x4b &v) { return _mm_movemask_ps(v.m)==15; }
INLINE int ForWhich(const f32x4b &v) { return _mm_movemask_ps(v.m); }



INLINE f32x4b operator ==(const f32x4 &a,const f32x4 &b) { return _mm_cmpeq_ps(a.m,b.m); }
INLINE f32x4b operator !=(const f32x4 &a,const f32x4 &b) { return _mm_cmpneq_ps(a.m,b.m); }
INLINE f32x4b operator <=(const f32x4 &a,const f32x4 &b) { return _mm_cmple_ps(a.m,b.m); }
INLINE f32x4b operator >=(const f32x4 &a,const f32x4 &b) { return _mm_cmpge_ps(a.m,b.m); }
INLINE f32x4b operator < (const f32x4 &a,const f32x4 &b) { return _mm_cmplt_ps(a.m,b.m); }
INLINE f32x4b operator > (const f32x4 &a,const f32x4 &b) { return _mm_cmpgt_ps(a.m,b.m); }

INLINE f32x4 operator+(const f32x4 &a,const f32x4 &b) { f32x4 out(a); out+=b; return out; }
INLINE f32x4 operator-(const f32x4 &a,const f32x4 &b) { f32x4 out(a); out-=b; return out; }
INLINE f32x4 operator*(const f32x4 &a,const f32x4 &b) { f32x4 out(a); out*=b; return out; }
INLINE f32x4 operator/(const f32x4 &a,const f32x4 &b) { f32x4 out(a); out/=b; return out; }

INLINE f32x4 Sqrt		(const f32x4 &v) { return _mm_sqrt_ps(v.m); }
INLINE f32x4 Inv		(const f32x4 &v) { return _mm_nrrcp_ps(v.m); }
INLINE f32x4 RSqrt		(const f32x4 &v) { return _mm_nrrsqrt_ps(v.m); }
INLINE f32x4 FastInv	(const f32x4 &v) { return _mm_rcp_ps(v.m); }
INLINE f32x4 FastRSqrt	(const f32x4 &v) { return _mm_rsqrt_ps(v.m); }


INLINE f32x4 Abs(const f32x4 &v)				{ return _mm_and_ps(_mm_set1_ps(BitCast<float,u32>(0x7fffffff)),v.m); }
INLINE f32x4 Min(const f32x4 &a,const f32x4 &b)	{ return _mm_min_ps(a.m,b.m); }
INLINE f32x4 Max(const f32x4 &a,const f32x4 &b)	{ return _mm_max_ps(a.m,b.m); }
INLINE int SignMask(const f32x4 &v)				{ return _mm_movemask_ps(v.m); }

INLINE f32x4 Condition(const f32x4b &test,const f32x4 &v1,const f32x4 &v2) {
	return _mm_or_ps(_mm_and_ps(test.m,v1.m),_mm_andnot_ps(test.m,v2.m));
}
INLINE f32x4 Condition(const f32x4bn &test,const f32x4 &v1,const f32x4 &v2) {
	return _mm_or_ps(_mm_andnot_ps(test.NegM(),v1.m),_mm_and_ps(test.NegM(),v2.m));
}
INLINE f32x4 Condition(const f32x4b &test,const f32x4 &v1)		{ return _mm_and_ps(test.m,v1.m); }
INLINE f32x4 Condition(const f32x4bn &test,const f32x4 &v1)		{ return _mm_andnot_ps(test.NegM(),v1.m); }

template <>
struct ScalarInfo<f32x4> {
	enum { multiplicity=4, floatingPoint=1 };
	typedef f32x4b TBool;

	INLINE static f32x4b ElementMask(int n) {
		static f32x4b elems[4]={
			_mm_set_ps(UValue(0).f,UValue(0).f,UValue(0).f,UValue(0xffffffff).f),
			_mm_set_ps(UValue(0).f,UValue(0).f,UValue(0xffffffff).f,UValue(0).f),
			_mm_set_ps(UValue(0).f,UValue(0xffffffff).f,UValue(0).f,UValue(0).f),
			_mm_set_ps(UValue(0xffffffff).f,UValue(0).f,UValue(0).f,UValue(0).f),
		};

		return elems[n];
	}
};

INLINE void Broadcast(const float &in,f32x4 &out) { out=_mm_load1(in); }
INLINE void Convert(const float in[4],f32x4 &out) { out=_mm_load4(in); }
INLINE void Convert(const f32x4 &in,float out[4]) { _mm_store4(in.m,out); }

INLINE void Convert(float x,float y,float z,float w,f32x4 &out) { out=_mm_set_ps(w,z,y,x); }
INLINE void Convert(const f32x4 &in,float &outX,float &outY,float &outZ,float &outW) {
	_mm_store_ss(&outX,in.m);
	_mm_store_ss(&outY,_mm_shuffle(1,in.m));
	_mm_store_ss(&outZ,_mm_shuffle(2,in.m));
	_mm_store_ss(&outW,_mm_shuffle(3,in.m));
}


#endif

