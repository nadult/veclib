#ifndef VECLIB_SSE_I32_H
#define VECLIB_SSE_I32_H

#include "vecbase.h"
#include "sse/f32.h"

class i32x4b;
class i32x4bn;

class i32x4
{
public:
	i32x4() { }
	i32x4(__m128i m) :m(m) { }
	i32x4(const i32x4 &rhs) :m(rhs.m) { }
	i32x4(int i) :m(_mm_set1_epi32(i)) { }
	i32x4(unsigned i) :m(_mm_set1_epi32(i)) { }
	i32x4(int a, int b, int c, int d) :m(_mm_set_epi32(d,c,b,a)) { }
	explicit i32x4(i32x4b);

	const i32x4 operator=(const i32x4 &rhs) { m=rhs.m; return *this; }

	explicit i32x4(const f32x4 &v) :m(_mm_cvttps_epi32(v.m)) { }
	operator f32x4() const { return _mm_cvtepi32_ps(m); }

	const i32x4 operator+=(i32x4 v) { m=_mm_add_epi32(m,v.m); return *this; }
	const i32x4 operator-=(i32x4 v) { m=_mm_sub_epi32(m,v.m); return *this; }
	const i32x4 operator&=(i32x4 v) { m=_mm_and_si128(m,v.m); return *this; }
	const i32x4 operator|=(i32x4 v) { m=_mm_or_si128 (m,v.m); return *this; }
	const i32x4 operator^=(i32x4 v) { m=_mm_xor_si128(m,v.m); return *this; }
	const i32x4 operator<<=(i32x4 v) { m = _mm_sll_epi32(m, v.m); return *this; } //TODO test me please
	const i32x4 operator>>=(i32x4 v) { m = _mm_sra_epi32(m, v.m); return *this; } //TODO test me please
	const i32x4 operator<<=(int i) { m = _mm_slli_epi32(m, i); return *this; }
	const i32x4 operator>>=(int i) { m = _mm_srai_epi32(m, i); return *this; }

	// FFS gcc doesnt want to inline that ;/
	const i32x4 operator*=(i32x4 v) __attribute__((always_inline));
	const i32x4 operator/=(i32x4 v) __attribute__((always_inline));

	const i32x4 operator%=(i32x4 v) {
		i[0] %= v.i[0]; i[1] %= v.i[1]; i[2] %= v.i[2]; i[3] %= v.i[3];
	// TODO: repair this
	/*	__m128d a0=_mm_cvtepi32_pd(m),b0=_mm_cvtepi32_pd(v.m);
		__m128d a1=_mm_cvtepi32_pd(_mm_shuffle_epi32(m,2*1+3*4)),b1=_mm_cvtepi32_pd(_mm_shuffle_epi32(v.m,2*1+3*4));
		a0=_mm_div_pd(a0,b0); a1=_mm_div_pd(a1,b1);

		a0=_mm_cvtepi32_pd(_mm_cvttpd_epi32(a0));
		a1=_mm_cvtepi32_pd(_mm_cvttpd_epi32(a1));

		a0=_mm_mul_pd(a0,b0); a1=_mm_mul_pd(a1,b1);

		m=_mm_sub_epi32(m,	_mm_castps_si128(	_mm_shuffle_ps(	_mm_castsi128_ps(_mm_cvttpd_epi32(a0)),
																_mm_castsi128_ps(_mm_cvttpd_epi32(a1)),0+1*4+0*16+1*64))); */
		return *this;
	}

	const i32x4 operator++() { m = _mm_add_epi32(m, _mm_set1_epi32(+1)); return *this; }
	const i32x4 operator--() { m = _mm_add_epi32(m, _mm_set1_epi32(-1)); return *this; }

	const i32x4 operator-() const { return _mm_sub_epi32(_mm_setzero_si128(),m); }
	const i32x4 operator~() const { return _mm_andnot_si128(m,_mm_set1_epi32(~0)); }

	const i32x4b operator!() const;
	operator const i32x4bn() const;

	operator i32*() { return i; }
	operator const i32*() const { return i; }

	union {
		__m128i m;
		i32 i[4];
		u32 u[4];
	};
};

inline const i32x4 i32x4::operator*=(i32x4 v) {
	__m128i xmm1 = m, xmm0 = v.m;
	__m128i xmm2 = xmm1;
	xmm1 = _mm_srli_si128(xmm1, 4);
	xmm2 = _mm_mul_epu32(xmm0, xmm2);
	xmm0 = _mm_srli_si128(xmm0, 4);
	xmm1 = _mm_mul_epu32(xmm0, xmm1);
	xmm0 = _mm_shuffle_epi32(xmm2, 8);
	xmm1 = _mm_shuffle_epi32(xmm1, 8);
	m = _mm_unpacklo_epi32(xmm0, xmm1);
	return *this;
}

inline const i32x4 i32x4::operator/=(i32x4 v) {
	__m128d a0 = _mm_cvtepi32_pd(m), b0 = _mm_cvtepi32_pd(v.m);
	__m128d a1 = _mm_cvtepi32_pd(_mm_shuffle_epi32(m, 2 * 1 + 3 * 4)), b1 = _mm_cvtepi32_pd(_mm_shuffle_epi32(v.m, 2 * 1 + 3 * 4));
	a0 = _mm_div_pd(a0, b0);
	a1 = _mm_div_pd(a1, b1);
	m = _mm_castps_si128(	_mm_shuffle_ps(	_mm_castsi128_ps(_mm_cvttpd_epi32(a0)),
											_mm_castsi128_ps(_mm_cvttpd_epi32(a1)),0+1*4+0*16+1*64));
	return *this;
}

inline const i32x4 operator+(i32x4 a, i32x4 b)	{ return _mm_add_epi32(a.m, b.m); }
inline const i32x4 operator-(i32x4 a, i32x4 b)	{ return _mm_sub_epi32(a.m, b.m); }
inline const i32x4 operator*(i32x4 a, i32x4 b)	{ i32x4 out(a); out *= b; return out; }
inline const i32x4 operator/(i32x4 a, i32x4 b)	{ i32x4 out(a); out /= b; return out; }
inline const i32x4 operator%(i32x4 a, i32x4 b)	{ i32x4 out(a); out %= b; return out; }
inline const i32x4 operator&(i32x4 a, i32x4 b)	{ return _mm_and_si128(a.m, b.m); }
inline const i32x4 operator|(i32x4 a, i32x4 b)	{ return _mm_or_si128(a.m, b.m); }
inline const i32x4 operator^(i32x4 a, i32x4 b)	{ return _mm_xor_si128(a.m, b.m); }
inline const i32x4 operator<<(i32x4 a, i32x4 b)	{ return _mm_sll_epi32(a.m, b.m); }
inline const i32x4 operator>>(i32x4 a, i32x4 b)	{ return _mm_sra_epi32(a.m, b.m); }

template <unsigned bits>
inline const i32x4 Shl(i32x4 in) { return _mm_slli_epi32(in.m, bits); }

template <unsigned bits>
inline const i32x4 Shr(i32x4 in) { return _mm_srli_epi32(in.m, bits); }

// Correct up to 23 bits; UAYOR
inline const i32x4 FastMul(i32x4 ta,i32x4 tb) {
	__m128 a = _mm_cvtepi32_ps(ta.m),b=_mm_cvtepi32_ps(tb.m);
	return _mm_cvttps_epi32(_mm_mul_ps(a,b));
}
// Correct up to 23 bits; UAYOR
inline const i32x4 FastDiv(i32x4 ta,i32x4 tb) {
	__m128 a = _mm_cvtepi32_ps(ta.m), b = _mm_cvtepi32_ps(tb.m);
	return _mm_cvttps_epi32(_mm_div_ps(a, b));
}

inline const i32x4 Abs(i32x4 in) {
#if VECLIB_SSE_VER>=0x31
	return _mm_abs_epi32(in.m);
#else
	__m128i tmp = _mm_srai_epi32(in.m, 31);
	return _mm_sub_epi32(_mm_xor_si128(in.m, tmp), tmp);
#endif
}


class i32x4b
{
public:
	i32x4b() { }
	i32x4b(__m128i m) :m(m) { }

	const i32x4b operator^(i32x4b v) const	{ return _mm_xor_si128(m,v.m); }
	const i32x4b operator&&(i32x4b v) const	{ return _mm_and_si128(m,v.m); }
	const i32x4b operator||(i32x4b v) const	{ return _mm_or_si128(m,v.m); }

	i32x4b(f32x4b v)					:m(_mm_castps_si128(v.m)) { }
	operator const f32x4b() const		{ return _mm_castsi128_ps(m); }

	__m128i m;
};

inline i32x4::i32x4(i32x4b v) :m(v.m) { }

class i32x4bn
{
public:
	const i32x4bn operator^(i32x4b v) const		{ return _mm_xor_si128(m,v.m); }
	const i32x4b operator^(i32x4bn v) const		{ return _mm_xor_si128(m,v.m); }
	const i32x4b operator!() const				{ return i32x4b(m); }

	const i32x4b operator&&(i32x4b v) const		{ return _mm_andnot_si128(m,v.m); }
	const i32x4bn operator&&(i32x4bn v) const	{ return _mm_or_si128(m,v.m); }

	const i32x4bn operator||(i32x4bn v) const	{ return _mm_and_si128(m,v.m); }
	const i32x4b operator||(i32x4b v) const		{ return _mm_or_si128(_mm_andnot_si128(m,_mm_set1_epi32(~0)),v.m); }
	operator const i32x4b() const				{ return _mm_andnot_si128(m,_mm_set1_epi32(~0)); }

//	i32x4bn(const f32x4bn &v)			:m(_mm_castps_si128(v.NegM())) { }
//	operator f32x4bn() const			{ return _mm_castsi128_ps(m); }

	const __m128i NegM() const { return m; }

private:
	i32x4bn(__m128i m) :m(m) { }
	friend const i32x4bn operator!(i32x4b);
	friend const i32x4bn operator^(i32x4b, i32x4bn);
	friend const i32x4bn operator!=(i32x4, i32x4);
	friend const i32x4bn operator<=(i32x4, i32x4);
	friend const i32x4bn operator>=(i32x4, i32x4);
	friend i32x4::operator const i32x4bn() const;

	// To access it you have to
	// convert to i32x4b first
	__m128i m;
};

inline i32x4::operator const i32x4bn() const { return i32x4bn(_mm_cmpeq_epi32(m,_mm_setzero_si128())); }
inline const i32x4b i32x4::operator!() const { return i32x4b(_mm_cmpeq_epi32(m,_mm_setzero_si128())); }

inline const i32x4bn operator!(i32x4b v)				{ return i32x4bn(v.m); }
inline const i32x4bn operator^(i32x4b a,i32x4bn b)		{ return i32x4bn(_mm_xor_si128(a.m,b.NegM())); }
inline const i32x4b operator&&(i32x4b a,i32x4bn b)		{ return _mm_andnot_si128(b.NegM(),a.m); }
inline const i32x4b operator||(i32x4b a,i32x4bn b)
	{ return _mm_or_si128(a.m,_mm_andnot_si128(b.NegM(),_mm_set1_epi32(~0))); }

inline bool ForAny(i32x4b test) { return _mm_movemask_epi8(test.m)?1:0; }
inline bool ForAll(i32x4b test) { return _mm_movemask_epi8(test.m)==0xffff?1:0; }
inline int ForWhich(i32x4b test) {
	int mask = _mm_movemask_epi8(test.m);
	return ((mask & 0x000f)?1 : 0) | ((mask & 0x00f0)?2 : 0) | ((mask & 0x0f00)?4 : 0) | ((mask & 0xf000)?8 : 0);
}
inline const i32x4bn	operator!=(i32x4 a,i32x4 b) { return _mm_cmpeq_epi32(a.m,b.m); }
inline const i32x4b 	operator==(i32x4 a,i32x4 b) { return _mm_cmpeq_epi32(a.m,b.m); }
inline const i32x4b		operator< (i32x4 a,i32x4 b) { return _mm_cmplt_epi32(a.m,b.m); }
inline const i32x4b		operator> (i32x4 a,i32x4 b) { return _mm_cmpgt_epi32(a.m,b.m); }
inline const i32x4bn	operator<=(i32x4 a,i32x4 b) { return _mm_cmpgt_epi32(a.m,b.m); }
inline const i32x4bn	operator>=(i32x4 a,i32x4 b) { return _mm_cmplt_epi32(a.m,b.m); }

inline const i32x4 Condition(i32x4b test,i32x4 v1,i32x4 v2)
	{ return _mm_or_si128(_mm_and_si128(test.m,v1.m),_mm_andnot_si128(test.m,v2.m)); }
inline const i32x4 Condition(i32x4b test,i32x4 v1)
	{ return _mm_and_si128(test.m,v1.m); }
inline const i32x4 Condition(i32x4bn test,i32x4 v1,i32x4 v2)
	{ return _mm_or_si128(_mm_andnot_si128(test.NegM(),v1.m),_mm_and_si128(test.NegM(),v2.m)); }
inline const i32x4 Condition(i32x4bn test,i32x4 v1)
	{ return _mm_andnot_si128(test.NegM(),v1.m); }

inline const i32x4 Max(i32x4 a,i32x4 b) {
	__m128i tmp = _mm_cmpgt_epi32(a.m,b.m);
	return _mm_or_si128(_mm_andnot_si128(tmp, b.m), _mm_and_si128(tmp, a.m));
}
inline const i32x4 Min(i32x4 a,i32x4 b) {
	__m128i tmp = _mm_cmpgt_epi32(a.m,b.m);
	return _mm_or_si128(_mm_and_si128(tmp, b.m),_mm_andnot_si128(tmp, a.m));
}
template<>
struct ScalarInfo<i32x4> {
	enum { multiplicity=4, floatingPoint=0 };
	typedef i32x4b TBool;

	inline static i32x4 ElementMask(int n) {
		static __m128i elems[4]={_mm_set_epi32(0,0,0,~0),_mm_set_epi32(0,0,~0,0),_mm_set_epi32(0,~0,0,0),_mm_set_epi32(~0,0,0,0)};
		return i32x4(elems[n]);
    }
};

inline void Broadcast(const int &in, i32x4 &out) { out = _mm_set1_epi32(in); }
inline void Convert(const int in[4], i32x4 &out) { out = _mm_loadu_si128((__m128i*)in); }
inline void Convert(i32x4 in, int out[4]) { _mm_storeu_si128((__m128i*)out, in.m); }

inline void Convert(int inX, int inY, int inZ, int inW, i32x4 &out) {
    out = _mm_set_epi32(inW,inZ,inY,inX);
}
inline void Convert(const i32x4 in, int &outX, int &outY, int &outZ, int &outW) {
	outX = in[0]; outY = in[1]; outZ = in[2]; outW = in[3];
}

inline const i32x4 Round(const f32x4 &flt)			{ return _mm_cvtps_epi32(flt.m); }
inline const i32x4 Trunc(const f32x4 &flt)			{ return _mm_cvttps_epi32(flt.m); }

inline void Cast(i32x4 src, f32x4 &dst)			{ dst.m=_mm_castsi128_ps(src.m); }
inline void Cast(const f32x4 &src, i32x4 &dst)	{ dst.m=_mm_castps_si128(src.m); }

// Auto conversion
//inline void Cast(i32x4b src	,f32x4b &dst)	{ dst.m=_mm_castsi128_ps(src.m); }
//inline void Cast(const f32x4b &src	,i32x4b &dst)	{ dst.m=_mm_castps_si128(src.m); }

#endif

