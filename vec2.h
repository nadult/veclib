#ifndef VECLIB_VEC2_H
#define VECLIB_VEC2_H

#include "vecbase.h"

template <class base> class Vec3;
template <class base> class Vec4;

template <class base>
class Vec2 {
public:
	typedef base TScalar;
	typedef typename ScalarInfo<base>::TBool TBool;

	INLINE Vec2() { }
	INLINE Vec2(const base &t) :x(t),y(t) { }
	INLINE Vec2(const base arr[2]) :x(arr[0]),y(arr[1]) { }
	INLINE Vec2(const base &tx,const base &ty) :x(tx),y(ty) { }

	explicit INLINE Vec2(const Vec3<base>&);
	explicit INLINE Vec2(const Vec4<base>&);

#define GEN_OP(op) \
	template <class GenericVec3> \
	INLINE const Vec2 &operator op(const GenericVec3 &v) { \
		x op v.X(); y op v.Y(); \
		return *this; \
	}

	GEN_OP(+=)
	GEN_OP(-=)
	GEN_OP(*=)
	GEN_OP(/=)

#undef GEN_OP

	INLINE const Vec2 &operator*=(const base &s) {
		x*=s; y*=s;
		return *this;
	}
	INLINE const Vec2 &operator/=(const base &s) {
		base inv=Inv(s);
		x*=inv; y*=inv;
		return *this;
	}
	INLINE Vec2 operator-() const {
		Vec2 out;
		out.x=-x;
		out.y=-y;
		return out;
	}

	INLINE base& X() { return x; }
	INLINE base& Y() { return y; }
	INLINE const base& X() const { return x; }
	INLINE const base& Y() const { return y; }


//private:
	base x,y;
};

#include "vec3.h"

template <class base>
Vec2<base>::Vec2(const Vec3<base> &v) :x(v.X()),y(v.Y()) { }
template <class base>
Vec2<base>::Vec2(const Vec4<base> &v) :x(v.X()),y(v.Y()) { }


#define GEN_OP(op,sop) \
	template <class base,class GenericVec> \
	INLINE Vec2<base> operator op(const Vec2<base> &a,const GenericVec &b) { \
		Vec2<base> out(a); \
		out sop b; \
		return out; \
	}
#define GEN_SCL_OP(op,sop) \
	template <class base> \
	INLINE Vec2<base> operator op(const Vec2<base> &a,const base &s) { \
		Vec2<base> out(a); \
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
INLINE base operator|(const Vec2<base> &a,const GenericVec &b) {
	base out=a.X()*b.X()+a.Y()*b.Y();
	return out;
}
template <class base>
INLINE base Sum(const Vec2<base> &v) {
	base out=v.X()+v.Y();
	return out;
}

#define GEN_UNARY(name) \
	template <class base> \
	INLINE Vec2<base> name(const Vec2<base> &v) { \
		Vec2<base> out; \
		out.X() = name(v.X()); \
		out.Y() = name(v.Y()); \
		return out; \
	}
#define GEN_BINARY(name) \
	template <class base> \
	INLINE Vec2<base> name(const Vec2<base> &a,const Vec2<base> &b) { \
		Vec2<base> out; \
		out.X() = name(a.X(),b.X()); \
		out.Y() = name(a.Y(),b.Y()); \
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

template <class base>
base Length(const Vec2<base> &v) {
	return Sqrt(v|v);
}

template <class base>
INLINE Vec2<base> Condition(bool expr,const Vec2<base> &a,const Vec2<base> &b) {
	return expr?a:b;
}
template <class base>
INLINE Vec2<base> Condition(bool expr,const Vec2<base> &v) {
	return expr?v:Vec2<base>(Const<base,0>());
}

template<class base>
INLINE void Convert(const Vec2<base> &in,Vec2<base> &out) {
	out=in;
}

#endif
