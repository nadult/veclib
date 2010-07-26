#ifndef VECLIB_VECLIB_CONF_H
#define VECLIB_VECLIB_CONF_H

#ifdef INLINE
	#undef INLINE
#endif

#ifndef __GNUC__
	#error "Compiler not supported :/"
#elif defined(__GNUC__) || defined(__ICC)
#else
	#error "Compiler not supported :/"
#endif
	
#define INLINE __inline__
#define VECLIB_DECL_ALIGNED_FLOAT(name,size)    float name[size] __attribute__ ((aligned (16)));

// You can define it yourself if you like :)
#ifndef VECLIB_SSE_VER

	#ifdef __SSSE3__
		#define VECLIB_SSE_VER 0x31
	#elif __SSE3__
		#define VECLIB_SSE_VER 0x30
	#elif __SSE2__
		#define VECLIB_SSE_VER 0x20
	#elif __SSE__
		#define VECLIB_SSE_VER 0x10
	#endif

#endif

#if defined(__x86_64)
	#define VECLIB_X86		0x64
#elif defined(__i386)
	#define VECLIB_X86		0x32
#elif defined(__PPC)
	#define VECLIB_PPC		1
#else
	#error "Architecture not supported"
#endif

#endif

