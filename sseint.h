#if !defined(VECLIB_SSEINT_H) && VECLIB_SSE_VER >= 0x20
#define VECLIB_SSEINT_H

#include "vecbase.h"

class SSEI32
{
public:
	INLINE SSEI32() { }
	INLINE SSEI32(const __m128i &v) :m(v) { }
	INLINE SSEI32(int i) :m(_mm_set1_epi32(i)) { }
	INLINE SSEI32(int a,int b,int c,int d) :m(_mm_set_epi32(a,b,c,d)) { }

	INLINE const SSEI32 &operator+=(const SSEI32 &v) { m=_mm_add_epi32(m,v.m); return *this; }
	INLINE const SSEI32 &operator-=(const SSEI32 &v) { m=_mm_sub_epi32(m,v.m); return *this; }
	INLINE const SSEI32 &operator&=(const SSEI32 &v) { m=_mm_and_si128(m,v.m); return *this; }
	INLINE const SSEI32 &operator|=(const SSEI32 &v) { m=_mm_or_si128 (m,v.m); return *this; }
	INLINE const SSEI32 &operator^=(const SSEI32 &v) { m=_mm_xor_si128(m,v.m); return *this; }

#undef GEN_SOP

	INLINE SSEI32 operator-() const { return _mm_sub_epi32(_mm_setzero_si128(),m); }
	INLINE SSEI32 operator~() const { return _mm_andnot_si128(m,_mm_set1_epi32(~0)); }
	INLINE SSEI32 operator!() const { return _mm_andnot_si128(m,_mm_set1_epi32(~0)); }
	
	__m128i m;
};

INLINE SSEI32 operator+(const SSEI32 &a,const SSEI32 &b) { SSEI32 out(a); out+=b; return a; }
INLINE SSEI32 operator-(const SSEI32 &a,const SSEI32 &b) { SSEI32 out(a); out-=b; return a; }
INLINE SSEI32 operator&(const SSEI32 &a,const SSEI32 &b) { SSEI32 out(a); out&=b; return a; }
INLINE SSEI32 operator|(const SSEI32 &a,const SSEI32 &b) { SSEI32 out(a); out|=b; return a; }
INLINE SSEI32 operator^(const SSEI32 &a,const SSEI32 &b) { SSEI32 out(a); out^=b; return a; }

template <int bits>
INLINE SSEI32 Shl(const SSEI32 &in) { SSEI32 out(_mm_slli_epi32(in.m,bits)); return out; }
template <int bits>
INLINE SSEI32 Shr(const SSEI32 &in) { SSEI32 out(_mm_srli_epi32(in.m,bits)); return out; }
INLINE SSEI32 Shl(const SSEI32 &in,const SSEI32 &bits) { SSEI32 out(_mm_sll_epi32(in.m,bits.m)); return out; }
INLINE SSEI32 Shr(const SSEI32 &in,const SSEI32 &bits) { SSEI32 out(_mm_srl_epi32(in.m,bits.m)); return out; }

INLINE SSEI32 operator||(const SSEI32 &a,const SSEI32 &b) { return a|b; }
INLINE SSEI32 operator&&(const SSEI32 &a,const SSEI32 &b) { return a&b; }
INLINE SSEI32 AndNot(const SSEI32 &a,const SSEI32 &b) { return _mm_andnot_si128(a.m,b.m); }

INLINE SSEI32 operator!=(const SSEI32 &a,const SSEI32 &b) { SSEI32 out(_mm_andnot_si128(_mm_cmpeq_epi32(a.m,b.m),_mm_set1_epi32(~0))); return out; }
INLINE SSEI32 operator==(const SSEI32 &a,const SSEI32 &b) { SSEI32 out(_mm_cmpeq_epi32(a.m,b.m)); return out; }
INLINE SSEI32 operator< (const SSEI32 &a,const SSEI32 &b) { SSEI32 out(_mm_cmplt_epi32(a.m,b.m)); return out; }
INLINE SSEI32 operator> (const SSEI32 &a,const SSEI32 &b) { SSEI32 out(_mm_cmpgt_epi32(a.m,b.m)); return out; }
INLINE SSEI32 operator<=(const SSEI32 &a,const SSEI32 &b) { SSEI32 out(_mm_or_si128((a<b).m,(a==b).m)); return out; }
INLINE SSEI32 operator>=(const SSEI32 &a,const SSEI32 &b) { SSEI32 out(_mm_or_si128((a>b).m,(a==b).m)); return out; }

INLINE SSEI32 Condition(const SSEI32 &test,const SSEI32 &v1,const SSEI32 &v2) {
    return _mm_or_si128(_mm_and_si128(test.m,v1.m),_mm_andnot_si128(test.m,v2.m));
}
INLINE SSEI32 Condition(const SSEI32 &test,const SSEI32 &v1) {
    return _mm_and_si128(test.m,v1.m);
}

INLINE bool ForAny(const SSEI32 &test) {
	return _mm_movemask_epi8(test.m)?1:0;
}
INLINE bool ForAll(const SSEI32 &test) {
	return _mm_movemask_epi8(test.m)==0xffff?1:0;
}
INLINE int ForWhich(const SSEI32 &test) {
	int mask=_mm_movemask_epi8(test.m);
	return ((mask&0x000f)?1:0)|((mask&0x00f0)?2:0)|((mask&0x0f00)?4:0)|((mask&0xf000)?8:0);
}

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

template<>
struct ScalarInfo<SSEI32> {
	enum { multiplicity=4, floatingPoint=0 };
	typedef SSEI32 TBool;

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


#endif

