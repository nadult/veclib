#ifndef VECLIB_SSEREAL_H
#define VECLIB_SSEREAL_H

#include "sse.h"
#include "ssemask.h"

// -----------------------------------------------------------------------------------------------------------
#define CLASS_NAME SSEReal
#define MASK_NAME SSEMask
#define MASK_NAME_NEG SSEMaskNeg
#define ADDITIONAL_CLASS_CODE \
	INLINE SSEReal(float a,float b,float c,float d) :m(_mm_set_ps(a,b,c,d)) { } \
	INLINE SSEReal(const float *ptr) :m(_mm_load_ps(ptr)) { }

#include "ssereal_gen.h"

#undef CLASS_NAME
#undef MASK_NAME
#undef MASK_NAME_NEG
#undef ADDITIONAL_CLASS_CODE
// -----------------------------------------------------------------------------------------------------------
#define CLASS_NAME SSEPReal
#define MASK_NAME SSEPMask
#define MASK_NAME_NEG SSEPMaskNeg
#define ADDITIONAL_CLASS_CODE \
	operator SSEReal() const { SSEReal out; out.m=m; return out; }

#include "ssereal_gen.h"

#undef CLASS_NAME
#undef MASK_NAME
#undef MASK_NAME_NEG
#undef ADDITIONAL_CLASS_CODE
// -----------------------------------------------------------------------------------------------------------

template <>
struct ScalarInfo<SSEReal> {
	enum { Multiplicity=4 };
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

template <>
struct ScalarInfo<SSEPReal> {
	enum { Multiplicity=1 };
	typedef SSEPMask TBool;

	INLINE static SSEPMask ElementMask(int n) {
		return Const<SSEPMask,0xffffffff>::Value();
	}
};

INLINE void Broadcast(const float &in,SSEReal &out) {
	out=_mm_load1(in);
}
INLINE void Convert(const float in[4],SSEReal &out) {
	out=_mm_load4(in);
}
INLINE void Convert(const SSEReal &in,float out[4]) {
	_mm_store4(in.m,out);
}
INLINE void Convert(float inX,float inY,float inZ,float inW,SSEReal &out) {
	out=_mm_set_ps(inW,inZ,inY,inX);
}
INLINE void Convert(const SSEReal &in,float &outX,float &outY,float &outZ,float &outW) {
	_mm_store_ss(&outX,in.m);
	_mm_store_ss(&outY,_mm_shuffle(1,in.m));
	_mm_store_ss(&outZ,_mm_shuffle(2,in.m));
	_mm_store_ss(&outW,_mm_shuffle(3,in.m));
}

INLINE void Convert(const float &in,SSEPReal &out) {
	out=_mm_load1(in);
}
INLINE void Convert(const SSEPReal &in,float &out) {
	_mm_store_ss(&out,in.m);
}


#endif
