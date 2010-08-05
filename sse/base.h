#ifndef VECLIB_SSE_BASE_H
#define VECLIB_SSE_BASE_H

#include "vecbase.h"


template <unsigned mask>
__m128 _mm_shuffle_(__m128 v) {
	return _mm_shuffle_ps(v,v,mask);
}

#define _mm_shuffle(mask,v)	_mm_shuffle_<mask>(v)

inline __m128 _mm_load4a(const float arr[4]) {
	return _mm_load_ps(arr);
}

// float x,y,z,w -> __m128(x,y,z,w)
inline __m128 _mm_load4(const float arr[4]) {
	return _mm_loadu_ps(arr);
}

inline void _mm_store4a(__m128 v,float arr[4]) { _mm_store_ps(arr,v); }
inline void _mm_store4(__m128 v,float arr[4]) { _mm_storeu_ps(arr,v); }


/// float x,y,z	-> __m128(x,y,z,z)
inline __m128 _mm_load3(const float arr[3]) {
	return _mm_shuffle_ps(
			_mm_shuffle_ps(
				_mm_load_ss(arr+0),
				_mm_load_ss(arr+1),0 ),
			_mm_load_ss(arr+2),
			0 + (2 << 2) + (0 << 4) + (0 << 6) ); 
}
/// float x,y,z	-> __m128(x,y,z,z)
inline __m128 _mm_load3(float a,float b,float c) {
	return _mm_shuffle_ps(
			_mm_shuffle_ps(
				_mm_load_ss(&a),
				_mm_load_ss(&b),0 ),
			_mm_load_ss(&c),
			0+(2<<2)+(0<<4)+(0<<6) ); 
}
/// __m128(x,y,z,b) -> float x,y,z
inline void _mm_store3(__m128 v,float arr[3]) {
	_mm_store_ss(arr+0,v);
	_mm_store_ss(arr+1,_mm_shuffle_ps(v,v,1));
	_mm_store_ss(arr+2,_mm_shuffle_ps(v,v,2));
}

/// float x,y	-> __m128(x,y,x,y)
inline __m128 _mm_load2(const float arr[2]) {
	__m128 tmp = _mm_shuffle_ps(_mm_load_ss(arr + 0), _mm_load_ss(arr + 1), 0);
	return _mm_shuffle_ps(tmp, tmp, 0 + (3 << 2) + (0 << 4) + (3 << 6)); 
}
/// float x,y	-> __m128(x,y,x,y)
inline __m128 _mm_load2(float a, float b) {
	__m128 out;
	out=_mm_shuffle_ps(_mm_load_ss(&a), _mm_load_ss(&b), 0);
	out=_mm_shuffle_ps(out, out, 0 + (3 << 2) + (0 << 4) + (3 << 6)); 
	return out;
}
/// __m128(x,y,a,b) -> float x,y
inline void _mm_store2(__m128 v, float arr[2]) {
	_mm_store_ss(arr+0,v);
	_mm_store_ss(arr+1,_mm_shuffle_ps(v,v,1));
}

/// float x	-> __m128(x,x,x,x)
inline __m128 _mm_load1(float v) {
	__m128 out;
	out=_mm_load_ss(&v);
	out=_mm_shuffle_ps(out,out,0);
	return out;
}
/// __m128(x,a,b,c) -> float x
inline float _mm_store1(__m128 v) {
	float out;
	_mm_store_ss(&out,v);
	return out;
}

inline __m128 _mm_nrrcp_ps(__m128 v) {
	__m128 t=_mm_rcp_ps(v);
	return _mm_sub_ps(_mm_add_ps(t,t), _mm_mul_ps(_mm_mul_ps(v,t), t));
}
inline __m128 _mm_nrrsqrt_ps(__m128 v) {
	__m128 t=_mm_rsqrt_ps(v);
	return _mm_mul_ps(	_mm_mul_ps(_mm_set1_ps(0.5f),t),
						_mm_sub_ps(_mm_set1_ps(3.0f),_mm_mul_ps(_mm_mul_ps(v,t),t)) );
}

inline __m128 _mm_bool2mask(bool v) {
	return _mm_set1_ps(BitCast<float,u32>(v?0xffffffff : 0));
}


inline void _mm_transpose(__m128 x, __m128 y, __m128 z, __m128 w,
			   __m128 &ox, __m128 &oy, __m128 &oz, __m128 &ow)
{
	__m128 tmp3, tmp2, tmp1, tmp0;
	tmp0 = _mm_shuffle_ps(x, y, 0x44);
	tmp2 = _mm_shuffle_ps(x, y, 0xEE);
	tmp1 = _mm_shuffle_ps(z, w, 0x44);
	tmp3 = _mm_shuffle_ps(z, w, 0xEE);

	ox = _mm_shuffle_ps(tmp0, tmp1, 0x88);
	oy = _mm_shuffle_ps(tmp0, tmp1, 0xDD);
	oz = _mm_shuffle_ps(tmp2, tmp3, 0x88);
	ow = _mm_shuffle_ps(tmp2, tmp3, 0xDD);
}

inline void _mm_transpose(__m128 &x,__m128 &y,__m128 &z,__m128 &w) {
	_mm_transpose(x, y, z, w, x, y, z, w);
}

#endif
