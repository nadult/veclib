#ifndef VECLIB_VECLIB_CONF_H
#define VECLIB_VECLIB_CONF_H

#ifdef INLINE
	#undef INLINE
#endif

#ifdef _MSC_VER
	#define VECLIB_MSVC_STYLE
	#define INLINE __forceinline
    #define VECLIB_DECL_ALIGNED_FLOAT(name,size)    __declspec(align(16)) float name[size];
#elif defined(__GNUC__) || defined(__ICC)
	#define VECLIB_GCC_STYLE
	#define INLINE __inline__
    #define VECLIB_DECL_ALIGNED_FLOAT(name,size)    float name[size] __attribute__ ((aligned (16)));
#else
	#error "Compiler not supported :/"
#endif

// You can define it yourself if you like :)
#ifndef VECLIB_SSE_VER

	#ifdef VECLIB_MSVC_STYLE

		#if _M_IX86_FP>=2
			#define VECLIB_SSE_VER 0x20
		#elif _M_IX86_FP>=1
			#define VECLIB_SSE_VER 0x10
		#else
			#define VECLIB_SSE_VER 0x00
		#endif

	#elif defined(VECLIB_GCC_STYLE)

		#ifdef __SSSE3__
			#define VECLIB_SSE_VER 0x31
		#elif __SSE3__
			#define VECLIB_SSE_VER 0x30
		#elif __SSE2__
			#define VECLIB_SSE_VER 0x20
		#elif __SSE__
			#define VECLIB_SSE_VER 0x10
		#else
			#define VECLIB_SSE_VER 0x00
		#endif

	#else
		#define VECLIB_SSE_VER 0x00 
	#endif

#endif

// Only X86 (==0x32) and AMD64 (==0x64) supported (for now)
#ifndef VECLIB_ARCH

	#ifdef VECLIB_MSVC_STYLE

		#if defined(_M_X64)
			#define VECLIB_ARCH		0x64
		#elif defined(_M_IX86)
			#define VECLIB_ARCH		0x32
		#else
			#error "Architecture not supported"
		#endif
	
	#elif defined(VECLIB_GCC_STYLE)

		#if defined(__x86_64)
			#define VECLIB_ARCH		0x64
		#elif defined(__i386)
			#define VECLIB_ARCH		0x32
		#else
			#error "Architecture not supported"
		#endif

	#endif

#endif



#endif

