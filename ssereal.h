#if !defined(VECLIB_SSEREAL_H) && VECLIB_SSE_VER>=0x10
#define VECLIB_SSEREAL_H

#include "sse.h"


class SSERealMask;
class SSERealMaskNeg;

class SSEReal
{
public:
	INLINE SSEReal() { }
	INLINE SSEReal(const __m128 &v) :m(v) { }
    INLINE SSEReal(float a,float b,float c,float d) :m(_mm_set_ps(a,b,c,d)) { }
	INLINE SSEReal(float v) :m(_mm_set1_ps(v)) { }

	INLINE const SSEReal &operator+=(const SSEReal &v) { m=_mm_add_ps(m,v.m); return *this; }
	INLINE const SSEReal &operator-=(const SSEReal &v) { m=_mm_sub_ps(m,v.m); return *this; }
	INLINE const SSEReal &operator*=(const SSEReal &v) { m=_mm_mul_ps(m,v.m); return *this; }
	INLINE const SSEReal &operator/=(const SSEReal &v) { m=_mm_div_ps(m,v.m); return *this; }

	INLINE SSEReal operator-() const { return _mm_sub_ps(_mm_setzero_ps(),m); }

	__m128 m;
};

template <int m,int n>
struct CConst<SSEReal,m,n> { static SSEReal Value() { return SSEReal(SSEFloatConst<m,n>::value); } };

class SSERealMask
{
public:
	INLINE SSERealMask() { }
	INLINE SSERealMask(const __m128 &v) :m(v) { }

	INLINE SSERealMask operator^(const SSERealMask &v) const	{ return _mm_xor_ps(m,v.m); }
	INLINE SSERealMask operator&&(const SSERealMask &v) const	{ return _mm_and_ps(m,v.m); }
	INLINE SSERealMask operator||(const SSERealMask &v) const	{ return _mm_or_ps(m,v.m); }

	__m128 m;
};

template <bool v>
struct CBConst<SSERealMask,v> { static SSERealMask Value() { return SSERealMask(SSERealMaskConst<v?0xffffffff:0>::value); } };

class SSERealMaskNeg
{
public:
	INLINE SSERealMaskNeg operator^(const SSERealMask &v) const		{ return _mm_xor_ps(m,v.m); }
	INLINE SSERealMask operator^(const SSERealMaskNeg &v) const		{ return _mm_xor_ps(m,v.m); }
	INLINE SSERealMask operator!() const							{ return SSERealMask(m); }

	INLINE SSERealMask operator&&(const SSERealMask &v) const		{ return _mm_andnot_ps(m,v.m); }
	INLINE SSERealMaskNeg operator&&(const SSERealMaskNeg &v) const	{ return _mm_or_ps(m,v.m); }

	INLINE SSERealMaskNeg operator||(const SSERealMaskNeg &v) const	{ return _mm_and_ps(m,v.m); }
	INLINE SSERealMask operator||(const SSERealMask &v) const		{ return _mm_or_ps(_mm_andnot_ps(m,SSERealMaskConst<0xffffffff>::value),v.m); }
	operator SSERealMask() const									{ return _mm_andnot_ps(m,SSERealMaskConst<0xffffffff>::value); }

	const __m128 &NegM() const { return m; }
private:
	INLINE SSERealMaskNeg(const __m128 &v) :m(v) { }
	friend SSERealMaskNeg operator!(const SSERealMask&);
	friend SSERealMaskNeg operator^(const SSERealMask&,const SSERealMaskNeg&);

	// To access it you have to
	// convert to SSERealMask first
	__m128 m;
};

INLINE SSERealMaskNeg operator!(const SSERealMask &v)							{ return SSERealMaskNeg(v.m); }
INLINE SSERealMaskNeg operator^(const SSERealMask &a,const SSERealMaskNeg &b)	{ return SSERealMaskNeg(_mm_xor_ps(a.m,b.NegM())); }
INLINE SSERealMask operator&&(const SSERealMask &a,const SSERealMaskNeg &b)		{ return _mm_andnot_ps(b.NegM(),a.m); }
INLINE SSERealMask operator||(const SSERealMask &a,const SSERealMaskNeg &b)
	{ return _mm_or_ps(a.m,_mm_andnot_ps(b.NegM(),SSERealMaskConst<0xffffffff>::value)); }

INLINE bool ForAny(const SSERealMask &v) { return _mm_movemask_ps(v.m)?1:0; }
INLINE bool ForAll(const SSERealMask &v) { return _mm_movemask_ps(v.m)==15; }
INLINE int ForWhich(const SSERealMask &v) { return _mm_movemask_ps(v.m); }



INLINE SSERealMask operator ==(const SSEReal &a,const SSEReal &b) { return _mm_cmpeq_ps(a.m,b.m); }
INLINE SSERealMask operator !=(const SSEReal &a,const SSEReal &b) { return _mm_cmpneq_ps(a.m,b.m); }
INLINE SSERealMask operator <=(const SSEReal &a,const SSEReal &b) { return _mm_cmple_ps(a.m,b.m); }
INLINE SSERealMask operator >=(const SSEReal &a,const SSEReal &b) { return _mm_cmpge_ps(a.m,b.m); }
INLINE SSERealMask operator < (const SSEReal &a,const SSEReal &b) { return _mm_cmplt_ps(a.m,b.m); }
INLINE SSERealMask operator > (const SSEReal &a,const SSEReal &b) { return _mm_cmpgt_ps(a.m,b.m); }

INLINE SSEReal operator+(const SSEReal &a,const SSEReal &b) { SSEReal out(a); out+=b; return out; }
INLINE SSEReal operator-(const SSEReal &a,const SSEReal &b) { SSEReal out(a); out-=b; return out; }
INLINE SSEReal operator*(const SSEReal &a,const SSEReal &b) { SSEReal out(a); out*=b; return out; }
INLINE SSEReal operator/(const SSEReal &a,const SSEReal &b) { SSEReal out(a); out/=b; return out; }

INLINE SSEReal Sqrt		(const SSEReal &v) { return _mm_sqrt_ps(v.m); }
INLINE SSEReal Inv		(const SSEReal &v) { return _mm_nrrcp_ps(v.m); }
INLINE SSEReal RSqrt	(const SSEReal &v) { return _mm_nrrsqrt_ps(v.m); }
INLINE SSEReal FastInv	(const SSEReal &v) { return _mm_rcp_ps(v.m); }
INLINE SSEReal FastRSqrt(const SSEReal &v) { return _mm_rsqrt_ps(v.m); }


INLINE SSEReal Abs(const SSEReal &v)					{ return _mm_and_ps(SSERealMaskConst<0x7fffffff>::value,v.m); }
INLINE SSEReal Min(const SSEReal &a,const SSEReal &b)	{ return _mm_min_ps(a.m,b.m); }
INLINE SSEReal Max(const SSEReal &a,const SSEReal &b)	{ return _mm_max_ps(a.m,b.m); }
INLINE int SignMask(const SSEReal &v)					{ return _mm_movemask_ps(v.m); }

INLINE SSEReal Condition(const SSERealMask &test,const SSEReal &v1,const SSEReal &v2) {
	return _mm_or_ps(_mm_and_ps(test.m,v1.m),_mm_andnot_ps(test.m,v2.m));
}
INLINE SSEReal Condition(const SSERealMaskNeg &test,const SSEReal &v1,const SSEReal &v2) {
	return _mm_or_ps(_mm_andnot_ps(test.NegM(),v1.m),_mm_and_ps(test.NegM(),v2.m));
}
INLINE SSEReal Condition(const SSERealMask &test,const SSEReal &v1) {
	return _mm_and_ps(test.m,v1.m);
}
INLINE SSEReal Condition(const SSERealMaskNeg &test,const SSEReal &v1) {
	return _mm_andnot_ps(test.NegM(),v1.m);
}

template <>
struct ScalarInfo<SSEReal> {
	enum { multiplicity=4, floatingPoint=1 };
	typedef SSERealMask TBool;

	INLINE static SSERealMask ElementMask(int n) {
		static SSERealMask elems[4]={
			SSERealMask(_mm_set_ps(UValue(0).f,UValue(0).f,UValue(0).f,UValue(0xffffffff).f)),
			SSERealMask(_mm_set_ps(UValue(0).f,UValue(0).f,UValue(0xffffffff).f,UValue(0).f)),
			SSERealMask(_mm_set_ps(UValue(0).f,UValue(0xffffffff).f,UValue(0).f,UValue(0).f)),
			SSERealMask(_mm_set_ps(UValue(0xffffffff).f,UValue(0).f,UValue(0).f,UValue(0).f)),
		};

		return elems[n];
	}
};

INLINE void Broadcast(const float &in,SSEReal &out) { out=_mm_load1(in); }
INLINE void Convert(const float in[4],SSEReal &out) { out=_mm_load4(in); }
INLINE void Convert(const SSEReal &in,float out[4]) { _mm_store4(in.m,out); }

INLINE void Convert(float x,float y,float z,float w,SSEReal &out) { out=_mm_set_ps(w,z,y,x); }
INLINE void Convert(const SSEReal &in,float &outX,float &outY,float &outZ,float &outW) {
	_mm_store_ss(&outX,in.m);
	_mm_store_ss(&outY,_mm_shuffle(1,in.m));
	_mm_store_ss(&outZ,_mm_shuffle(2,in.m));
	_mm_store_ss(&outW,_mm_shuffle(3,in.m));
}


#endif

