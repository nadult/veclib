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


Basic types -----------------------------------------------------------------------------------
f32		f64		i8		i16		i32		i64		u8		u16		u32		u64
bool

Packed types (SSE) ----------------------------------------------------------------------------
f32x4	f64x2	i8x16	i16x8	i32x4	i64x2	u8x16	u16x8	u32x4	u64x2

Vector templates ------------------------------------------------------------------------------
vec2< >
vec3< >
vec4< >

Packed vector types (SSE) ---------------------------------------------------------------------
pvec2f32	pvec2f64
pvec3f32	pvec3f64
pvec4f32	pvec4f64

Matrices --------------------------------------------------------------------------------------

Matrix< >

ScalarInfo < Type > gives info about types:
	::floatingPoint			- false for integer types
	::multiplicity			- number of sub elements, for example:
								ScalarInfo< f32x4 >::multiplicity == 4
	::TBool					- use this type to store boolean information obtained
								from comparing objects of given Type
	::ElementMask( n )		- returns mask of type TBool true for selected element


Templated functions -------------------------------------------------------------------------------

Clamp ( a, min, max )				returns object a clamped to values min, max
Lerp ( a, b, x )					linear interpolation of objects a and b; x==0 -> a;  x==1 -> b 
Swap ( a& , b& )					classic swap

Not vectorized functions:

Sin ( v )
Cos ( v )

Floating point operations -------------------------------------------------------------------------

+ - * /
Sqrt ( v )
Inv ( v )					==		1 / v
RSqrt ( v )					==		1 / Sqrt ( v )
FastInv	( v )				~=		Inv ( v )
FastRSqrt ( v )				~=		RSqrt ( v )

Abs ( v )
Min ( a , b )
Max ( a , b )

Condition ( expr, a, b )			if expr then a else b
Condition ( expr, a )				if expr then a else 0

Convert ( in , out )				Conversion between different scalar / vector formats

All of these operations work also on vectors, for example:
	Vec (x1, y1, z1) * Vec(x2, y2, z2) == Vec(x1*x2, y1*y2, z1*z2)

Additional vector operations ----------------------------------------------------------------------
|									dot product
^									cross product
Length ( v )						Sqrt ( v|v )


Integer operations --------------------------------------------------------------------------------
+ - * / % | & ^ ~
Abs ( v )
Max ( a , b )
Min ( a , b )


Technical functions -------------------------------------------------------------------------------

SignMask ( v )						Returns integer with #n bit set when #n element is < 0

ForAny ( e )						| Returns true if expression if true for any / every element,
ForAll ( e )						| example: if ( ForAll( val1*val2 < val3 ) ) { .. do something .. }
ForWhich ( e )						similar to SignMask, #n bit is set when expression is true for #n element

u64 Ticks ( )						rdtsc cpu instruction

*/


#endif
