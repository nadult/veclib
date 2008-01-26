#ifndef VECLIB_SSEMASK4_H
#define VECLIB_SSEMASK4_H

#include "ssemask.h"

class SSEMaskNeg4;

class SSEMask4
{
public:
	INLINE SSEMask4() { }
	INLINE SSEMask4(const __m128 &v) { m[0]=m[1]=m[2]=m[3]=v; }
	INLINE SSEMask4(const __m128 &v0,const __m128 &v1,const __m128 &v2,const __m128 &v3) { m[0]=v0; m[1]=v1; m[2]=v2; m[3]=v3; }
	INLINE SSEMask4(const SSEPMask &v) { m[0]=m[1]=m[2]=m[3]=v.m; }

	INLINE SSEMask4 operator^(const SSEMask4 &v) const {
		SSEMask4 out;
		out.m[0]=_mm_xor_ps(m[0],v.m[0]);
		out.m[1]=_mm_xor_ps(m[1],v.m[1]);
		out.m[2]=_mm_xor_ps(m[2],v.m[2]);
		out.m[3]=_mm_xor_ps(m[3],v.m[3]);
		return out;
	}
	INLINE SSEMask4 operator&&(const SSEMask4 &v) const {
		SSEMask4 out;
		out.m[0]=_mm_and_ps(m[0],v.m[0]);
		out.m[1]=_mm_and_ps(m[1],v.m[1]);
		out.m[2]=_mm_and_ps(m[2],v.m[2]);
		out.m[3]=_mm_and_ps(m[3],v.m[3]);
		return out;
	}

	INLINE SSEMask4 operator||(const SSEMask4 &v) const {
		SSEMask4 out;
		out.m[0]=_mm_or_ps(m[0],v.m[0]);
		out.m[1]=_mm_or_ps(m[1],v.m[1]);
		out.m[2]=_mm_or_ps(m[2],v.m[2]);
		out.m[3]=_mm_or_ps(m[3],v.m[3]);
		return out;
	}

	__m128 m[4];
};

template <int mask> class Const<SSEMask4,mask,1> {
public:
	static SSEMask4 Value() { return SSEMask4(Const<SSEPMask,mask,1>::Value()); }
};

class SSEMaskNeg4
{
public:
	INLINE SSEMaskNeg4() { }
	INLINE SSEMaskNeg4(const __m128 &v) { m[0]=m[1]=m[2]=m[3]=v; }
	INLINE SSEMaskNeg4(const __m128 &v0,const __m128 &v1,const __m128 &v2,const __m128 &v3) { m[0]=v0; m[1]=v1; m[2]=v2; m[3]=v3; }
	INLINE SSEMaskNeg4(const SSEPMaskNeg &v) { m[0]=m[1]=m[2]=m[3]=v.m; }

	INLINE SSEMaskNeg4 operator^(const SSEMask4 &v) const {
		SSEMaskNeg4 out;
		out.m[0]=_mm_xor_ps(m[0],v.m[0]);
		out.m[1]=_mm_xor_ps(m[1],v.m[1]);
		out.m[2]=_mm_xor_ps(m[2],v.m[2]);
		out.m[3]=_mm_xor_ps(m[3],v.m[3]);
		return out;
	}
	INLINE SSEMask4 operator^(const SSEMaskNeg4 &v) const {
		SSEMask4 out;
		out.m[0]=_mm_xor_ps(m[0],v.m[0]);
		out.m[1]=_mm_xor_ps(m[1],v.m[1]);
		out.m[2]=_mm_xor_ps(m[2],v.m[2]);
		out.m[3]=_mm_xor_ps(m[3],v.m[3]);
		return out;
	}
	INLINE SSEMask4 operator!() const {
		return SSEMask4(m[0],m[1],m[2],m[3]);
	}

	INLINE SSEMask4 operator&&(const SSEMask4 &v) const {
		SSEMask4 out;
		out.m[0]=_mm_andnot_ps(m[0],v.m[0]);
		out.m[1]=_mm_andnot_ps(m[1],v.m[1]);
		out.m[2]=_mm_andnot_ps(m[2],v.m[2]);
		out.m[3]=_mm_andnot_ps(m[3],v.m[3]);
		return out;
	}
	INLINE SSEMaskNeg4 operator&&(const SSEMaskNeg4 &v) const {
		SSEMaskNeg4 out;
		out.m[0]=_mm_or_ps(m[0],v.m[0]);
		out.m[1]=_mm_or_ps(m[1],v.m[1]);
		out.m[2]=_mm_or_ps(m[2],v.m[2]);
		out.m[3]=_mm_or_ps(m[3],v.m[3]);
		return out;
	}

	INLINE SSEMaskNeg4 operator||(const SSEMaskNeg4 &v) const {
		SSEMaskNeg4 out;
		out.m[0]=_mm_and_ps(m[0],v.m[0]);
		out.m[1]=_mm_and_ps(m[1],v.m[1]);
		out.m[2]=_mm_and_ps(m[2],v.m[2]);
		out.m[3]=_mm_and_ps(m[3],v.m[3]);
		return out;
	}
	INLINE SSEMask4 operator||(const SSEMask4 &v) const {
		SSEMaskNeg4 out;
		out.m[0]=_mm_or_ps(_mm_andnot_ps(m[0],Const<SSEPMask,0xffffffff>::Value().m),v.m[0]);
		out.m[1]=_mm_or_ps(_mm_andnot_ps(m[1],Const<SSEPMask,0xffffffff>::Value().m),v.m[1]);
		out.m[2]=_mm_or_ps(_mm_andnot_ps(m[2],Const<SSEPMask,0xffffffff>::Value().m),v.m[2]);
		out.m[3]=_mm_or_ps(_mm_andnot_ps(m[3],Const<SSEPMask,0xffffffff>::Value().m),v.m[3]);
		return out;
	}
	operator SSEMask4() const {
		SSEMaskNeg4 out;
		out.m[0]=_mm_andnot_ps(m[0],Const<SSEPMask,0xffffffff>::Value().m);
		out.m[1]=_mm_andnot_ps(m[1],Const<SSEPMask,0xffffffff>::Value().m);
		out.m[2]=_mm_andnot_ps(m[2],Const<SSEPMask,0xffffffff>::Value().m);
		out.m[3]=_mm_andnot_ps(m[3],Const<SSEPMask,0xffffffff>::Value().m);
		return out;
	}

	__m128 m[4];
};

INLINE SSEMaskNeg4 operator!(const SSEMask4 &v) {
	return SSEMaskNeg4(v.m[0],v.m[1],v.m[2],v.m[3]);
}
INLINE SSEMaskNeg4 operator^(const SSEMask4 &a,const SSEMaskNeg4 &b) {
	SSEMaskNeg4 out;
	out.m[0]=_mm_xor_ps(a.m[0],b.m[0]);
	out.m[1]=_mm_xor_ps(a.m[1],b.m[1]);
	out.m[2]=_mm_xor_ps(a.m[2],b.m[2]);
	out.m[3]=_mm_xor_ps(a.m[3],b.m[3]);
	return out;
}
INLINE SSEMask4 operator&&(const SSEMask4 &a,const SSEMaskNeg4 &b) {
	SSEMask4 out;
	out.m[0]=_mm_andnot_ps(b.m[0],a.m[0]);
	out.m[1]=_mm_andnot_ps(b.m[1],a.m[1]);
	out.m[2]=_mm_andnot_ps(b.m[2],a.m[2]);
	out.m[3]=_mm_andnot_ps(b.m[3],a.m[3]);
	return out;
}
INLINE SSEMask4 operator||(const SSEMask4 &a,const SSEMaskNeg4 &b) {
	SSEMask4 out;
	out.m[0]=_mm_or_ps(a.m[0],_mm_andnot_ps(b.m[0],Const<SSEPMask,0xffffffff>::Value().m));
	out.m[1]=_mm_or_ps(a.m[1],_mm_andnot_ps(b.m[1],Const<SSEPMask,0xffffffff>::Value().m));
	out.m[2]=_mm_or_ps(a.m[2],_mm_andnot_ps(b.m[2],Const<SSEPMask,0xffffffff>::Value().m));
	out.m[3]=_mm_or_ps(a.m[3],_mm_andnot_ps(b.m[3],Const<SSEPMask,0xffffffff>::Value().m));
	return out;
}

INLINE bool ForAny(const SSEMask4 &v) {
	return (_mm_movemask_ps(v.m[0])+_mm_movemask_ps(v.m[1]))+(_mm_movemask_ps(v.m[2])+_mm_movemask_ps(v.m[3]))?1:0;
}
INLINE bool ForAll(const SSEMask4 &v) {
	return ((_mm_movemask_ps(v.m[0])&_mm_movemask_ps(v.m[1]))&(_mm_movemask_ps(v.m[2])&_mm_movemask_ps(v.m[3])))==15;
}
INLINE int ForWhich(const SSEMask4 &v) {
	return	(_mm_movemask_ps(v.m[0])<<0)+
			(_mm_movemask_ps(v.m[1])<<4)+
			(_mm_movemask_ps(v.m[2])<<8)+
			(_mm_movemask_ps(v.m[3])<<12);
}


#endif
