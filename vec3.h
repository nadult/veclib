#ifndef VECLIB_VEC3_H
#define VECLIB_VEC3_H

#include "vec2.h"

template <class base> class Vec4;

template <class base>
class Vec3 {
public:
	typedef base TScalar;
	typedef typename ScalarInfo<base>::TBool TBool;

	INLINE Vec3() { }
	INLINE Vec3(const base &t) :x(t),y(t),z(t) { }
	INLINE Vec3(const base arr[3]) :x(arr[0]),y(arr[1]),z(arr[2]) { }
	INLINE Vec3(const base &tx,const base &ty,const base &tz) :x(tx),y(ty),z(tz) { }

	explicit INLINE Vec3(const Vec2<base>&v) :x(v.X()),y(v.Y()),z(Const<base,0>()) { }
	explicit INLINE Vec3(const Vec4<base>&);

#define GEN_OP(op) \
	template <class GenericVec3> \
	INLINE const Vec3 &operator op(const GenericVec3 &v) { \
		x op v.X(); y op v.Y(); z op v.Z(); \
		return *this; \
	}

	GEN_OP(+=)
	GEN_OP(-=)
	GEN_OP(*=)
	GEN_OP(/=)

#undef GEN_OP

	INLINE const Vec3 &operator*=(const base &s) {
		x*=s; y*=s; z*=s;
		return *this;
	}
	INLINE const Vec3 &operator/=(const base &s) {
		base inv=Inv(s);
		x*=inv; y*=inv; z*=inv;
		return *this;
	}
	INLINE Vec3 operator-() const {
		Vec3 out;
		out.x=-x;
		out.y=-y;
		out.z=-z;
		return out;
	}

	INLINE base& X() { return x; }
	INLINE base& Y() { return y; }
	INLINE base& Z() { return z; }
	INLINE const base& X() const { return x; }
	INLINE const base& Y() const { return y; }
	INLINE const base& Z() const { return z; }


//private:
	base x,y,z;
};

#include "vec4.h"

template <class base>
Vec3<base>::Vec3(const Vec4<base> &v) :x(v.X()),y(v.Y()),z(v.Z()) { }

#define GEN_OP(op,sop) \
	template <class base,class GenericVec> \
	INLINE Vec3<base> operator op(const Vec3<base> &a,const GenericVec &b) { \
		Vec3<base> out(a); \
		out sop b; \
		return out; \
	}
#define GEN_SCL_OP(op,sop) \
	template <class base> \
	INLINE Vec3<base> operator op(const Vec3<base> &a,const base &s) { \
		Vec3<base> out(a); \
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
INLINE base operator|(const Vec3<base> &a,const GenericVec &b) {
	base out=a.X()*b.X()+a.Y()*b.Y()+a.Z()*b.Z();
	return out;
}
template <class base>
INLINE base Sum(const Vec3<base> &v) {
	base out=v.X()+v.Y()+v.Z();
	return out;
}
template <class base,class GenericVec>
INLINE Vec3<base> operator^(const Vec3<base> &b,const GenericVec &c) {
	Vec3<base> out;
	out.X() = b.Y()*c.Z()-b.Z()*c.Y();
	out.Y() = b.Z()*c.X()-b.X()*c.Z();
	out.Z() = b.X()*c.Y()-b.Y()*c.X();
	return out;
}

#define GEN_UNARY(name) \
	template <class base> \
	INLINE Vec3<base> name(const Vec3<base> &v) { \
		Vec3<base> out; \
		out.X() = name(v.X()); \
		out.Y() = name(v.Y()); \
		out.Z() = name(v.Z()); \
		return out; \
	}
#define GEN_BINARY(name) \
	template <class base> \
	INLINE Vec3<base> name(const Vec3<base> &a,const Vec3<base> &b) { \
		Vec3<base> out; \
		out.X() = name(a.X(),b.X()); \
		out.Y() = name(a.Y(),b.Y()); \
		out.Z() = name(a.Z(),b.Z()); \
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

template <class base> base Length(const Vec3<base> &v) { return Sqrt(v|v); }

template <class base> INLINE Vec3<base> Condition(const typename Vec3<base>::TBool &expr,const Vec3<base> &a,const Vec3<base> &b)
	{ return out( Condition(expr,a.X(),b.X()),Condition(expr,a.Y(),b.Y()),Condition(expr,a.Z(),b.Z()) ); }
template <class base> INLINE Vec3<base> Condition(const typename Vec3<base>::TBool &expr,const Vec3<base> &v)
	{ return out( Condition(expr,v.X()),Condition(expr,v.Y(),Condition(expr,v.Z())) ); }

template <> INLINE Vec3<float> Condition(const bool &expr,const Vec3<float> &a,const Vec3<float> &b) { return expr?a:b; }
template <> INLINE Vec3<float> Condition(const bool &expr,const Vec3<float> &a) { return expr?a:Vec3<float>(0.0f,0.0f,0.0f); }

#endif

