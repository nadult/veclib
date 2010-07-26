#ifndef VECLIB_VEC4_H
#define VECLIB_VEC4_H

#include "vec3.h"

template <class base>
class Vec4 {
public:
	typedef base TScalar;
	typedef typename ScalarInfo<base>::TBool TBool;

	INLINE Vec4() { }
	INLINE Vec4(const base &t) :x(t),y(t),z(t),w(t) { }
	INLINE Vec4(const base arr[4]) :x(arr[0]),y(arr[1]),z(arr[2]),w(arr[3]) { }
	INLINE Vec4(const base &tx,const base &ty,const base &tz,const base &tw) :x(tx),y(ty),z(tz),w(tw) { }
	INLINE Vec4(const Vec4 &rhs) :x(rhs.x),y(rhs.y),z(rhs.z),w(rhs.w) { }
	INLINE const Vec4& operator=(const Vec4 &rhs) { x=rhs.x; y=rhs.y; z=rhs.z; w=rhs.w; return *this; }

	explicit INLINE Vec4(const Vec2<base> &v) :x(v.x),y(v.y),z(base(0.0f)),w(base(0.0f)) { }
	explicit INLINE Vec4(const Vec3<base> &v) :x(v.x),y(v.y),z(v.z),w(base(0.0f)) { }
	
	template <class VEC>
	INLINE explicit Vec4(const VEC &v) :x(v.x),y(v.y),z(v.z),w(v.w) { }

#define GEN_OP(sop) \
	template <class GenericVec> \
	INLINE const Vec4 &operator sop(const GenericVec &v) { \
		x sop v.x; y sop v.y; z sop v.z; w sop v.w; \
		return *this; \
	}

	GEN_OP(+=)
	GEN_OP(-=)
	GEN_OP(*=)
	GEN_OP(/=)

#undef GEN_OP
	
	INLINE TBool operator==(const Vec4 &rhs) const { return x==rhs.x&&y==rhs.y&&z==rhs.z&&w==rhs.w; }
	INLINE TBool operator!=(const Vec4 &rhs) const { return x!=rhs.x||y!=rhs.y||z==rhs.z||w==rhs.w; }

	INLINE const Vec4 &operator*=(const base &s) {
		x*=s; y*=s; z*=s; w*=s;
		return *this;
	}
	INLINE const Vec4 &operator/=(const base &s) {
		base inv=Inv(s);
		x*=inv; y*=inv; z*=inv; w*=inv;
		return *this;
	}
	INLINE Vec4 operator-() const {
		Vec4 out;
		out.x=-x;
		out.y=-y;
		out.z=-z;
		out.w=-w;
		return out;
	}

	base x,y,z,w;
};

#define GEN_OP(op,sop) \
	template <class base,class GenericVec> \
	INLINE Vec4<base> operator op(const Vec4<base> &a,const GenericVec &b) { \
		Vec4<base> out(a); \
		out sop b; \
		return out; \
	}
#define GEN_SCL_OP(op,sop) \
	template <class base> \
	INLINE Vec4<base> operator op(const Vec4<base> &a,const base &s) { \
		Vec4<base> out(a); \
		out sop s; \
		return out; \
	}

GEN_OP(+,+=)
GEN_OP(-,-=)
GEN_OP(*,*=)
GEN_OP(/,/=)

GEN_SCL_OP(*,*=)
GEN_SCL_OP(/,/=)

#undef GEN_OP
#undef GEN_SCL_OP

template <class base,class GenericVec>
INLINE base operator|(const Vec4<base> &a,const GenericVec &b) {
	base out=a.x*b.x+a.y*b.y+a.z*b.z+a.w*b.w;
	return out;
}
template <class base>
INLINE base Sum(const Vec4<base> &v) {
	base out=v.x+v.y+v.z+v.w;
	return out;
}


#define GEN_UNARY(name) \
	template <class base> \
	INLINE Vec4<base> V##name(const Vec4<base> &v) { \
		Vec4<base> out; \
		out.x = name(v.x); \
		out.y = name(v.y); \
		out.z = name(v.z); \
		out.w = name(v.w); \
		return out; \
	}
#define GEN_BINARY(name) \
	template <class base> \
	INLINE Vec4<base> V##name(const Vec4<base> &a,const Vec4<base> &b) { \
		Vec4<base> out; \
		out.x = name(a.x,b.x); \
		out.y = name(a.y,b.y); \
		out.z = name(a.z,b.z); \
		out.w = name(a.w,b.w); \
		return out; \
	}

GEN_UNARY(Inv)
GEN_UNARY(Sqrt)
GEN_UNARY(RSqrt)
GEN_UNARY(Abs)
GEN_UNARY(FastInv)
GEN_UNARY(FastRSqrt)

GEN_BINARY(Max)
GEN_BINARY(Min)

#undef GEN_UNARY
#undef GEN_BINARY

template <class base> INLINE base Length(const Vec4<base> &v) { return Sqrt(v | v); }
template <class base> INLINE base LengthSq(const Vec4<base> &v) { return v | v; }

template <class base> INLINE Vec4<base> Condition(const typename Vec4<base>::TBool &expr,const Vec4<base> &a,const Vec4<base> &b)
	{ return Vec4<base>( Condition(expr,a.x,b.x),Condition(expr,a.y,b.y),Condition(expr,a.z,b.z),Condition(expr,a.w,b.w) ); }
template <class base> INLINE Vec4<base> Condition(const typename Vec4<base>::TBool &expr,const Vec4<base> &v)
	{ return Vec4<base>( Condition(expr,v.x),Condition(expr,v.y),Condition(expr,v.z),Condition(expr,v.w) ); }

INLINE Vec4<float> Condition(bool expr, const Vec4<float> &a, const Vec4<float> &b) {
	return expr? a : b;
}
INLINE Vec4<float> Condition(bool expr, const Vec4<float> &a) {
	return expr? a : Vec4<float>(0.0f, 0.0f, 0.0f, 0.0f); }

template <class base1, class base2>
INLINE void Convert(const Vec4<base1> &vec, base2 &outX, base2 &outY, base2 &outZ, base2 &outW) {
	Convert(vec.x, outX);
	Convert(vec.y, outY);
	Convert(vec.z, outZ);
	Convert(vec.w, outW);
}

template <class base1, class base2>
INLINE void Convert(const base1 x, const base1 y, const base1 z, const base1 w, Vec4<base2> &out) {
   	Convert(x, out.x);
	Convert(y, out.y);
	Convert(z, out.z);
	Convert(w, out.w);
}

#endif

