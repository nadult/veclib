#if !defined(VECLIB_SSEREAL_H) && VECLIB_SSE_VER>=0x10
#define VECLIB_SSEREAL_H

#include "sse.h"
#include "ssemask.h"

class SSEReal
{
public:
	INLINE SSEReal() { }
	INLINE SSEReal(const __m128 &v) :m(v) { }
    INLINE SSEReal(float a,float b,float c,float d) :m(_mm_set_ps(a,b,c,d)) { } \
	INLINE SSEReal(float v) :m(_mm_set1_ps(v)) { }

#define GEN_SOP(sop,mmname) \
	INLINE const SSEReal &operator sop(const SSEReal &v) { \
		m=mmname(m,v.m); \
		return *this; \
	}

	GEN_SOP(+=,_mm_add_ps)
	GEN_SOP(-=,_mm_sub_ps)
	GEN_SOP(*=,_mm_mul_ps)
	GEN_SOP(/=,_mm_div_ps)

#undef GEN_SOP

	INLINE SSEReal operator-() const {
		return _mm_sub_ps(_mm_setzero_ps(),m);
	}

	__m128 m;
};

template <int m,int n>
struct CConst<SSEReal,m,n> { static SSEReal Value() { return SSEReal(SSEFloatConst<m,n>::value); } };

INLINE SSEMask operator ==(const SSEReal &a,const SSEReal &b) { return _mm_cmpeq_ps(a.m,b.m); }
INLINE SSEMask operator !=(const SSEReal &a,const SSEReal &b) { return _mm_cmpneq_ps(a.m,b.m); }
INLINE SSEMask operator <=(const SSEReal &a,const SSEReal &b) { return _mm_cmple_ps(a.m,b.m); }
INLINE SSEMask operator >=(const SSEReal &a,const SSEReal &b) { return _mm_cmpge_ps(a.m,b.m); }
INLINE SSEMask operator < (const SSEReal &a,const SSEReal &b) { return _mm_cmplt_ps(a.m,b.m); }
INLINE SSEMask operator > (const SSEReal &a,const SSEReal &b) { return _mm_cmpgt_ps(a.m,b.m); }

INLINE SSEReal operator+(const SSEReal &a,const SSEReal &b) { SSEReal out(a); out+=b; return out; }
INLINE SSEReal operator-(const SSEReal &a,const SSEReal &b) { SSEReal out(a); out-=b; return out; }
INLINE SSEReal operator*(const SSEReal &a,const SSEReal &b) { SSEReal out(a); out*=b; return out; }
INLINE SSEReal operator/(const SSEReal &a,const SSEReal &b) { SSEReal out(a); out/=b; return out; }

INLINE SSEReal Sqrt		(const SSEReal &v) { return _mm_sqrt_ps(v.m); }
INLINE SSEReal Inv		(const SSEReal &v) { return _mm_nrrcp_ps(v.m); }
INLINE SSEReal RSqrt	(const SSEReal &v) { return _mm_nrrsqrt_ps(v.m); }
INLINE SSEReal FastInv	(const SSEReal &v) { return _mm_rcp_ps(v.m); }
INLINE SSEReal FastRSqrt(const SSEReal &v) { return _mm_rsqrt_ps(v.m); }


INLINE SSEReal Abs(const SSEReal &v)					{ return _mm_and_ps(SSEMaskConst<0x7fffffff>::value,v.m); }
INLINE SSEReal Min(const SSEReal &a,const SSEReal &b)	{ return _mm_min_ps(a.m,b.m); }
INLINE SSEReal Max(const SSEReal &a,const SSEReal &b)	{ return _mm_max_ps(a.m,b.m); }
INLINE int SignMask(const SSEReal &v)					{ return _mm_movemask_ps(v.m); }

INLINE SSEReal Condition(const SSEMask &test,const SSEReal &v1,const SSEReal &v2) {
	return _mm_or_ps(_mm_and_ps(test.m,v1.m),_mm_andnot_ps(test.m,v2.m));
}
INLINE SSEReal Condition(const SSEMaskNeg &test,const SSEReal &v1,const SSEReal &v2) {
	return _mm_or_ps(_mm_andnot_ps(test.NegM(),v1.m),_mm_and_ps(test.NegM(),v2.m));
}
INLINE SSEReal Condition(const SSEMask &test,const SSEReal &v1) {
	return _mm_and_ps(test.m,v1.m);
}
INLINE SSEReal Condition(const SSEMaskNeg &test,const SSEReal &v1) {
	return _mm_andnot_ps(test.NegM(),v1.m);
}

template <>
struct ScalarInfo<SSEReal> {
	enum { multiplicity=4, floatingPoint=1 };
	typedef SSEMask TBool;

	INLINE static SSEMask ElementMask(int n) {
		static SSEMask elems[4]={
			SSEMask(_mm_set_ps(UValue(0).f,UValue(0).f,UValue(0).f,UValue(0xffffffff).f)),
			SSEMask(_mm_set_ps(UValue(0).f,UValue(0).f,UValue(0xffffffff).f,UValue(0).f)),
			SSEMask(_mm_set_ps(UValue(0).f,UValue(0xffffffff).f,UValue(0).f,UValue(0).f)),
			SSEMask(_mm_set_ps(UValue(0xffffffff).f,UValue(0).f,UValue(0).f,UValue(0).f)),
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

