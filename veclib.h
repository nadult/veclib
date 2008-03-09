#ifndef VECLIB_VECLIB_H
#define VECLIB_VECLIB_H


#include <cmath>
#include <cstdlib>

#include "veclib_conf.h"

#if VECLIB_SSE_VER>=0x31
    #include <tmmintrin.h>
#elif VECLIB_SSE_VER>=0x30
    #include <pmmintrin.h>
#elif VECLIB_SSE_VER>=0x20
    #include <emmintrin.h>
#elif VECLIB_SSE_VER>=0x10
    #include <xmmintrin.h>
#endif


#if 0
	#if VECLIB_SSE_VER>=0x31
		#include "vecliball_pp31.h"
	#elif VECLIB_SSE_VER>=0x30
		#include "vecliball_pp30.h"
	#elif VECLIB_SSE_VER>=0x20
		#include "vecliball_pp20.h"
	#elif VECLIB_SSE_VER>=0x10
		#include "vecliball_pp10.h"
	#else
		#include "vecliball_pp.h"
	#endif
#else
	#include "vecliball.h"
#endif

namespace veclib
{

#if defined(VECLIB_GCC_STYLE)
	#if VECLIB_ARCH==0x32

INLINE u64 Ticks() {
	u64 x;
	__asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
	return x;
}

	#elif VECLIB_ARCH==0x64

INLINE u64 Ticks() {
    unsigned hi, lo;
    __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
   	return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}

	#endif
#elif defined(VECLIB_MSVC_STYLE)

INLINE u64 Ticks() {
	u32 ddlow,ddhigh;
	__asm{
		rdtsc
		mov ddlow, eax
		mov ddhigh, edx
	}
	return (((u64)ddhigh)<<32)|(u64)ddlow;
}

#endif

}

#ifndef _mm_shuffle
	#define _mm_shuffle(mask,v)	_mm_shuffle_<mask>(v)
#endif

/*
	float			float*2				float*4				float*8				float*16
	Vec2<float>		Vec2<float>*2		Vec2<float>*4		Vec2<float>*8		Vec2<float>*16
	Vec3<float>		Vec3<float>*2		Vec3<float>*4		Vec3<float>*8		Vec3<float>*16
	Vec4<float>		Vec4<float>*2		Vec4<float>*4		Vec4<float>*8		Vec4<float>*16
	AMatrix
	Matrix

	float								SSEReal				*** Will be added in the future ***
	SSEPVec2							SSEVec2				*** At least i hope so ***
	SSEPVec3							SSEVec3
	SSEPVec4							SSEVec4				*** Im sure it will, when new processors with
	SSEPMatrix													x16 simd operations will show up :) ****
	SSEPAMatrix

	float			floatd				floatq
	vec2			vec2d				vec2q


	i32				i32*2				i32*4

										SSEInt
*/

/*

Avaliable function:					Equals to:

+ - * /
Sqrt
Inv ( v )							1 / v
RSqrt ( v )							1 / Sqrt ( v )
FastInv	( v )						~ Inv ( v )
FastRSqrt ( v )						~ RSqrt ( v )

Abs
Min
Max

Condition ( expr, a, b )			if expr then a else b
Condition ( expr, a )				if expr then a else 0

Convert ( in , out )				Conversion between different scalar / vector formats

Vector operations:
|									dot product
^									cross product
Length ( v )						Sqrt ( v|v )

*/


#endif
