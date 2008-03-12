#if !defined(VECLIB_SSEINT_H) && VECLIB_SSE_VER >= 0x20
#define VECLIB_SSEINT_H

#include "vecbase.h"
#include "ssereal.h"

class SSEI32Mask;
class SSEI32MaskNeg;

class SSEI32
{
public:
	INLINE SSEI32() { }
	INLINE SSEI32(const __m128i &v) :m(v) { }
	INLINE explicit SSEI32(int i) :m(_mm_set1_epi32(i)) { }
	INLINE SSEI32(int a,int b,int c,int d) :m(_mm_set_epi32(a,b,c,d)) { }
	INLINE explicit SSEI32(const SSEI32Mask&);

	INLINE const SSEI32 &operator+=(const SSEI32 &v) { m=_mm_add_epi32(m,v.m); return *this; }
	INLINE const SSEI32 &operator-=(const SSEI32 &v) { m=_mm_sub_epi32(m,v.m); return *this; }
	INLINE const SSEI32 &operator&=(const SSEI32 &v) { m=_mm_and_si128(m,v.m); return *this; }
	INLINE const SSEI32 &operator|=(const SSEI32 &v) { m=_mm_or_si128 (m,v.m); return *this; }
	INLINE const SSEI32 &operator^=(const SSEI32 &v) { m=_mm_xor_si128(m,v.m); return *this; }
	INLINE const SSEI32 &operator<<=(const SSEI32 &v) {
		i32 *a=(i32*)&m,*b=(i32*)&v.m;
		a[0]<<=b[0]; a[1]<<=b[1]; a[2]<<=b[2]; a[3]<<=b[3];
	//	m=_mm_sll_epi32(m,v.m);
		return *this;
	}
	INLINE const SSEI32 &operator>>=(const SSEI32 &v) {
		i32 *a=(i32*)&m,*b=(i32*)&v.m;
		a[0]>>=b[0]; a[1]>>=b[1]; a[2]>>=b[2]; a[3]>>=b[3];
	//	m=_mm_sra_epi32(m,v.m);
		return *this;
	}
	INLINE const SSEI32 &operator<<=(int i) { m=_mm_sra_epi32(m,SSEI32(-i).m); return *this; }
	INLINE const SSEI32 &operator>>=(int i) { m=_mm_sra_epi32(m,SSEI32(i).m); return *this; }

	INLINE const SSEI32 &operator*=(const SSEI32 &v) {
		i32 *a=(i32*)&m,*b=(i32*)&v.m;
		a[0]*=b[0]; a[1]*=b[1]; a[2]*=b[2]; a[3]*=b[3];
		
	//	__m128d a0=_mm_cvtepi32_pd(m),b0=_mm_cvtepi32_pd(v.m);
	//	__m128d a1=_mm_cvtepi32_pd(_mm_shuffle_epi32(m,2*1+3*4)),b1=_mm_cvtepi32_pd(_mm_shuffle_epi32(v.m,2*1+3*4));
	//	a0=_mm_mul_pd(a0,b0); a1=_mm_mul_pd(a1,b1);
	//	m=_mm_castps_si128(		_mm_shuffle_ps(	_mm_castsi128_ps(_mm_cvttpd_epi32(a0)),
	//											_mm_castsi128_ps(_mm_cvttpd_epi32(a1)),0+1*4+0*16+1*64));
		return *this;
	}
	INLINE const SSEI32 &operator/=(const SSEI32 &v) {
		__m128d a0=_mm_cvtepi32_pd(m),b0=_mm_cvtepi32_pd(v.m);
		__m128d a1=_mm_cvtepi32_pd(_mm_shuffle_epi32(m,2*1+3*4)),b1=_mm_cvtepi32_pd(_mm_shuffle_epi32(v.m,2*1+3*4));
		a0=_mm_div_pd(a0,b0); a1=_mm_div_pd(a1,b1);
		m=_mm_castps_si128(		_mm_shuffle_ps(	_mm_castsi128_ps(_mm_cvttpd_epi32(a0)),
												_mm_castsi128_ps(_mm_cvttpd_epi32(a1)),0+1*4+0*16+1*64));

		return *this;
	}
	INLINE const SSEI32 &operator%=(const SSEI32 &v) {
		__m128d a0=_mm_cvtepi32_pd(m),b0=_mm_cvtepi32_pd(v.m);
		__m128d a1=_mm_cvtepi32_pd(_mm_shuffle_epi32(m,2*1+3*4)),b1=_mm_cvtepi32_pd(_mm_shuffle_epi32(v.m,2*1+3*4));
		a0=_mm_div_pd(a0,b0); a1=_mm_div_pd(a1,b1);

		a0=_mm_cvtepi32_pd(_mm_cvttpd_epi32(a0));
		a1=_mm_cvtepi32_pd(_mm_cvttpd_epi32(a1));

		a0=_mm_mul_pd(a0,b0); a1=_mm_mul_pd(a1,b1);

		m=_mm_sub_epi32(m,	_mm_castps_si128(	_mm_shuffle_ps(	_mm_castsi128_ps(_mm_cvttpd_epi32(a0)),
																_mm_castsi128_ps(_mm_cvttpd_epi32(a1)),0+1*4+0*16+1*64)));

	}

	INLINE SSEI32 operator-() const { return _mm_sub_epi32(_mm_setzero_si128(),m); }
	INLINE SSEI32 operator~() const { return _mm_andnot_si128(m,_mm_set1_epi32(~0)); }

	INLINE SSEI32Mask operator!() const;
	INLINE operator SSEI32MaskNeg() const;
	
	__m128i m;
};

INLINE SSEI32 operator+(const SSEI32 &a,const SSEI32 &b) { SSEI32 out(a); out+=b; return out; }
INLINE SSEI32 operator-(const SSEI32 &a,const SSEI32 &b) { SSEI32 out(a); out-=b; return out; }
INLINE SSEI32 operator*(const SSEI32 &a,const SSEI32 &b) { SSEI32 out(a); out*=b; return out; }
INLINE SSEI32 operator/(const SSEI32 &a,const SSEI32 &b) { SSEI32 out(a); out/=b; return out; }
INLINE SSEI32 operator%(const SSEI32 &a,const SSEI32 &b) { SSEI32 out(a); out%=b; return out; }
INLINE SSEI32 operator&(const SSEI32 &a,const SSEI32 &b) { SSEI32 out(a); out&=b; return out; }
INLINE SSEI32 operator|(const SSEI32 &a,const SSEI32 &b) { SSEI32 out(a); out|=b; return out; }
INLINE SSEI32 operator^(const SSEI32 &a,const SSEI32 &b) { SSEI32 out(a); out^=b; return out; }
INLINE SSEI32 operator<<(const SSEI32 &a,const SSEI32 &b) { SSEI32 out(a); out<<=b; return out; }
INLINE SSEI32 operator>>(const SSEI32 &a,const SSEI32 &b) { SSEI32 out(a); out>>=b; return out; }

template <uint bits> INLINE SSEI32 Shl(const SSEI32 &in) { SSEI32 out(_mm_slli_epi32(in.m,bits)); return out; }
template <uint bits> INLINE SSEI32 Shr(const SSEI32 &in) { SSEI32 out(_mm_srli_epi32(in.m,bits)); return out; }

// Correct up to 23 bits; UAYOR
INLINE SSEI32 FastMul(const SSEI32 &ta,const SSEI32 &tb) {
	SSEI32 out;
	__m128 a=_mm_cvtepi32_ps(ta.m),b=_mm_cvtepi32_ps(tb.m);
	out.m=_mm_cvttps_epi32(_mm_mul_ps(a,b));
	return out;
}
// Correct up to 23 bits; UAYOR
INLINE SSEI32 FastDiv(const SSEI32 &ta,const SSEI32 &tb) {
	SSEI32 out;
	__m128 a=_mm_cvtepi32_ps(ta.m),b=_mm_cvtepi32_ps(tb.m);
	out.m=_mm_cvttps_epi32(_mm_div_ps(a,b));
	return out;
}

INLINE SSEI32 Abs(const SSEI32 &in) {
	SSEI32 out;
#if VECLIB_SSE_VER>=0x31
	out.m=_mm_abs_epi32(in.m);
#else
	out.m=_mm_srai_epi32(in.m,31);
	out.m=_mm_sub_epi32(_mm_xor_si128(in.m,out.m),out.m);
#endif
	return out;
}


class SSEI32Mask
{
public:
	INLINE SSEI32Mask() { }
	INLINE SSEI32Mask(const __m128i &v) :m(v) { }

	INLINE SSEI32Mask operator^(const SSEI32Mask &v) const	{ return _mm_xor_si128(m,v.m); }
	INLINE SSEI32Mask operator&&(const SSEI32Mask &v) const	{ return _mm_and_si128(m,v.m); }
	INLINE SSEI32Mask operator||(const SSEI32Mask &v) const	{ return _mm_or_si128(m,v.m); }

	__m128i m;
};

SSEI32::SSEI32(const SSEI32Mask &v) :m(v.m) { }

template <bool v>
struct CBConst<SSEI32Mask,v> { static SSEI32Mask Value() { return SSEI32Mask(SSEI32Const<v?0xffffffff:0>::value); } };

class SSEI32MaskNeg
{
public:
	INLINE SSEI32MaskNeg operator^(const SSEI32Mask &v) const		{ return _mm_xor_si128(m,v.m); }
	INLINE SSEI32Mask operator^(const SSEI32MaskNeg &v) const		{ return _mm_xor_si128(m,v.m); }
	INLINE SSEI32Mask operator!() const								{ return SSEI32Mask(m); }

	INLINE SSEI32Mask operator&&(const SSEI32Mask &v) const			{ return _mm_andnot_si128(m,v.m); }
	INLINE SSEI32MaskNeg operator&&(const SSEI32MaskNeg &v) const	{ return _mm_or_si128(m,v.m); }

	INLINE SSEI32MaskNeg operator||(const SSEI32MaskNeg &v) const	{ return _mm_and_si128(m,v.m); }
	INLINE SSEI32Mask operator||(const SSEI32Mask &v) const			{ return _mm_or_si128(_mm_andnot_si128(m,SSEI32Const<0xffffffff>::value),v.m); }
	operator SSEI32Mask() const										{ return _mm_andnot_si128(m,SSEI32Const<0xffffffff>::value); }

	const __m128i &NegM() const { return m; }
private:
	INLINE SSEI32MaskNeg(const __m128i &v) :m(v) { }
	friend SSEI32MaskNeg operator!(const SSEI32Mask&);
	friend SSEI32MaskNeg operator^(const SSEI32Mask&,const SSEI32MaskNeg&);
	friend SSEI32MaskNeg operator!=(const SSEI32&,const SSEI32&);
	friend SSEI32MaskNeg operator<=(const SSEI32&,const SSEI32&);
	friend SSEI32MaskNeg operator>=(const SSEI32&,const SSEI32&);
	friend SSEI32::operator SSEI32MaskNeg() const;

	// To access it you have to
	// convert to SSEI32Mask first
	__m128i m;
};

SSEI32::operator SSEI32MaskNeg() const { return SSEI32MaskNeg(_mm_cmpeq_epi32(m,_mm_setzero_si128())); }
SSEI32Mask SSEI32::operator!() const { return SSEI32Mask(_mm_cmpeq_epi32(m,_mm_setzero_si128())); }

INLINE SSEI32MaskNeg operator!(const SSEI32Mask &v)								{ return SSEI32MaskNeg(v.m); }
INLINE SSEI32MaskNeg operator^(const SSEI32Mask &a,const SSEI32MaskNeg &b)		{ return SSEI32MaskNeg(_mm_xor_si128(a.m,b.NegM())); }
INLINE SSEI32Mask operator&&(const SSEI32Mask &a,const SSEI32MaskNeg &b)		{ return _mm_andnot_si128(b.NegM(),a.m); }
INLINE SSEI32Mask operator||(const SSEI32Mask &a,const SSEI32MaskNeg &b)
	{ return _mm_or_si128(a.m,_mm_andnot_si128(b.NegM(),SSEI32Const<0xffffffff>::value)); }

INLINE bool ForAny(const SSEI32Mask &test) { return _mm_movemask_epi8(test.m)?1:0; }
INLINE bool ForAll(const SSEI32Mask &test) { return _mm_movemask_epi8(test.m)==0xffff?1:0; }
INLINE int ForWhich(const SSEI32Mask &test) {
	int mask=_mm_movemask_epi8(test.m);
	return ((mask&0x000f)?1:0)|((mask&0x00f0)?2:0)|((mask&0x0f00)?4:0)|((mask&0xf000)?8:0);
}
INLINE SSEI32MaskNeg	operator!=(const SSEI32 &a,const SSEI32 &b) { return _mm_cmpeq_epi32(a.m,b.m); }
INLINE SSEI32Mask 		operator==(const SSEI32 &a,const SSEI32 &b) { return _mm_cmpeq_epi32(a.m,b.m); }
INLINE SSEI32Mask		operator< (const SSEI32 &a,const SSEI32 &b) { return _mm_cmplt_epi32(a.m,b.m); }
INLINE SSEI32Mask		operator> (const SSEI32 &a,const SSEI32 &b) { return _mm_cmpgt_epi32(a.m,b.m); }
INLINE SSEI32MaskNeg	operator<=(const SSEI32 &a,const SSEI32 &b) { return _mm_cmpgt_epi32(a.m,b.m); }
INLINE SSEI32MaskNeg	operator>=(const SSEI32 &a,const SSEI32 &b) { return _mm_cmplt_epi32(a.m,b.m); }

INLINE SSEI32 Condition(const SSEI32Mask &test,const SSEI32 &v1,const SSEI32 &v2)
	{ return _mm_or_si128(_mm_and_si128(test.m,v1.m),_mm_andnot_si128(test.m,v2.m)); }
INLINE SSEI32 Condition(const SSEI32Mask &test,const SSEI32 &v1)
	{ return _mm_and_si128(test.m,v1.m); }
INLINE SSEI32 Condition(const SSEI32MaskNeg &test,const SSEI32 &v1,const SSEI32 &v2)
	{ return _mm_or_si128(_mm_andnot_si128(test.NegM(),v1.m),_mm_and_si128(test.NegM(),v2.m)); }
INLINE SSEI32 Condition(const SSEI32MaskNeg &test,const SSEI32 &v1)
	{ return _mm_andnot_si128(test.NegM(),v1.m); }

INLINE SSEI32 Max(const SSEI32 &a,const SSEI32 &b) {
	SSEI32 out(_mm_cmpgt_epi32(a.m,b.m));
	out.m=_mm_or_si128(_mm_andnot_si128(out.m,b.m),_mm_and_si128(out.m,a.m));
	return out;
}
INLINE SSEI32 Min(const SSEI32 &a,const SSEI32 &b) {
	SSEI32 out(_mm_cmpgt_epi32(a.m,b.m));
	out.m=_mm_or_si128(_mm_and_si128(out.m,b.m),_mm_andnot_si128(out.m,a.m));
	return out;
}
template<>
struct ScalarInfo<SSEI32> {
	enum { multiplicity=4, floatingPoint=0 };
	typedef SSEI32Mask TBool;

	INLINE static SSEI32 ElementMask(int n) {
		static __m128i elems[4]={_mm_set_epi32(0,0,0,~0),_mm_set_epi32(0,0,~0,0),_mm_set_epi32(0,~0,0,0),_mm_set_epi32(~0,0,0,0)};
		return SSEI32(elems[n]);
    }
};

INLINE void Broadcast(const int &in,SSEI32 &out) { out=_mm_set1_epi32(in); }
INLINE void Convert(const int in[4],SSEI32 &out) { out=_mm_loadu_si128((__m128i*)in); }
INLINE void Convert(const SSEI32 &in,int out[4]) { _mm_storeu_si128((__m128i*)out,in.m); }

INLINE void Convert(int inX,int inY,int inZ,int inW,SSEI32 &out) {
    out=_mm_set_epi32(inW,inZ,inY,inX);
}
INLINE void Convert(const SSEI32 &in,int &outX,int &outY,int &outZ,int &outW) {
	int *p=(int*)&in;
	outX=p[0]; outY=p[1]; outZ=p[2]; outW=p[3];
}

INLINE void Cast(const SSEI32 &src		,SSEReal &dst)		{ dst.m=_mm_castsi128_ps(src.m); }
INLINE void Cast(const SSEI32Mask &src	,SSERealMask &dst)	{ dst.m=_mm_castsi128_ps(src.m); }
INLINE void Cast(const SSEReal &src		,SSEI32 &dst)		{ dst.m=_mm_castps_si128(src.m); }
INLINE void Cast(const SSERealMask &src	,SSEI32Mask &dst)	{ dst.m=_mm_castps_si128(src.m); }

#endif

