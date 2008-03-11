#if !defined(VECLIB_SSEVEC_H) && VECLIB_SSE_VER>=0x10
#define VECLIB_SSEVEC_H

#include "sse.h"
#include "ssereal.h"
#include "vec4.h"

typedef Vec2<SSEReal> SSEVec2;
typedef Vec3<SSEReal> SSEVec3;
typedef Vec4<SSEReal> SSEVec4;

INLINE SSEVec2 Condition(const SSERealMaskNeg &test,const SSEVec2 &v1,const SSEVec2 &v2) {
	SSEVec2 out;
	out.x = Condition(test,v1.x,v2.x);
	out.y = Condition(test,v1.y,v2.y);
	return out;
}
INLINE SSEVec2 Condition(const SSERealMaskNeg &test,const SSEVec2 &v1) {
	SSEVec2 out;
	out.x = Condition(test,v1.x);
	out.y = Condition(test,v1.y);
	return out;
}

INLINE SSEVec3 Condition(const SSERealMaskNeg &test,const SSEVec3 &v1,const SSEVec3 &v2) {
	SSEVec3 out;
	out.x = Condition(test,v1.x,v2.x);
	out.y = Condition(test,v1.y,v2.y);
	out.z = Condition(test,v1.z,v2.z);
	return out;
}
INLINE SSEVec3 Condition(const SSERealMaskNeg &test,const SSEVec3 &v1) {
	SSEVec3 out;
	out.x = Condition(test,v1.x);
	out.y = Condition(test,v1.y);
	out.z = Condition(test,v1.z);
	return out;
}

INLINE SSEVec4 Condition(const SSERealMaskNeg &test,const SSEVec4 &v1,const SSEVec4 &v2) {
	SSEVec4 out;
	out.x = Condition(test,v1.x,v2.x);
	out.y = Condition(test,v1.y,v2.y);
	out.z = Condition(test,v1.z,v2.z);
	out.w = Condition(test,v1.w,v2.w);
	return out;
}
INLINE SSEVec4 Condition(const SSERealMaskNeg &test,const SSEVec4 &v1) {
	SSEVec4 out;
	out.x = Condition(test,v1.x);
	out.y = Condition(test,v1.y);
	out.z = Condition(test,v1.z);
	out.w = Condition(test,v1.w);
	return out;
}

INLINE void Broadcast(const Vec2<float> &in,SSEVec2 &out) {
	out=SSEVec2(SSEReal(in.x),SSEReal(in.y));
}
INLINE void Convert(const Vec2<float> in[4],SSEVec2 &out) {
	Convert(in[0].x,in[1].x,in[2].x,in[3].x,out.x);
	Convert(in[0].y,in[1].y,in[2].y,in[3].y,out.y);
}
INLINE void Convert(const SSEVec2 &in,Vec2<float> out[4]) {
	Convert(in.x,out[0].x,out[1].x,out[2].x,out[3].x);
	Convert(in.y,out[0].y,out[1].y,out[2].y,out[3].y);
}
INLINE void Convert(const Vec2<float> &a,const Vec2<float> &b,const Vec2<float> &c,const Vec2<float> &d,SSEVec2 &out) {
	Convert(a.x,b.x,c.x,d.x,out.x);
	Convert(a.y,b.y,c.y,d.y,out.y);
}
INLINE void Convert(const SSEVec2 &in,Vec2<float> &outA,Vec2<float> &outB,Vec2<float> &outC,Vec2<float> &outD) {
	Convert(in.x,outA.x,outB.x,outC.x,outD.x);
	Convert(in.y,outA.y,outB.y,outC.y,outD.y);
}


INLINE void Broadcast(const Vec3<float> &in,SSEVec3 &out) {
	out=SSEVec3(SSEReal(in.x),SSEReal(in.y),SSEReal(in.z));
}
INLINE void Convert(const Vec3<float> in[4],SSEVec3 &out) {
	Convert(in[0].x,in[1].x,in[2].x,in[3].x,out.x);
	Convert(in[0].y,in[1].y,in[2].y,in[3].y,out.y);
	Convert(in[0].z,in[1].z,in[2].z,in[3].z,out.z);
}
INLINE void Convert(const SSEVec3 &in,Vec3<float> out[4]) {
	Convert(in.x,out[0].x,out[1].x,out[2].x,out[3].x);
	Convert(in.y,out[0].y,out[1].y,out[2].y,out[3].y);
	Convert(in.z,out[0].z,out[1].z,out[2].z,out[3].z);
}
INLINE void Convert(const Vec3<float> &a,const Vec3<float> &b,const Vec3<float> &c,const Vec3<float> &d,SSEVec3 &out) {
	Convert(a.x,b.x,c.x,d.x,out.x);
	Convert(a.y,b.y,c.y,d.y,out.y);
	Convert(a.z,b.z,c.z,d.z,out.z);
}
INLINE void Convert(const SSEVec3 &in,Vec3<float> &outA,Vec3<float> &outB,Vec3<float> &outC,Vec3<float> &outD) {
	Convert(in.x,outA.x,outB.x,outC.x,outD.x);
	Convert(in.y,outA.y,outB.y,outC.y,outD.y);
	Convert(in.z,outA.z,outB.z,outC.z,outD.z);
}

INLINE void Broadcast(const Vec4<float> &in,SSEVec4 &out) {
	out=SSEVec4(SSEReal(in.x),SSEReal(in.y),SSEReal(in.z),SSEReal(in.w));
}
INLINE void Convert(const Vec4<float> in[4],SSEVec4 &out) {
	Convert(in[0].x,in[1].x,in[2].x,in[3].x,out.x);
	Convert(in[0].y,in[1].y,in[2].y,in[3].y,out.y);
	Convert(in[0].z,in[1].z,in[2].z,in[3].z,out.z);
	Convert(in[0].w,in[1].w,in[2].w,in[3].w,out.w);
}
INLINE void Convert(const SSEVec4 &in,Vec4<float> out[4]) {
	Convert(in.x,out[0].x,out[1].x,out[2].x,out[3].x);
	Convert(in.y,out[0].y,out[1].y,out[2].y,out[3].y);
	Convert(in.z,out[0].z,out[1].z,out[2].z,out[3].z);
	Convert(in.w,out[0].w,out[1].w,out[2].w,out[3].w);
}
INLINE void Convert(const Vec4<float> &a,const Vec4<float> &b,const Vec4<float> &c,const Vec4<float> &d,SSEVec4 &out) {
	// Wolne, zrobic transpozycje
	Convert(a.x,b.x,c.x,d.x,out.x);
	Convert(a.y,b.y,c.y,d.y,out.y);
	Convert(a.z,b.z,c.z,d.z,out.z);
	Convert(a.w,b.w,c.w,d.w,out.w);
}
INLINE void Convert(const SSEVec4 &in,Vec4<float> &outA,Vec4<float> &outB,Vec4<float> &outC,Vec4<float> &outD) {
	// Tak samo jak wyzej
	Convert(in.x,outA.x,outB.x,outC.x,outD.x);
	Convert(in.y,outA.y,outB.y,outC.y,outD.y);
	Convert(in.z,outA.z,outB.z,outC.z,outD.z);
	Convert(in.w,outA.w,outB.w,outC.w,outD.w);
}


#endif
