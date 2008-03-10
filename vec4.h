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

	explicit INLINE Vec4(const Vec2<base> &v) :x(v.X()),y(v.Y()),z(Const<base,0>()),w(Const<base,0>()) { }
	explicit INLINE Vec4(const Vec3<base> &v) :x(v.X()),y(v.Y()),z(v.Z()),w(Const<base,0>()) { }

#define GEN_OP(sop) \
	template <class GenericVec> \
	INLINE const Vec4 &operator sop(const GenericVec &v) { \
		x sop v.X(); y sop v.Y(); z sop v.Z(); w sop v.W(); \
		return *this; \
	}

	GEN_OP(+=)
	GEN_OP(-=)
	GEN_OP(*=)
	GEN_OP(/=)

#undef GEN_OP

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

	INLINE base& X() { return x; }
	INLINE base& Y() { return y; }
	INLINE base& Z() { return z; }
	INLINE base& W() { return w; }
	INLINE const base& X() const { return x; }
	INLINE const base& Y() const { return y; }
	INLINE const base& Z() const { return z; }
	INLINE const base& W() const { return w; }

//private:
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
	base out=a.X()*b.X()+a.Y()*b.Y()+a.Z()*b.Z()+a.W()*b.W();
	return out;
}
template <class base>
INLINE base Sum(const Vec4<base> &v) {
	base out=v.X()+v.Y()+v.Z()+v.W();
	return out;
}


#define GEN_UNARY(name) \
	template <class base> \
	INLINE Vec4<base> name(const Vec4<base> &v) { \
		Vec4<base> out; \
		out.X() = name(v.X()); \
		out.Y() = name(v.Y()); \
		out.Z() = name(v.Z()); \
		out.W() = name(v.W()); \
		return out; \
	}
#define GEN_BINARY(name) \
	template <class base> \
	INLINE Vec4<base> name(const Vec4<base> &a,const Vec4<base> &b) { \
		Vec4<base> out; \
		out.X() = name(a.X(),b.X()); \
		out.Y() = name(a.Y(),b.Y()); \
		out.Z() = name(a.Z(),b.Z()); \
		out.W() = name(a.W(),b.W()); \
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

template <class base> base Length(const Vec4<base> &v) { return Sqrt(v|v); }

template <class base> INLINE Vec4<base> Condition(const typename Vec4<base>::TBool &expr,const Vec4<base> &a,const Vec4<base> &b)
	{ return out( Condition(expr,a.X(),b.X()),Condition(expr,a.Y(),b.Y()),Condition(expr,a.Z(),b.Z()),Condition(expr,a.W(),b.W()) ); }
template <class base> INLINE Vec4<base> Condition(const typename Vec4<base>::TBool &expr,const Vec4<base> &v)
	{ return out( Condition(expr,v.X()),Condition(expr,v.Y()),Condition(expr,v.Z()),Condition(expr,v.W()) ); }

template <> INLINE Vec4<float> Condition(const bool &expr,const Vec4<float> &a,const Vec4<float> &b) { return expr?a:b; }
template <> INLINE Vec4<float> Condition(const bool &expr,const Vec4<float> &a) { return expr?a:Vec4<float>(0.0f,0.0f,0.0f,0.0f); }

#endif

