#ifndef VECLIB_SSEPVEC_H
#define VECLIB_SSEPVEC_H

#include "ssevec.h"
#include "ssereal.h"
//#include "ssereal4.h"

// Wektorek 'upakowany'; W przeciwienstwie do VecN<SSEReal> nie zawiera
// N * 4 wartoci, ale jedynie N (pozostale skadowe rejestru SSE sa ignorowane)
// Komponenty sa read-only; bo przy przypisaniu traciloby sie czesc informacji
// Generalnie korzystanie z takich wektorow o N<4 to marnotrastwo mocy


class SSEPVec2;
class SSEPVec3;
class SSEPVec4;

//typedef Vec2<SSEReal4> SSEVec24;
//typedef Vec3<SSEReal4> SSEVec34;
//typedef Vec4<SSEReal4> SSEVec44;

// -----------------------------------------------------------------------------------------------------------
#define CLASS_NAME SSEPVec2
#define ADDITIONAL_CLASS_CODE \
	INLINE explicit SSEPVec2(const SSEPVec3 &v); \
	INLINE explicit SSEPVec2(const SSEPVec4 &v); \
	INLINE SSEPVec2(const SSEPReal &x,const SSEPReal &y) { m=_mm_shuffle(0+(3<<2)+(0<<4)+(3<<6),_mm_shuffle_ps(x.m,y.m,0)); } \
	INLINE SSEPReal X() const { return _mm_shuffle(0,m); } \
	INLINE SSEPReal Y() const { return _mm_shuffle(1+(1<<2)+(1<<4)+(1<<6),m); } \
	INLINE operator SSEVec2() const { SSEVec2 out; out=SSEVec2(X(),Y()); return out; }// \
	INLINE operator SSEVec24() const;


#include "ssepvec_gen.h"

#undef ADDITIONAL_CLASS_CODE
#undef CLASS_NAME
// -----------------------------------------------------------------------------------------------------------
#define CLASS_NAME SSEPVec3
#define ADDITIONAL_CLASS_CODE \
	INLINE explicit SSEPVec3(const SSEPVec2 &v); \
	INLINE explicit SSEPVec3(const SSEPVec4 &v); \
	INLINE SSEPVec3(const SSEPReal &x,const SSEPReal &y,const SSEPReal &z) { \
		m=_mm_shuffle_ps(_mm_shuffle_ps(x.m,y.m,0),z.m,0+(2<<2)+(0<<4)+(0<<6)); \
	} \
	INLINE SSEPReal X() const { return _mm_shuffle(0,m); } \
	INLINE SSEPReal Y() const { return _mm_shuffle(1+(1<<2)+(1<<4)+(1<<6),m); } \
	INLINE SSEPReal Z() const { return _mm_shuffle(2+(2<<2)+(2<<4)+(2<<6),m); } \
	INLINE operator SSEVec3() const { SSEVec3 out; out=SSEVec3(X(),Y(),Z()); return out; }// \
	INLINE operator SSEVec34() const;

#include "ssepvec_gen.h"

#undef ADDITIONAL_CLASS_CODE
#undef CLASS_NAME
// -----------------------------------------------------------------------------------------------------------
#define CLASS_NAME SSEPVec4
#define ADDITIONAL_CLASS_CODE \
	INLINE explicit SSEPVec4(const SSEPVec2 &v) { m=_mm_shuffle_ps(v.m,_mm_setzero_ps(),0+(1<<2)); } \
	INLINE explicit SSEPVec4(const SSEPVec3 &v) { \
		__m128 zzww=_mm_shuffle_ps(v.m,_mm_setzero_ps(),0); \
		m=_mm_shuffle_ps(v.m,zzww,0+(1<<2)+(0<<4)+(2<<6)); \
	} \
	INLINE SSEPVec4(const SSEPReal &x,const SSEPReal &y,const SSEPReal &z,const SSEPReal &w) { \
		__m128 xy=_mm_shuffle_ps(x.m,y.m,0),zw=_mm_shuffle_ps(z.m,w.m,0); \
		m=_mm_shuffle_ps(xy,zw,0+(2<<2)+(0<<4)+(2<<6)); \
	} \
	INLINE SSEPReal X() const { return _mm_shuffle(0,m); } \
	INLINE SSEPReal Y() const { return _mm_shuffle(1+(1<<2)+(1<<4)+(1<<6),m); } \
	INLINE SSEPReal Z() const { return _mm_shuffle(2+(2<<2)+(2<<4)+(2<<6),m); } \
	INLINE SSEPReal W() const { return _mm_shuffle(3+(3<<2)+(3<<4)+(3<<6),m); } \
	INLINE operator SSEVec4() const { SSEVec4 out; out=SSEVec4(X(),Y(),Z(),W()); return out; }// \
	INLINE operator SSEVec44() const;

#include "ssepvec_gen.h"

#undef ADDITIONAL_CLASS_CODE
#undef CLASS_NAME
// -----------------------------------------------------------------------------------------------------------

SSEPVec3::SSEPVec3(const SSEPVec2 &v) { m=_mm_shuffle_ps(v.m,_mm_setzero_ps(),0+(1<<2)); }
SSEPVec3::SSEPVec3(const SSEPVec4 &v) { m=v.m; }
SSEPVec2::SSEPVec2(const SSEPVec3 &v) { m=v.m; }
SSEPVec2::SSEPVec2(const SSEPVec4 &v) { m=v.m; }


INLINE SSEPReal operator|(const SSEPVec2 &a,const SSEPVec2 &b) {
	SSEPReal out;
	__m128 t=_mm_mul_ps(a.m,b.m);
	t=_mm_add_ss(t,_mm_shuffle_ps(t,t,1));
	out.m=_mm_shuffle(0,t);
	return out;
}
INLINE SSEPReal operator|(const SSEPVec3 &a,const SSEPVec3 &b) {
	SSEPReal out;
	__m128 t=_mm_mul_ps(a.m,b.m);
	t=_mm_add_ss(/*Z*/_mm_movehl_ps(t,t),_mm_add_ss(/*X*/t,/*Y*/_mm_shuffle_ps(t,t,1)));
	out.m=_mm_shuffle(0,t);
	return out;
}
INLINE SSEPReal operator|(const SSEPVec4 &a,const SSEPVec4 &b) {
	SSEPReal out;
	__m128 t=_mm_mul_ps(a.m,b.m);
	t=_mm_add_ps(t,_mm_shuffle_ps(t,t,0x4E));
	t=_mm_add_ps(t,_mm_shuffle_ps(t,t,0x11));
	out.m=t; // alredy broadcasted
	return out;
}

INLINE SSEPVec3 operator^(const SSEPVec3 &a,const SSEPVec3 &b)
{
	SSEPVec3 out;

	/*	ay*bz	-	by*az
		az*bx	-	bz*ax
		ax*by	-	bx*ay	*/
	__m128 a1=_mm_shuffle_ps(a.m,a.m,201);	// y,z,x,w
	__m128 b1=_mm_shuffle_ps(b.m,b.m,210);	// z,x,y,w
	__m128 a2=_mm_shuffle_ps(a.m,a.m,210);	// z,x,y,w
	__m128 b2=_mm_shuffle_ps(b.m,b.m,201);	// y,z,x,w

	out.m=_mm_sub_ps(_mm_mul_ps(a1,b1),_mm_mul_ps(a2,b2));;
	return out;
}

INLINE void Convert(const Vec2<float> &v,SSEPVec2 &out)	{ out.m=_mm_load2(&v.X()); }
INLINE void Convert(const float v[2],SSEPVec2 &out)		{ out.m=_mm_load2(v+0); }
INLINE void Convert(const SSEPVec2 &v,Vec2<float> &out)	{ _mm_store2(v.m,&out.X()); }
INLINE void Convert(const SSEPVec2 &v,float out[2])		{ _mm_store2(v.m,out+0); }

INLINE void Convert(const Vec3<float> &v,SSEPVec3 &out)	{ out.m=_mm_load3(&v.X()); }
INLINE void Convert(const float v[3],SSEPVec3 &out)		{ out.m=_mm_load3(v+0); }
INLINE void Convert(const SSEPVec3 &v,Vec3<float> &out)	{ _mm_store3(v.m,&out.X()); }
INLINE void Convert(const SSEPVec3 &v,float out[3])		{ _mm_store3(v.m,out+0); }

INLINE void Convert(const Vec4<float> &v,SSEPVec4 &out)	{ out.m=_mm_load4(&v.X()); }
INLINE void Convert(const float v[4],SSEPVec4 &out)		{ out.m=_mm_load4(v+0); }
INLINE void Convert(const SSEPVec4 &v,Vec4<float> &out)	{ _mm_store4(v.m,&out.X()); }
INLINE void Convert(const SSEPVec4 &v,float out[4])		{ _mm_store4(v.m,out+0); }

INLINE void Convert(const SSEVec3 &in,SSEPVec3 out[4]) {
	_mm_transpose(	in.X().m,in.Y().m,in.Z().m,in.Z().m,
					out[0].m,out[1].m,out[2].m,out[3].m);
}
INLINE void Convert(const SSEPVec3 in[4],SSEVec3 &out) {
	__m128 tmp3, tmp2, tmp1, tmp0;
	tmp0=_mm_shuffle_ps(in[0].m, in[1].m, 0x44);
	tmp2=_mm_shuffle_ps(in[0].m, in[1].m, 0xEE);
	tmp1=_mm_shuffle_ps(in[2].m, in[3].m, 0x44);
	tmp3=_mm_shuffle_ps(in[2].m, in[3].m, 0xEE);

	out.X().m=_mm_shuffle_ps(tmp0, tmp1, 0x88);
	out.Y().m=_mm_shuffle_ps(tmp0, tmp1, 0xDD);
	out.Z().m=_mm_shuffle_ps(tmp2, tmp3, 0x88);
}

INLINE void Convert(const SSEVec4 &in,SSEPVec4 out[4]) {
	_mm_transpose(	in.X().m,in.Y().m,in.Z().m,in.W().m,
					out[0].m,out[1].m,out[2].m,out[3].m);
}
INLINE void Convert(const SSEPVec4 in[4],SSEVec4 &out) {
	__m128 tmp3, tmp2, tmp1, tmp0;
	tmp0=_mm_shuffle_ps(in[0].m, in[1].m, 0x44);
	tmp2=_mm_shuffle_ps(in[0].m, in[1].m, 0xEE);
	tmp1=_mm_shuffle_ps(in[2].m, in[3].m, 0x44);
	tmp3=_mm_shuffle_ps(in[2].m, in[3].m, 0xEE);

	out.X().m=_mm_shuffle_ps(tmp0, tmp1, 0x88);
	out.Y().m=_mm_shuffle_ps(tmp0, tmp1, 0xDD);
	out.Z().m=_mm_shuffle_ps(tmp2, tmp3, 0x88);
	out.W().m=_mm_shuffle_ps(tmp2, tmp3, 0xDD);
}



#endif
