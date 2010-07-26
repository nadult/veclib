#ifndef VECLIB_VECLIBALL_H
#define VECLIB_VECLIBALL_H

namespace veclib
{

	#include "vecbase.h"
	#include "vec2.h"
	#include "vec3.h"
	#include "vec4.h"

#ifdef VECLIB_SSE_VER
	#include "sse/f32.h"
	#include "sse/vecf32.h"
	#include "sse/i32.h"
	#ifndef _mm_shuffle
		#define _mm_shuffle(mask,v)	_mm_shuffle_<mask>(v)
	#endif
//#elif defined(VECLIB_PPC)
//	#include "altivecf32.h"
//	#include "altiveci32.h"
//	#include "altivecvecf32.h"
#else
	#include "scalar/f32.h"
	#include "scalar/i32.h"
	#include "scalar/vecf32.h"
#endif

	#include "matrix.h"

}

#endif
