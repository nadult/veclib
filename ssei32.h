#if !defined(VECLIB_SSEINT_H) && VECLIB_SSE_VER >= 0x20
#define VECLIB_SSEINT_H

#include "vecbase.h"
#include "ssef32.h"

class i32x4b;
class i32x4bn;

class i32x4
{
public:
	INLINE i32x4() { }
	INLINE i32x4(const __m128i &v) :m(v) { }
	INLINE i32x4(const i32x4 &rhs) :m(rhs.m) { }
	INLINE explicit i32x4(int i) :m(_mm_set1_epi32(i)) { }
	INLINE i32x4(int a,int b,int c,int d) :m(_mm_set_epi32(a,b,c,d)) { }
	INLINE explicit i32x4(const i32x4b&);

	INLINE const i32x4 &operator=(const i32x4 &rhs) { m=rhs.m; return *this; }

	INLINE explicit i32x4(const f32x4 &v) :m(_mm_cvttps_epi32(v.m)) { }
	INLINE operator f32x4() const { return _mm_cvtepi32_ps(m); }

	INLINE const i32x4 &operator+=(const i32x4 &v) { m=_mm_add_epi32(m,v.m); return *this; }
	INLINE const i32x4 &operator-=(const i32x4 &v) { m=_mm_sub_epi32(m,v.m); return *this; }
	INLINE const i32x4 &operator&=(const i32x4 &v) { m=_mm_and_si128(m,v.m); return *this; }
	INLINE const i32x4 &operator|=(const i32x4 &v) { m=_mm_or_si128 (m,v.m); return *this; }
	INLINE const i32x4 &operator^=(const i32x4 &v) { m=_mm_xor_si128(m,v.m); return *this; }
	INLINE const i32x4 &operator<<=(const i32x4 &v) {
		i[0]<<=v.i[0]; i[1]<<=v.i[1]; i[2]<<=v.i[2]; i[3]<<=v.i[3];
	//	m=_mm_sll_epi32(m,v.m);
		return *this;
	}
	INLINE const i32x4 &operator>>=(const i32x4 &v) {
		i[0]>>=v.i[0]; i[1]>>=v.i[1]; i[2]>>=v.i[2]; i[3]>>=v.i[3];
	//	m=_mm_sra_epi32(m,v.m);
		return *this;
	}
	INLINE const i32x4 &operator<<=(int i) { m=_mm_sll_epi32(m,i32x4(i).m); return *this; }
	INLINE const i32x4 &operator>>=(int i) { m=_mm_srl_epi32(m,i32x4(i).m); return *this; }

	INLINE const i32x4 &operator*=(const i32x4 &v) {
		i[0]*=v.i[0]; i[1]*=v.i[1]; i[2]*=v.i[2]; i[3]*=v.i[3];
	
	// Not working too good for too big values
	//	__m128d a0=_mm_cvtepi32_pd(m),b0=_mm_cvtepi32_pd(v.m);
	//	__m128d a1=_mm_cvtepi32_pd(_mm_shuffle_epi32(m,2*1+3*4)),b1=_mm_cvtepi32_pd(_mm_shuffle_epi32(v.m,2*1+3*4));
	//	a0=_mm_mul_pd(a0,b0); a1=_mm_mul_pd(a1,b1);
	//	m=_mm_castps_si128(		_mm_shuffle_ps(	_mm_castsi128_ps(_mm_cvttpd_epi32(a0)),
	//											_mm_castsi128_ps(_mm_cvttpd_epi32(a1)),0+1*4+0*16+1*64));
		return *this;
	}
	INLINE const i32x4 &operator/=(const i32x4 &v) {
		__m128d a0=_mm_cvtepi32_pd(m),b0=_mm_cvtepi32_pd(v.m);
		__m128d a1=_mm_cvtepi32_pd(_mm_shuffle_epi32(m,2*1+3*4)),b1=_mm_cvtepi32_pd(_mm_shuffle_epi32(v.m,2*1+3*4));
		a0=_mm_div_pd(a0,b0); a1=_mm_div_pd(a1,b1);
		m=_mm_castps_si128(		_mm_shuffle_ps(	_mm_castsi128_ps(_mm_cvttpd_epi32(a0)),
												_mm_castsi128_ps(_mm_cvttpd_epi32(a1)),0+1*4+0*16+1*64));

		return *this;
	}
	INLINE const i32x4 &operator%=(const i32x4 &v) {
		i[0]%=v.i[0]; i[1]%=v.i[1]; i[2]%=v.i[2]; i[3]%=v.i[3];
	// TODO: repair this
	/*	__m128d a0=_mm_cvtepi32_pd(m),b0=_mm_cvtepi32_pd(v.m);
		__m128d a1=_mm_cvtepi32_pd(_mm_shuffle_epi32(m,2*1+3*4)),b1=_mm_cvtepi32_pd(_mm_shuffle_epi32(v.m,2*1+3*4));
		a0=_mm_div_pd(a0,b0); a1=_mm_div_pd(a1,b1);

		a0=_mm_cvtepi32_pd(_mm_cvttpd_epi32(a0));
		a1=_mm_cvtepi32_pd(_mm_cvttpd_epi32(a1));

		a0=_mm_mul_pd(a0,b0); a1=_mm_mul_pd(a1,b1);

		m=_mm_sub_epi32(m,	_mm_castps_si128(	_mm_shuffle_ps(	_mm_castsi128_ps(_mm_cvttpd_epi32(a0)),
																_mm_castsi128_ps(_mm_cvttpd_epi32(a1)),0+1*4+0*16+1*64))); */
	}

	INLINE const i32x4 &operator++() { m=_mm_add_epi32(m,SSEI32Const<1>::value); return *this; }
	INLINE const i32x4 &operator--() { m=_mm_add_epi32(m,SSEI32Const<1>::value); return *this; }

	INLINE i32x4 operator-() const { return _mm_sub_epi32(_mm_setzero_si128(),m); }
	INLINE i32x4 operator~() const { return _mm_andnot_si128(m,_mm_set1_epi32(~0)); }

	INLINE i32x4b operator!() const;
	INLINE operator i32x4bn() const;

	INLINE operator i32*() { return i; }
	INLINE operator const i32*() const { return i; }

	union {
		__m128i m;
		i32 i[4];
		u32 u[4];
	};
};

INLINE i32x4 operator+(const i32x4 &a,const i32x4 &b)	{ i32x4 out(a); out+=b; return out; }
INLINE i32x4 operator-(const i32x4 &a,const i32x4 &b)	{ i32x4 out(a); out-=b; return out; }
INLINE i32x4 operator*(const i32x4 &a,const i32x4 &b)	{ i32x4 out(a); out*=b; return out; }
INLINE i32x4 operator/(const i32x4 &a,const i32x4 &b)	{ i32x4 out(a); out/=b; return out; }
INLINE i32x4 operator%(const i32x4 &a,const i32x4 &b)	{ i32x4 out(a); out%=b; return out; }
INLINE i32x4 operator&(const i32x4 &a,const i32x4 &b)	{ i32x4 out(a); out&=b; return out; }
INLINE i32x4 operator|(const i32x4 &a,const i32x4 &b)	{ i32x4 out(a); out|=b; return out; }
INLINE i32x4 operator^(const i32x4 &a,const i32x4 &b)	{ i32x4 out(a); out^=b; return out; }
INLINE i32x4 operator<<(const i32x4 &a,const i32x4 &b)	{ i32x4 out(a); out<<=b; return out; }
INLINE i32x4 operator>>(const i32x4 &a,const i32x4 &b)	{ i32x4 out(a); out>>=b; return out; }

template <uint bits> INLINE i32x4 Shl(const i32x4 &in)	{ i32x4 out(_mm_slli_epi32(in.m,bits)); return out; }
template <uint bits> INLINE i32x4 Shr(const i32x4 &in)	{ i32x4 out(_mm_srli_epi32(in.m,bits)); return out; }

// Correct up to 23 bits; UAYOR
INLINE i32x4 FastMul(const i32x4 &ta,const i32x4 &tb) {
	i32x4 out;
	__m128 a=_mm_cvtepi32_ps(ta.m),b=_mm_cvtepi32_ps(tb.m);
	out.m=_mm_cvttps_epi32(_mm_mul_ps(a,b));
	return out;
}
// Correct up to 23 bits; UAYOR
INLINE i32x4 FastDiv(const i32x4 &ta,const i32x4 &tb) {
	i32x4 out;
	__m128 a=_mm_cvtepi32_ps(ta.m),b=_mm_cvtepi32_ps(tb.m);
	out.m=_mm_cvttps_epi32(_mm_div_ps(a,b));
	return out;
}

INLINE i32x4 Abs(const i32x4 &in) {
	i32x4 out;
#if VECLIB_SSE_VER>=0x31
	out.m=_mm_abs_epi32(in.m);
#else
	out.m=_mm_srai_epi32(in.m,31);
	out.m=_mm_sub_epi32(_mm_xor_si128(in.m,out.m),out.m);
#endif
	return out;
}


class i32x4b
{
public:
	INLINE i32x4b() { }
	INLINE i32x4b(const __m128i &v) :m(v) { }

	INLINE i32x4b operator^(const i32x4b &v) const	{ return _mm_xor_si128(m,v.m); }
	INLINE i32x4b operator&&(const i32x4b &v) const	{ return _mm_and_si128(m,v.m); }
	INLINE i32x4b operator||(const i32x4b &v) const	{ return _mm_or_si128(m,v.m); }

	INLINE i32x4b(const f32x4b &v)					:m(_mm_castps_si128(v.m)) { }
	INLINE operator f32x4b() const					{ return _mm_castsi128_ps(m); }

	__m128i m;
};

i32x4::i32x4(const i32x4b &v) :m(v.m) { }

template <bool v>
struct CBConst<i32x4b,v> { static i32x4b Value() { return i32x4b(SSEI32Const<v?0xffffffff:0>::value); } };

class i32x4bn
{
public:
	INLINE i32x4bn operator^(const i32x4b &v) const		{ return _mm_xor_si128(m,v.m); }
	INLINE i32x4b operator^(const i32x4bn &v) const		{ return _mm_xor_si128(m,v.m); }
	INLINE i32x4b operator!() const						{ return i32x4b(m); }

	INLINE i32x4b operator&&(const i32x4b &v) const		{ return _mm_andnot_si128(m,v.m); }
	INLINE i32x4bn operator&&(const i32x4bn &v) const	{ return _mm_or_si128(m,v.m); }

	INLINE i32x4bn operator||(const i32x4bn &v) const	{ return _mm_and_si128(m,v.m); }
	INLINE i32x4b operator||(const i32x4b &v) const		{ return _mm_or_si128(_mm_andnot_si128(m,SSEI32Const<0xffffffff>::value),v.m); }
	INLINE operator i32x4b() const						{ return _mm_andnot_si128(m,SSEI32Const<0xffffffff>::value); }

//	INLINE i32x4bn(const f32x4bn &v)					:m(_mm_castps_si128(v.NegM())) { }
//	INLINE operator f32x4bn() const						{ return _mm_castsi128_ps(m); }

	INLINE const __m128i &NegM() const { return m; }
private:
	INLINE i32x4bn(const __m128i &v) :m(v) { }
	friend i32x4bn operator!(const i32x4b&);
	friend i32x4bn operator^(const i32x4b&,const i32x4bn&);
	friend i32x4bn operator!=(const i32x4&,const i32x4&);
	friend i32x4bn operator<=(const i32x4&,const i32x4&);
	friend i32x4bn operator>=(const i32x4&,const i32x4&);
	friend i32x4::operator i32x4bn() const;

	// To access it you have to
	// convert to i32x4b first
	__m128i m;
};

i32x4::operator i32x4bn() const { return i32x4bn(_mm_cmpeq_epi32(m,_mm_setzero_si128())); }
i32x4b i32x4::operator!() const { return i32x4b(_mm_cmpeq_epi32(m,_mm_setzero_si128())); }

INLINE i32x4bn operator!(const i32x4b &v)						{ return i32x4bn(v.m); }
INLINE i32x4bn operator^(const i32x4b &a,const i32x4bn &b)		{ return i32x4bn(_mm_xor_si128(a.m,b.NegM())); }
INLINE i32x4b operator&&(const i32x4b &a,const i32x4bn &b)		{ return _mm_andnot_si128(b.NegM(),a.m); }
INLINE i32x4b operator||(const i32x4b &a,const i32x4bn &b)
	{ return _mm_or_si128(a.m,_mm_andnot_si128(b.NegM(),SSEI32Const<0xffffffff>::value)); }

INLINE bool ForAny(const i32x4b &test) { return _mm_movemask_epi8(test.m)?1:0; }
INLINE bool ForAll(const i32x4b &test) { return _mm_movemask_epi8(test.m)==0xffff?1:0; }
INLINE int ForWhich(const i32x4b &test) {
	int mask=_mm_movemask_epi8(test.m);
	return ((mask&0x000f)?1:0)|((mask&0x00f0)?2:0)|((mask&0x0f00)?4:0)|((mask&0xf000)?8:0);
}
INLINE i32x4bn	operator!=(const i32x4 &a,const i32x4 &b) { return _mm_cmpeq_epi32(a.m,b.m); }
INLINE i32x4b 	operator==(const i32x4 &a,const i32x4 &b) { return _mm_cmpeq_epi32(a.m,b.m); }
INLINE i32x4b	operator< (const i32x4 &a,const i32x4 &b) { return _mm_cmplt_epi32(a.m,b.m); }
INLINE i32x4b	operator> (const i32x4 &a,const i32x4 &b) { return _mm_cmpgt_epi32(a.m,b.m); }
INLINE i32x4bn	operator<=(const i32x4 &a,const i32x4 &b) { return _mm_cmpgt_epi32(a.m,b.m); }
INLINE i32x4bn	operator>=(const i32x4 &a,const i32x4 &b) { return _mm_cmplt_epi32(a.m,b.m); }

INLINE i32x4 Condition(const i32x4b &test,const i32x4 &v1,const i32x4 &v2)
	{ return _mm_or_si128(_mm_and_si128(test.m,v1.m),_mm_andnot_si128(test.m,v2.m)); }
INLINE i32x4 Condition(const i32x4b &test,const i32x4 &v1)
	{ return _mm_and_si128(test.m,v1.m); }
INLINE i32x4 Condition(const i32x4bn &test,const i32x4 &v1,const i32x4 &v2)
	{ return _mm_or_si128(_mm_andnot_si128(test.NegM(),v1.m),_mm_and_si128(test.NegM(),v2.m)); }
INLINE i32x4 Condition(const i32x4bn &test,const i32x4 &v1)
	{ return _mm_andnot_si128(test.NegM(),v1.m); }

INLINE i32x4 Max(const i32x4 &a,const i32x4 &b) {
	i32x4 out(_mm_cmpgt_epi32(a.m,b.m));
	out.m=_mm_or_si128(_mm_andnot_si128(out.m,b.m),_mm_and_si128(out.m,a.m));
	return out;
}
INLINE i32x4 Min(const i32x4 &a,const i32x4 &b) {
	i32x4 out(_mm_cmpgt_epi32(a.m,b.m));
	out.m=_mm_or_si128(_mm_and_si128(out.m,b.m),_mm_andnot_si128(out.m,a.m));
	return out;
}
template<>
struct ScalarInfo<i32x4> {
	enum { multiplicity=4, floatingPoint=0 };
	typedef i32x4b TBool;

	INLINE static i32x4 ElementMask(int n) {
		static __m128i elems[4]={_mm_set_epi32(0,0,0,~0),_mm_set_epi32(0,0,~0,0),_mm_set_epi32(0,~0,0,0),_mm_set_epi32(~0,0,0,0)};
		return i32x4(elems[n]);
    }
};

INLINE void Broadcast(const int &in,i32x4 &out) { out=_mm_set1_epi32(in); }
INLINE void Convert(const int in[4],i32x4 &out) { out=_mm_loadu_si128((__m128i*)in); }
INLINE void Convert(const i32x4 &in,int out[4]) { _mm_storeu_si128((__m128i*)out,in.m); }

INLINE void Convert(int inX,int inY,int inZ,int inW,i32x4 &out) {
    out=_mm_set_epi32(inW,inZ,inY,inX);
}
INLINE void Convert(const i32x4 &in,int &outX,int &outY,int &outZ,int &outW) {
	outX=in[0]; outY=in[1]; outZ=in[2]; outW=in[3];
}

INLINE i32x4 Round(const f32x4 &flt) 				{ return _mm_cvtps_epi32(flt.m); }
INLINE i32x4 Trunc(const f32x4 &flt)				{ return _mm_cvttps_epi32(flt.m); }

INLINE void Cast(const i32x4 &src	,f32x4 &dst)	{ dst.m=_mm_castsi128_ps(src.m); }
INLINE void Cast(const f32x4 &src	,i32x4 &dst)	{ dst.m=_mm_castps_si128(src.m); }

// Auto conversion
//INLINE void Cast(const i32x4b &src	,f32x4b &dst)	{ dst.m=_mm_castsi128_ps(src.m); }
//INLINE void Cast(const f32x4b &src	,i32x4b &dst)	{ dst.m=_mm_castps_si128(src.m); }

#endif

