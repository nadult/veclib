// Author (mostly): Krzysztof 'nadult' Jakubowski
//
// Some of the code comes from Sony simdmathlibrary
// (licensed under BSD).


#ifndef VECLIB_VECLIB_H
#define VECLIB_VECLIB_H


#include <cmath>
#include <cstdlib>

#include "veclib_conf.h"

#ifdef VECLIB_SSE
	#if VECLIB_SSE >= 0x31
	    #include <tmmintrin.h>
	#elif VECLIB_SSE >= 0x30
	    #include <pmmintrin.h>
	#elif VECLIB_SSE >= 0x20
	    #include <emmintrin.h>
	#elif VECLIB_SSE >= 0x10
	    #include <xmmintrin.h>
	#endif
#elif defined(VECLIB_ALTIVEC)
	#define bool bool_ // FFS!
		#include <altivec.h>
	#undef bool
#elif defined(VECLIB_SPU)
	#define bool bool_
		#include <spu_intrinsics.h>
	#undef bool
#else
		#error "undefined"
#endif

namespace veclib
{
	namespace basetypes
	{
		typedef unsigned char		u8;
		typedef char				i8;
		typedef short				i16;
		typedef unsigned short		u16;
		typedef int					i32;
		typedef unsigned int		u32;
		typedef long long			i64;
		typedef unsigned long long	u64;
		
		typedef float				f32;
		typedef double				f64;
	}
	using namespace basetypes;

	#include "vecbase.h"
	#include "vec2.h"
	#include "vec3.h"
	#include "vec4.h"

#ifdef VECLIB_SSE
	#include "sse/f32.h"
	#include "sse/vecf32.h"
	#include "sse/i32.h"
	#ifndef _mm_shuffle
		#define _mm_shuffle(mask,v)	_mm_shuffle_<mask>(v)
	#endif
#elif defined(VECLIB_ALTIVEC)
	#include "altivec/f32.h"
	#include "altivec/i32.h"
	#include "altivec/vecf32.h"
#elif defined(__SPU__)
	#include "spu/f32.h"
	#include "spu/i32.h"
	#include "spu/vecf32.h"
#else
	#include "scalar/f32.h"
	#include "scalar/i32.h"
	#include "scalar/vecf32.h"
#endif

	#include "matrix.h"

}

// Include fwk_base.h first if you want serialization support
#ifdef FWK_BASE_H

SERIALIZE_AS_POD(veclib::Vec2<float>)
SERIALIZE_AS_POD(veclib::Vec3<float>)
SERIALIZE_AS_POD(veclib::Vec4<float>)
SERIALIZE_AS_POD(veclib::Vec2<double>)
SERIALIZE_AS_POD(veclib::Vec3<double>)
SERIALIZE_AS_POD(veclib::Vec4<double>)

#endif

/*

For now, from packed types, only f32x4 and i32x4 are implemented.

Basic types -----------------------------------------------------------------------------------
f32		f64		i8		i16		i32		i64		u8		u16		u32		u64
bool

Packed types (SSE) ----------------------------------------------------------------------------
f32x4	f64x2	i8x16	i16x8	i32x4	i64x2	u8x16	u16x8	u32x4	u64x2

Vector templates ------------------------------------------------------------------------------
Vec2< >
Vec3< >
Vec4< >

Packed vector types (SSE) ---------------------------------------------------------------------
pvec2f32	pvec2f64
pvec3f32	pvec3f64
pvec4f32	pvec4f64
vec2f32x4	vec2f64x2
vec3f32x4	vec3f64x2
vec4f32x4	vec4f64x4

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
	Vec3<>(x1, y1, z1) * Vec3<>(x2, y2, z2) == Vec3<>(x1*x2, y1*y2, z1*z2)
Named functions have 'V' prefix, for example:
	VInv( Vec2<>(x, y) ) == Vec2<>( Inv(x), Inv(y) )

Additional vector operations ----------------------------------------------------------------------
|									dot product
^									cross product
Length ( v )						Sqrt ( v|v )


Integer operations --------------------------------------------------------------------------------
+ - * / % | & ^ ~ ++ --
Abs ( v )
Max ( a , b )
Min ( a , b )

Technical functions -------------------------------------------------------------------------------

SignMask ( v )						Returns integer with #n bit set when #n element is < 0

ForAny ( e )						| Returns true if expression if true for any / every element,
ForAll ( e )						| example: if ( ForAll( val1*val2 < val3 ) ) { .. do something .. }
ForWhich ( e )						similar to SignMask, #n bit is set when expression is true for #n element

u64 Ticks ( )						rdtsc cpu instruction
AlignedAlloc ( )					| aligned (to 16 bytes) allocation procedures
AlignedFree ( )						| ..

*/


#endif
