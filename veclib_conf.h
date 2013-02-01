#ifndef VECLIB_VECLIB_CONF_H
#define VECLIB_VECLIB_CONF_H

#ifdef INLINE
	#undef INLINE
#endif

#ifndef __GNUC__
//	#error "Only GCC is supported so far :/"
#endif
	
#define INLINE __inline__

// You can define it yourself if you like :)
#ifndef VECLIB_SSE

	#ifdef __SSSE3__
		#define VECLIB_SSE 0x31
	#elif __SSE3__
		#define VECLIB_SSE 0x30
	#elif __SSE2__
		#define VECLIB_SSE 0x20
	#elif __SSE__
		#define VECLIB_SSE 0x10
	#endif

#endif

#ifndef VECLIB_ALTIVEC

#ifndef __IBMCPP__
	#ifdef __ALTIVEC__
		#define VECLIB_ALTIVEC 0x10
	#endif
#endif

#endif

#if defined(__x86_64)
	#define VECLIB_X86		0x64
#elif defined(__i386)
	#define VECLIB_X86		0x32
#elif defined(__PPC64__)
	#define VECLIB_PPC		0x64
#elif defined(__PPC) || defined(__PPC__)
	#define VECLIB_PPC		0x32
#elif defined(__SPU__)
	#define VECLIB_SPU		0x32
#else
	#error "Architecture not supported"
#endif

#endif

