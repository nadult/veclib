#ifndef VECLIB_SSEMASK_H
#define VECLIB_SSEMASK_H

#include "sse.h"

// -----------------------------------------------------------------------------------------------------------
#define SSEMASK_CLASS SSEMask
#define SSEMASK_NEG_CLASS SSEMaskNeg
#define SSEMASK_ADDITIONAL_CODE
#define SSEMASK_NEG_ADDITIONAL_CODE

#include "ssemask_gen.h"

#undef SSEMASK_ADDITIONAL_CODE
#undef SSEMASK_NEG_ADDITIONAL_CODE
#undef SSEMASK_CLASS
#undef SSEMASK_NEG_CLASS
// -----------------------------------------------------------------------------------------------------------
#define SSEMASK_CLASS SSEPMask
#define SSEMASK_NEG_CLASS SSEPMaskNeg
#define SSEMASK_ADDITIONAL_CODE \
	INLINE operator SSEMask() const { SSEMask out(m); return out; }

#define SSEMASK_NEG_ADDITIONAL_CODE \
	INLINE operator SSEMask() const { SSEMask out(_mm_andnot_ps(m,Const<SSEPMask,0xffffffff>::Value().m)); return out; } \
	INLINE operator SSEMaskNeg() const { SSEMaskNeg out(m); return out; }

#include "ssemask_gen.h"

#undef SSEMASK_ADDITIONAL_CODE
#undef SSEMASK_NEG_ADDITIONAL_CODE
#undef SSEMASK_CLASS
#undef SSEMASK_NEG_CLASS
// -----------------------------------------------------------------------------------------------------------

INLINE bool ForAny(const SSEMask &v) { return _mm_movemask_ps(v.m)?1:0; }
INLINE bool ForAll(const SSEMask &v) { return _mm_movemask_ps(v.m)==15; }
INLINE int ForWhich(const SSEMask &v) { return _mm_movemask_ps(v.m); }

INLINE bool ForAny(const SSEPMask &v) { return _mm_movemask_ps(v.m)?1:0; }
INLINE bool ForAll(const SSEPMask &v) { return _mm_movemask_ps(v.m)==15; }
INLINE int ForWhich(const SSEPMask &v) { return _mm_movemask_ps(v.m)&1; }


#endif
