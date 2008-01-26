#ifndef VECLIB_SSEVEC4_H
#define VECLIB_SSEVEC4_H

#include "ssevec.h"
#include "ssepvec.h"
#include "ssereal4.h"

typedef Vec2<SSEReal4> SSEVec24;
typedef Vec3<SSEReal4> SSEVec34;
typedef Vec4<SSEReal4> SSEVec44;

SSEPVec2::operator SSEVec24() const {
	SSEReal4 x(X()),y(Y());
	return SSEVec24(x,y);
}

SSEPVec3::operator SSEVec34() const {
	SSEReal4 x(X()),y(Y()),z(Z());
	return SSEVec34(x,y,z);
}

SSEPVec4::operator SSEVec44() const {
	SSEReal4 x(X()),y(Y()),z(Z()),w(W());
	return SSEVec44(x,y,z,w);
}

INLINE SSEVec24 Condition(const SSEMask4 &test,const SSEVec24 &v1,const SSEVec24 &v2) {
	SSEVec24 out;
	out.X() = Condition(test,v1.X(),v2.X());
	out.Y() = Condition(test,v1.Y(),v2.Y());
	return out;
}
INLINE SSEVec24 Condition(const SSEMaskNeg4 &test,const SSEVec24 &v1,const SSEVec24 &v2) {
	SSEVec24 out;
	out.X() = Condition(test,v1.X(),v2.X());
	out.Y() = Condition(test,v1.Y(),v2.Y());
	return out;
}
INLINE SSEVec24 Condition(const SSEMask4 &test,const SSEVec24 &v1) {
	SSEVec24 out;
	out.X() = Condition(test,v1.X());
	out.Y() = Condition(test,v1.Y());
	return out;
}
INLINE SSEVec24 Condition(const SSEMaskNeg4 &test,const SSEVec24 &v1) {
	SSEVec24 out;
	out.X() = Condition(test,v1.X());
	out.Y() = Condition(test,v1.Y());
	return out;
}

INLINE SSEVec34 Condition(const SSEMask4 &test,const SSEVec34 &v1,const SSEVec34 &v2) {
	SSEVec34 out;
	out.X() = Condition(test,v1.X(),v2.X());
	out.Y() = Condition(test,v1.Y(),v2.Y());
	out.Z() = Condition(test,v1.Z(),v2.Z());
	return out;
}
INLINE SSEVec34 Condition(const SSEMaskNeg4 &test,const SSEVec34 &v1,const SSEVec34 &v2) {
	SSEVec34 out;
	out.X() = Condition(test,v1.X(),v2.X());
	out.Y() = Condition(test,v1.Y(),v2.Y());
	out.Z() = Condition(test,v1.Z(),v2.Z());
	return out;
}
INLINE SSEVec34 Condition(const SSEMask4 &test,const SSEVec34 &v1) {
	SSEVec34 out;
	out.X() = Condition(test,v1.X());
	out.Y() = Condition(test,v1.Y());
	out.Z() = Condition(test,v1.Z());
	return out;
}
INLINE SSEVec34 Condition(const SSEMaskNeg4 &test,const SSEVec34 &v1) {
	SSEVec34 out;
	out.X() = Condition(test,v1.X());
	out.Y() = Condition(test,v1.Y());
	out.Z() = Condition(test,v1.Z());
	return out;
}

INLINE SSEVec44 Condition(const SSEMask4 &test,const SSEVec44 &v1,const SSEVec44 &v2) {
	SSEVec44 out;
	out.X() = Condition(test,v1.X(),v2.X());
	out.Y() = Condition(test,v1.Y(),v2.Y());
	out.Z() = Condition(test,v1.Z(),v2.Z());
	out.W() = Condition(test,v1.W(),v2.W());
	return out;
}
INLINE SSEVec44 Condition(const SSEMaskNeg4 &test,const SSEVec44 &v1,const SSEVec44 &v2) {
	SSEVec44 out;
	out.X() = Condition(test,v1.X(),v2.X());
	out.Y() = Condition(test,v1.Y(),v2.Y());
	out.Z() = Condition(test,v1.Z(),v2.Z());
	out.W() = Condition(test,v1.W(),v2.W());
	return out;
}
INLINE SSEVec44 Condition(const SSEMask4 &test,const SSEVec44 &v1) {
	SSEVec44 out;
	out.X() = Condition(test,v1.X());
	out.Y() = Condition(test,v1.Y());
	out.Z() = Condition(test,v1.Z());
	out.W() = Condition(test,v1.W());
	return out;
}
INLINE SSEVec44 Condition(const SSEMaskNeg4 &test,const SSEVec44 &v1) {
	SSEVec44 out;
	out.X() = Condition(test,v1.X());
	out.Y() = Condition(test,v1.Y());
	out.Z() = Condition(test,v1.Z());
	out.W() = Condition(test,v1.W());
	return out;
}

//INLINE void Broadcast(const SSEVec2 &in,SSEVec24 &out) {
//	out=SSEVec24(SSEReal4(in.X()),SSEReal4(in.Y()));
//}
INLINE void Convert(const SSEVec2 in[4],SSEVec24 &out) {
	Convert(in[0].X(),in[1].X(),in[2].X(),in[3].X(),out.X());
	Convert(in[0].Y(),in[1].Y(),in[2].Y(),in[3].Y(),out.Y());
}
INLINE void Convert(const SSEVec24 &in,SSEVec2 out[4]) {
	Convert(in.X(),out[0].X(),out[1].X(),out[2].X(),out[3].X());
	Convert(in.Y(),out[0].Y(),out[1].Y(),out[2].Y(),out[3].Y());
}
INLINE void Convert(const SSEVec2 &a,const SSEVec2 &b,const SSEVec2 &c,const SSEVec2 &d,SSEVec24 &out) {
	Convert(a.X(),b.X(),c.X(),d.X(),out.X());
	Convert(a.Y(),b.Y(),c.Y(),d.Y(),out.Y());
}
INLINE void Convert(const SSEVec24 &in,SSEVec2 &outA,SSEVec2 &outB,SSEVec2 &outC,SSEVec2 &outD) {
	Convert(in.X(),outA.X(),outB.X(),outC.X(),outD.X());
	Convert(in.Y(),outA.Y(),outB.Y(),outC.Y(),outD.Y());
}


//INLINE void Broadcast(const SSEVec3 &in,SSEVec34 &out) {
//	out=SSEVec34(SSEReal4(in.X()),SSEReal4(in.Y()),SSEReal4(in.Z()));
//}
INLINE void Convert(const SSEVec3 in[4],SSEVec34 &out) {
	Convert(in[0].X(),in[1].X(),in[2].X(),in[3].X(),out.X());
	Convert(in[0].Y(),in[1].Y(),in[2].Y(),in[3].Y(),out.Y());
	Convert(in[0].Z(),in[1].Z(),in[2].Z(),in[3].Z(),out.Z());
}
INLINE void Convert(const SSEVec34 &in,SSEVec3 out[4]) {
	Convert(in.X(),out[0].X(),out[1].X(),out[2].X(),out[3].X());
	Convert(in.Y(),out[0].Y(),out[1].Y(),out[2].Y(),out[3].Y());
	Convert(in.Z(),out[0].Z(),out[1].Z(),out[2].Z(),out[3].Z());
}
INLINE void Convert(const SSEVec3 &a,const SSEVec3 &b,const SSEVec3 &c,const SSEVec3 &d,SSEVec34 &out) {
	Convert(a.X(),b.X(),c.X(),d.X(),out.X());
	Convert(a.Y(),b.Y(),c.Y(),d.Y(),out.Y());
	Convert(a.Z(),b.Z(),c.Z(),d.Z(),out.Z());
}
INLINE void Convert(const SSEVec34 &in,SSEVec3 &outA,SSEVec3 &outB,SSEVec3 &outC,SSEVec3 &outD) {
	Convert(in.X(),outA.X(),outB.X(),outC.X(),outD.X());
	Convert(in.Y(),outA.Y(),outB.Y(),outC.Y(),outD.Y());
	Convert(in.Z(),outA.Z(),outB.Z(),outC.Z(),outD.Z());
}

//INLINE void Broadcast(const SSEVec4 &in,SSEVec44 &out) {
//	out=SSEVec44(SSEReal4(in.X()),SSEReal4(in.Y()),SSEReal4(in.Z()),SSEReal4(in.W()));
//}
INLINE void Convert(const SSEVec4 in[4],SSEVec44 &out) {
	Convert(in[0].X(),in[1].X(),in[2].X(),in[3].X(),out.X());
	Convert(in[0].Y(),in[1].Y(),in[2].Y(),in[3].Y(),out.Y());
	Convert(in[0].Z(),in[1].Z(),in[2].Z(),in[3].Z(),out.Z());
	Convert(in[0].W(),in[1].W(),in[2].W(),in[3].W(),out.W());
}
INLINE void Convert(const SSEVec44 &in,SSEVec4 out[4]) {
	Convert(in.X(),out[0].X(),out[1].X(),out[2].X(),out[3].X());
	Convert(in.Y(),out[0].Y(),out[1].Y(),out[2].Y(),out[3].Y());
	Convert(in.Z(),out[0].Z(),out[1].Z(),out[2].Z(),out[3].Z());
	Convert(in.W(),out[0].W(),out[1].W(),out[2].W(),out[3].W());
}
INLINE void Convert(const SSEVec4 &a,const SSEVec4 &b,const SSEVec4 &c,const SSEVec4 &d,SSEVec44 &out) {
	Convert(a.X(),b.X(),c.X(),d.X(),out.X());
	Convert(a.Y(),b.Y(),c.Y(),d.Y(),out.Y());
	Convert(a.Z(),b.Z(),c.Z(),d.Z(),out.Z());
	Convert(a.W(),b.W(),c.W(),d.W(),out.W());
}
INLINE void Convert(const SSEVec44 &in,SSEVec4 &outA,SSEVec4 &outB,SSEVec4 &outC,SSEVec4 &outD) {
	Convert(in.X(),outA.X(),outB.X(),outC.X(),outD.X());
	Convert(in.Y(),outA.Y(),outB.Y(),outC.Y(),outD.Y());
	Convert(in.Z(),outA.Z(),outB.Z(),outC.Z(),outD.Z());
	Convert(in.W(),outA.W(),outB.W(),outC.W(),outD.W());
}



//INLINE void Broadcast(const Vec3<float> &in,SSEVec34 &out) {
//	SSEVec3 tmp;
//	Broadcast(in,tmp);
//	Broadcast(tmp,out);
//}
INLINE void Convert(const Vec3<float> in[16],SSEVec34 &out) {
	SSEVec3 tmp[4];
	Convert(in+0,tmp[0]);
	Convert(in+4,tmp[1]);
	Convert(in+8,tmp[2]);
	Convert(in+12,tmp[3]);
	Convert(tmp,out);
}
INLINE void Convert(const SSEVec34 &in,Vec3<float> out[16]) {
	SSEVec3 tmp[4];
	Convert(in,tmp);
	Convert(tmp[0],out+0);
	Convert(tmp[1],out+4);
	Convert(tmp[2],out+8);
	Convert(tmp[3],out+12);
}
INLINE void Convert(const Vec3<float> a[4],const Vec3<float> b[4],const Vec3<float> c[4],const Vec3<float> d[4],SSEVec34 &out) {
	SSEVec3 tmp[4];
	Convert(a,tmp[0]);
	Convert(b,tmp[1]);
	Convert(c,tmp[2]);
	Convert(d,tmp[3]);
	Convert(tmp,out);
}
INLINE void Convert(const SSEVec34 &in,Vec3<float> outA[4],Vec3<float> outB[4],Vec3<float> outC[4],Vec3<float> outD[4]) {
	SSEVec3 tmp[4];
	Convert(in,tmp);
	Convert(tmp[0],outA);
	Convert(tmp[1],outB);
	Convert(tmp[2],outC);
	Convert(tmp[3],outD);
}



#endif
