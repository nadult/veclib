#if !defined(VECLIB_SSEMASK_H) && VECLIB_SSE_VER>=0x10
#define VECLIB_SSEMASK_H

#include "sse.h"

#define SSEMask SSEMask
#define SSEMaskNeg SSEMaskNeg
#define SSEMASK_ADDITIONAL_CODE
#define SSEMASK_NEG_ADDITIONAL_CODE

class SSEMaskNeg;

class SSEMask
{
public:
	INLINE SSEMask() { }
	INLINE SSEMask(const __m128 &v) :m(v) { }

	INLINE SSEMask operator^(const SSEMask &v) const	{ return _mm_xor_ps(m,v.m); }
	INLINE SSEMask operator&&(const SSEMask &v) const	{ return _mm_and_ps(m,v.m); }
	INLINE SSEMask operator||(const SSEMask &v) const	{ return _mm_or_ps(m,v.m); }

	__m128 m;
};

template <bool v>
struct CBConst<SSEMask,v> { static SSEMask Value() { return SSEMask(SSEMaskConst<v?0xffffffff:0>::value); } };

class SSEMaskNeg
{
public:
	INLINE SSEMaskNeg operator^(const SSEMask &v) const		{ return _mm_xor_ps(m,v.m); }
	INLINE SSEMask operator^(const SSEMaskNeg &v) const		{ return _mm_xor_ps(m,v.m); }
	INLINE SSEMask operator!() const						{ return SSEMask(m); }

	INLINE SSEMask operator&&(const SSEMask &v) const		{ return _mm_andnot_ps(m,v.m); }
	INLINE SSEMaskNeg operator&&(const SSEMaskNeg &v) const	{ return _mm_or_ps(m,v.m); }

	INLINE SSEMaskNeg operator||(const SSEMaskNeg &v) const	{ return _mm_and_ps(m,v.m); }
	INLINE SSEMask operator||(const SSEMask &v) const		{ return _mm_or_ps(_mm_andnot_ps(m,SSEMaskConst<0xffffffff>::value),v.m); }
	operator SSEMask() const								{ return _mm_andnot_ps(m,SSEMaskConst<0xffffffff>::value); }

	const __m128 &NegM() const { return m; }
private:
	INLINE SSEMaskNeg(const __m128 &v) :m(v) { }
	friend SSEMaskNeg operator!(const SSEMask&);
	friend SSEMaskNeg operator^(const SSEMask&,const SSEMaskNeg&);

	// To access it you have to
	// convert to SSEMask first
	__m128 m;
};

INLINE SSEMaskNeg operator!(const SSEMask &v)						{ return SSEMaskNeg(v.m); }
INLINE SSEMaskNeg operator^(const SSEMask &a,const SSEMaskNeg &b)	{ return SSEMaskNeg(_mm_xor_ps(a.m,b.NegM())); }
INLINE SSEMask operator&&(const SSEMask &a,const SSEMaskNeg &b)		{ return _mm_andnot_ps(b.NegM(),a.m); }
INLINE SSEMask operator||(const SSEMask &a,const SSEMaskNeg &b)
	{ return _mm_or_ps(a.m,_mm_andnot_ps(b.NegM(),SSEMaskConst<0xffffffff>::value)); }

INLINE bool ForAny(const SSEMask &v) { return _mm_movemask_ps(v.m)?1:0; }
INLINE bool ForAll(const SSEMask &v) { return _mm_movemask_ps(v.m)==15; }
INLINE int ForWhich(const SSEMask &v) { return _mm_movemask_ps(v.m); }

#endif

