#ifndef VECLIB_VECLIBALL_H
#define VECLIB_VECLIBALL_H

namespace veclib
{

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

#endif
