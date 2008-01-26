#ifndef VECLIB_VECLIB_H
#define VECLIB_VECLIB_H


#include <cmath>
#include <cstdlib>
#include <xmmintrin.h>
#include <emmintrin.h>

#ifdef _MSC_VER
	#define VECLIB_DECL_ALIGNED_FLOAT(name,size)	__declspec(align(16)) float name[size];
#else // gcc
	#define VECLIB_DECL_ALIGNED_FLOAT(name,size)	float name[size] __attribute__ ((aligned (16)));
#endif

#ifdef _MSC_VER
	#define INLINE	__forceinline
#else
	#define INLINE inline
#endif

#include "vecliball_pp.h"

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

	SSEPReal							SSEReal
	SSEPVec2							SSEVec2
	SSEPVec3							SSEVec3
	SSEPVec4							SSEVec4
	SSEPMatrix
	SSEPAMatrix

	float			floatd				floatq									floath
	vec2			vec2d				vec2q									vec2h
*/

/*

Avaliable functions:

+ - * /
Sqrt
Inv ( v )							1 / v
RSqrt ( v )							1 / Sqrt ( v )
FastInv	( v )						~ Inv ( v )
FastRSqrt ( v )						~ RSqrt ( v )

Abs
Min
Max

Condition ( expr, a, b )		if expr then a else b
Condition ( expr, a )			if expr then a else 0

Convert ( in , out )			Conversion between different scalar / vector formats

Vector operations:
|								dot product
^								cross product
Length ( v )					Sqrt ( v|v )

*/


#endif
