#if !defined(VECLIB_SSEVEC_H) && VECLIB_SSE_VER>=0x10
#define VECLIB_SSEVEC_H

#include "sse.h"
#include "ssereal.h"
#include "vec4.h"

typedef Vec2<SSEReal> SSEVec2;
typedef Vec3<SSEReal> SSEVec3;
typedef Vec4<SSEReal> SSEVec4;

INLINE SSEVec2 Condition(const SSERealMask &test,const SSEVec2 &v1,const SSEVec2 &v2) {
	SSEVec2 out;
	out.X() = Condition(test,v1.X(),v2.X());
	out.Y() = Condition(test,v1.Y(),v2.Y());
	return out;
}
INLINE SSEVec2 Condition(const SSERealMaskNeg &test,const SSEVec2 &v1,const SSEVec2 &v2) {
	SSEVec2 out;
	out.X() = Condition(test,v1.X(),v2.X());
	out.Y() = Condition(test,v1.Y(),v2.Y());
	return out;
}
INLINE SSEVec2 Condition(const SSERealMask &test,const SSEVec2 &v1) {
	SSEVec2 out;
	out.X() = Condition(test,v1.X());
	out.Y() = Condition(test,v1.Y());
	return out;
}
INLINE SSEVec2 Condition(const SSERealMaskNeg &test,const SSEVec2 &v1) {
	SSEVec2 out;
	out.X() = Condition(test,v1.X());
	out.Y() = Condition(test,v1.Y());
	return out;
}

INLINE SSEVec3 Condition(const SSERealMask &test,const SSEVec3 &v1,const SSEVec3 &v2) {
	SSEVec3 out;
	out.X() = Condition(test,v1.X(),v2.X());
	out.Y() = Condition(test,v1.Y(),v2.Y());
	out.Z() = Condition(test,v1.Z(),v2.Z());
	return out;
}
INLINE SSEVec3 Condition(const SSERealMaskNeg &test,const SSEVec3 &v1,const SSEVec3 &v2) {
	SSEVec3 out;
	out.X() = Condition(test,v1.X(),v2.X());
	out.Y() = Condition(test,v1.Y(),v2.Y());
	out.Z() = Condition(test,v1.Z(),v2.Z());
	return out;
}
INLINE SSEVec3 Condition(const SSERealMask &test,const SSEVec3 &v1) {
	SSEVec3 out;
	out.X() = Condition(test,v1.X());
	out.Y() = Condition(test,v1.Y());
	out.Z() = Condition(test,v1.Z());
	return out;
}
INLINE SSEVec3 Condition(const SSERealMaskNeg &test,const SSEVec3 &v1) {
	SSEVec3 out;
	out.X() = Condition(test,v1.X());
	out.Y() = Condition(test,v1.Y());
	out.Z() = Condition(test,v1.Z());
	return out;
}

INLINE SSEVec4 Condition(const SSERealMask &test,const SSEVec4 &v1,const SSEVec4 &v2) {
	SSEVec4 out;
	out.X() = Condition(test,v1.X(),v2.X());
	out.Y() = Condition(test,v1.Y(),v2.Y());
	out.Z() = Condition(test,v1.Z(),v2.Z());
	out.W() = Condition(test,v1.W(),v2.W());
	return out;
}
INLINE SSEVec4 Condition(const SSERealMaskNeg &test,const SSEVec4 &v1,const SSEVec4 &v2) {
	SSEVec4 out;
	out.X() = Condition(test,v1.X(),v2.X());
	out.Y() = Condition(test,v1.Y(),v2.Y());
	out.Z() = Condition(test,v1.Z(),v2.Z());
	out.W() = Condition(test,v1.W(),v2.W());
	return out;
}
INLINE SSEVec4 Condition(const SSERealMask &test,const SSEVec4 &v1) {
	SSEVec4 out;
	out.X() = Condition(test,v1.X());
	out.Y() = Condition(test,v1.Y());
	out.Z() = Condition(test,v1.Z());
	out.W() = Condition(test,v1.W());
	return out;
}
INLINE SSEVec4 Condition(const SSERealMaskNeg &test,const SSEVec4 &v1) {
	SSEVec4 out;
	out.X() = Condition(test,v1.X());
	out.Y() = Condition(test,v1.Y());
	out.Z() = Condition(test,v1.Z());
	out.W() = Condition(test,v1.W());
	return out;
}


INLINE void Broadcast(const Vec2<float> &in,SSEVec2 &out) {
	out=SSEVec2(SSEReal(in.X()),SSEReal(in.Y()));
}
INLINE void Convert(const Vec2<float> in[4],SSEVec2 &out) {
	Convert(in[0].X(),in[1].X(),in[2].X(),in[3].X(),out.X());
	Convert(in[0].Y(),in[1].Y(),in[2].Y(),in[3].Y(),out.Y());
}
INLINE void Convert(const SSEVec2 &in,Vec2<float> out[4]) {
	Convert(in.X(),out[0].X(),out[1].X(),out[2].X(),out[3].X());
	Convert(in.Y(),out[0].Y(),out[1].Y(),out[2].Y(),out[3].Y());
}
INLINE void Convert(const Vec2<float> &a,const Vec2<float> &b,const Vec2<float> &c,const Vec2<float> &d,SSEVec2 &out) {
	Convert(a.X(),b.X(),c.X(),d.X(),out.X());
	Convert(a.Y(),b.Y(),c.Y(),d.Y(),out.Y());
}
INLINE void Convert(const SSEVec2 &in,Vec2<float> &outA,Vec2<float> &outB,Vec2<float> &outC,Vec2<float> &outD) {
	Convert(in.X(),outA.X(),outB.X(),outC.X(),outD.X());
	Convert(in.Y(),outA.Y(),outB.Y(),outC.Y(),outD.Y());
}


INLINE void Broadcast(const Vec3<float> &in,SSEVec3 &out) {
	out=SSEVec3(SSEReal(in.X()),SSEReal(in.Y()),SSEReal(in.Z()));
}
INLINE void Convert(const Vec3<float> in[4],SSEVec3 &out) {
	Convert(in[0].X(),in[1].X(),in[2].X(),in[3].X(),out.X());
	Convert(in[0].Y(),in[1].Y(),in[2].Y(),in[3].Y(),out.Y());
	Convert(in[0].Z(),in[1].Z(),in[2].Z(),in[3].Z(),out.Z());
}
INLINE void Convert(const SSEVec3 &in,Vec3<float> out[4]) {
	Convert(in.X(),out[0].X(),out[1].X(),out[2].X(),out[3].X());
	Convert(in.Y(),out[0].Y(),out[1].Y(),out[2].Y(),out[3].Y());
	Convert(in.Z(),out[0].Z(),out[1].Z(),out[2].Z(),out[3].Z());
}
INLINE void Convert(const Vec3<float> &a,const Vec3<float> &b,const Vec3<float> &c,const Vec3<float> &d,SSEVec3 &out) {
	Convert(a.X(),b.X(),c.X(),d.X(),out.X());
	Convert(a.Y(),b.Y(),c.Y(),d.Y(),out.Y());
	Convert(a.Z(),b.Z(),c.Z(),d.Z(),out.Z());
}
INLINE void Convert(const SSEVec3 &in,Vec3<float> &outA,Vec3<float> &outB,Vec3<float> &outC,Vec3<float> &outD) {
	Convert(in.X(),outA.X(),outB.X(),outC.X(),outD.X());
	Convert(in.Y(),outA.Y(),outB.Y(),outC.Y(),outD.Y());
	Convert(in.Z(),outA.Z(),outB.Z(),outC.Z(),outD.Z());
}

INLINE void Broadcast(const Vec4<float> &in,SSEVec4 &out) {
	out=SSEVec4(SSEReal(in.X()),SSEReal(in.Y()),SSEReal(in.Z()),SSEReal(in.W()));
}
INLINE void Convert(const Vec4<float> in[4],SSEVec4 &out) {
	Convert(in[0].X(),in[1].X(),in[2].X(),in[3].X(),out.X());
	Convert(in[0].Y(),in[1].Y(),in[2].Y(),in[3].Y(),out.Y());
	Convert(in[0].Z(),in[1].Z(),in[2].Z(),in[3].Z(),out.Z());
	Convert(in[0].W(),in[1].W(),in[2].W(),in[3].W(),out.W());
}
INLINE void Convert(const SSEVec4 &in,Vec4<float> out[4]) {
	Convert(in.X(),out[0].X(),out[1].X(),out[2].X(),out[3].X());
	Convert(in.Y(),out[0].Y(),out[1].Y(),out[2].Y(),out[3].Y());
	Convert(in.Z(),out[0].Z(),out[1].Z(),out[2].Z(),out[3].Z());
	Convert(in.W(),out[0].W(),out[1].W(),out[2].W(),out[3].W());
}
INLINE void Convert(const Vec4<float> &a,const Vec4<float> &b,const Vec4<float> &c,const Vec4<float> &d,SSEVec4 &out) {
	Convert(a.X(),b.X(),c.X(),d.X(),out.X());
	Convert(a.Y(),b.Y(),c.Y(),d.Y(),out.Y());
	Convert(a.Z(),b.Z(),c.Z(),d.Z(),out.Z());
	Convert(a.W(),b.W(),c.W(),d.W(),out.W());
}
INLINE void Convert(const SSEVec4 &in,Vec4<float> &outA,Vec4<float> &outB,Vec4<float> &outC,Vec4<float> &outD) {
	Convert(in.X(),outA.X(),outB.X(),outC.X(),outD.X());
	Convert(in.Y(),outA.Y(),outB.Y(),outC.Y(),outD.Y());
	Convert(in.Z(),outA.Z(),outB.Z(),outC.Z(),outD.Z());
	Convert(in.W(),outA.W(),outB.W(),outC.W(),outD.W());
}


#endif
