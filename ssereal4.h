#ifndef VECLIB_SSEREAL4_H
#define VECLIB_SSEREAL4_H

#include "sse.h"
#include "ssereal.h"

class SSEMask4;

class SSEReal4
{
public:
	typedef SSEMask4 TBool;

	INLINE SSEReal4() { }
	INLINE SSEReal4(const __m128 &v0,const __m128 &v1,const __m128 &v2,const __m128 &v3) { m[0]=v0; m[1]=v1; m[2]=v2; m[3]=v3; }
	INLINE SSEReal4(const __m128 &v) { m[0]=v; m[1]=v; m[2]=v; m[3]=v; }
	INLINE SSEReal4(float v) { m[0]=m[1]=m[2]=m[3]=_mm_set1_ps(v); }
	INLINE SSEReal4(const SSEReal &v) { m[0]=m[1]=m[2]=m[3]=v.m; }
	INLINE SSEReal4(const SSEPReal &v) { m[0]=m[1]=m[2]=m[3]=v.m; }

#define GEN_SOP(sop,mmname) \
	INLINE const SSEReal4 &operator sop(const SSEReal4 &v) { \
		m[0]=mmname(m[0],v.m[0]); \
		m[1]=mmname(m[1],v.m[1]); \
		m[2]=mmname(m[2],v.m[2]); \
		m[3]=mmname(m[3],v.m[3]); \
		return *this; \
	}

	GEN_SOP(+=,_mm_add_ps)
	GEN_SOP(-=,_mm_sub_ps)
	GEN_SOP(*=,_mm_mul_ps)
	GEN_SOP(/=,_mm_div_ps)

#undef GEN_SOP

	INLINE SSEReal4 operator-() const {
		SSEReal4 out;
		__m128 zero=_mm_setzero_ps();
		out.m[0]=_mm_sub_ps(zero,m[0]);
		out.m[1]=_mm_sub_ps(zero,m[1]);
		out.m[2]=_mm_sub_ps(zero,m[2]);
		out.m[3]=_mm_sub_ps(zero,m[3]);
		return out;
	}
	INLINE SSEReal4(const float *ptr) {
		m[0]=_mm_load_ps(ptr+0);
		m[1]=_mm_load_ps(ptr+4);
		m[2]=_mm_load_ps(ptr+8);
		m[3]=_mm_load_ps(ptr+12);
	}

	__m128 m[4];
};

#include "ssemask4.h"

#define GEN_CMP_OP(op,mmname) \
	INLINE SSEMask4 operator op(const SSEReal4 &a,const SSEReal4 &b) { \
		SSEMask4 out; \
		out.m[0]=mmname(a.m[0],b.m[0]); \
		out.m[1]=mmname(a.m[1],b.m[1]); \
		out.m[2]=mmname(a.m[2],b.m[2]); \
		out.m[3]=mmname(a.m[3],b.m[3]); \
		return out; \
	}
#define GEN_OP(op,sop) \
	INLINE SSEReal4 operator op(const SSEReal4 &a,const SSEReal4 &b) { \
		SSEReal4 out(a); \
		out sop b; \
		return out; \
	}
#define GEN_FUNC(name,mmname) \
	INLINE SSEReal4 name(const SSEReal4 &v) { \
		SSEReal4 out; \
		out.m[0]=mmname(v.m[0]); \
		out.m[1]=mmname(v.m[1]); \
		out.m[2]=mmname(v.m[2]); \
		out.m[3]=mmname(v.m[3]); \
		return out; \
	}

GEN_CMP_OP(==,_mm_cmpeq_ps)
GEN_CMP_OP(!=,_mm_cmpneq_ps)
GEN_CMP_OP(<=,_mm_cmple_ps)
GEN_CMP_OP(>=,_mm_cmpge_ps)
GEN_CMP_OP(<,_mm_cmplt_ps)
GEN_CMP_OP(>,_mm_cmpgt_ps)

GEN_OP(+,+=)
GEN_OP(-,-=)
GEN_OP(*,*=)
GEN_OP(/,/=)

GEN_FUNC(Sqrt,_mm_sqrt_ps)
GEN_FUNC(Inv,_mm_nrrcp_ps)
GEN_FUNC(RSqrt,_mm_nrrsqrt_ps)
GEN_FUNC(FastInv,_mm_rcp_ps)
GEN_FUNC(FastRSqrt,_mm_rsqrt_ps)

#undef GEN_OP
#undef GEN_CMP_OP
#undef GEN_FUNC


template <int m,int n> class Const<SSEReal4,m,n> {
public:
	INLINE static SSEReal4 Value() { return SSEReal4(Const<__m128,m,n>::Value()); }
};

INLINE SSEReal4 Abs(const SSEReal4 &v) {
	SSEReal4 out;
	out.m[0]=_mm_and_ps(Const<SSEMask,0x7fffffff>::Value().m,v.m[0]);
	out.m[1]=_mm_and_ps(Const<SSEMask,0x7fffffff>::Value().m,v.m[1]);
	out.m[2]=_mm_and_ps(Const<SSEMask,0x7fffffff>::Value().m,v.m[2]);
	out.m[3]=_mm_and_ps(Const<SSEMask,0x7fffffff>::Value().m,v.m[3]);
	return out;
}
INLINE SSEReal4 Min(const SSEReal4 &a,const SSEReal4 &b) {
	SSEReal4 out;
	out.m[0]=_mm_min_ps(a.m[0],b.m[0]);
	out.m[1]=_mm_min_ps(a.m[1],b.m[1]);
	out.m[2]=_mm_min_ps(a.m[2],b.m[2]);
	out.m[3]=_mm_min_ps(a.m[3],b.m[3]);
	return out;
}
INLINE SSEReal4 Max(const SSEReal4 &a,const SSEReal4 &b) {
	SSEReal4 out;
	out.m[0]=_mm_max_ps(a.m[0],b.m[0]);
	out.m[1]=_mm_max_ps(a.m[1],b.m[1]);
	out.m[2]=_mm_max_ps(a.m[2],b.m[2]);
	out.m[3]=_mm_max_ps(a.m[3],b.m[3]);
	return out;
}

INLINE int SignMask(const SSEReal4 &v) {
	return	(_mm_movemask_ps(v.m[0])<<0)+
			(_mm_movemask_ps(v.m[1])<<4)+
			(_mm_movemask_ps(v.m[2])<<8)+
			(_mm_movemask_ps(v.m[3])<<12);
}

INLINE SSEReal4 Condition(const SSEMask4 &test,const SSEReal4 &v1,const SSEReal4 &v2) {
	SSEReal4 out;
	out.m[0]=_mm_or_ps(_mm_and_ps(test.m[0],v1.m[0]),_mm_andnot_ps(test.m[0],v2.m[0]));
	out.m[1]=_mm_or_ps(_mm_and_ps(test.m[1],v1.m[1]),_mm_andnot_ps(test.m[1],v2.m[1]));
	out.m[2]=_mm_or_ps(_mm_and_ps(test.m[2],v1.m[2]),_mm_andnot_ps(test.m[2],v2.m[2]));
	out.m[3]=_mm_or_ps(_mm_and_ps(test.m[3],v1.m[3]),_mm_andnot_ps(test.m[3],v2.m[3]));
	return out;
}
INLINE SSEReal4 Condition(const SSEMaskNeg4 &test,const SSEReal4 &v1,const SSEReal4 &v2) {
	SSEReal4 out;
	out.m[0]=_mm_or_ps(_mm_andnot_ps(test.m[0],v1.m[0]),_mm_and_ps(test.m[0],v2.m[0]));
	out.m[1]=_mm_or_ps(_mm_andnot_ps(test.m[1],v1.m[1]),_mm_and_ps(test.m[1],v2.m[1]));
	out.m[2]=_mm_or_ps(_mm_andnot_ps(test.m[2],v1.m[2]),_mm_and_ps(test.m[2],v2.m[2]));
	out.m[3]=_mm_or_ps(_mm_andnot_ps(test.m[3],v1.m[3]),_mm_and_ps(test.m[3],v2.m[3]));
	return out;
}
INLINE SSEReal4 Condition(const SSEMask4 &test,const SSEReal4 &v1) {
	SSEReal4 out;
	out.m[0]=_mm_and_ps(test.m[0],v1.m[0]);
	out.m[1]=_mm_and_ps(test.m[1],v1.m[1]);
	out.m[2]=_mm_and_ps(test.m[2],v1.m[2]);
	out.m[3]=_mm_and_ps(test.m[3],v1.m[3]);
	return out;
}
INLINE SSEReal4 Condition(const SSEMaskNeg4 &test,const SSEReal4 &v1) {
	SSEReal4 out;
	out.m[0]=_mm_andnot_ps(test.m[0],v1.m[0]);
	out.m[1]=_mm_andnot_ps(test.m[1],v1.m[1]);
	out.m[2]=_mm_andnot_ps(test.m[2],v1.m[2]);
	out.m[3]=_mm_andnot_ps(test.m[3],v1.m[3]);
	return out;
}



template <>
struct ScalarInfo<SSEReal4> {
	enum { Multiplicity=16 };
	typedef SSEMask4 TBool;

	INLINE static SSEMask4 ElementMask(int n) {
		static __m128 elems[4]={
			_mm_set_ps(UValue(0).f,UValue(0).f,UValue(0).f,UValue(0xffffffff).f),
			_mm_set_ps(UValue(0).f,UValue(0).f,UValue(0xffffffff).f,UValue(0).f),
			_mm_set_ps(UValue(0).f,UValue(0xffffffff).f,UValue(0).f,UValue(0).f),
			_mm_set_ps(UValue(0xffffffff).f,UValue(0).f,UValue(0).f,UValue(0).f),
		};

		int t=n>>2;
		__m128 zero=_mm_setzero_ps(),val=elems[n&3];

		SSEMask4 out;
		out.m[0]=t==0?val:zero;
		out.m[1]=t==1?val:zero;
		out.m[2]=t==2?val:zero;
		out.m[3]=t==3?val:zero;
		return out;
	}
};

INLINE void Broadcast(const float &in,SSEReal4 &out) {
	out.m[0]=out.m[1]=out.m[2]=out.m[3]=_mm_load1(in);
}
INLINE void Convert(const float in[16],SSEReal4 &out) {
	out.m[0]=_mm_load4(in+0);
	out.m[1]=_mm_load4(in+4);
	out.m[2]=_mm_load4(in+8);
	out.m[3]=_mm_load4(in+12);
}
INLINE void Convert(const SSEReal4 &in,float out[16]) {
	_mm_store4(in.m[0],out+0);
	_mm_store4(in.m[1],out+4);
	_mm_store4(in.m[2],out+8);
	_mm_store4(in.m[3],out+12);
}
INLINE void Convert(const SSEReal &inX,const SSEReal &inY,const SSEReal &inZ,const SSEReal &inW,SSEReal4 &out) {
	out.m[0]=inX.m;
	out.m[1]=inY.m;
	out.m[2]=inZ.m;
	out.m[3]=inW.m;
}
INLINE void Convert(const SSEReal4 &in,SSEReal &outX,SSEReal &outY,SSEReal &outZ,SSEReal &outW) {
	outX=in.m[0];
	outY=in.m[1];
	outZ=in.m[2];
	outW=in.m[3];
}

#endif
