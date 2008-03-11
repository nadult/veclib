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

	explicit INLINE Vec3(const Vec2<base>&v) :x(v.x),y(v.y),z(Const<base,0>()) { }
	explicit INLINE Vec3(const Vec4<base>&);

#define GEN_OP(op) \
	template <class GenericVec3> \
	INLINE const Vec3 &operator op(const GenericVec3 &v) { \
		x op v.x; y op v.y; z op v.z; \
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
	
	base x,y,z;
};

#include "vec4.h"

template <class base>
Vec3<base>::Vec3(const Vec4<base> &v) :x(v.x),y(v.y),z(v.z) { }

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
	base out=a.x*b.x+a.y*b.y+a.z*b.z;
	return out;
}
template <class base>
INLINE base Sum(const Vec3<base> &v) {
	base out=v.x+v.y+v.z;
	return out;
}
template <class base,class GenericVec>
INLINE Vec3<base> operator^(const Vec3<base> &b,const GenericVec &c) {
	Vec3<base> out;
	out.x = b.y*c.z-b.z*c.y;
	out.y = b.z*c.x-b.x*c.z;
	out.z = b.x*c.y-b.y*c.x;
	return out;
}

#define GEN_UNARY(name) \
	template <class base> \
	INLINE Vec3<base> name(const Vec3<base> &v) { \
		Vec3<base> out; \
		out.x = name(v.x); \
		out.y = name(v.y); \
		out.z = name(v.z); \
		return out; \
	}
#define GEN_BINARY(name) \
	template <class base> \
	INLINE Vec3<base> name(const Vec3<base> &a,const Vec3<base> &b) { \
		Vec3<base> out; \
		out.x = name(a.x,b.x); \
		out.y = name(a.y,b.y); \
		out.z = name(a.z,b.z); \
		return out; \
	}

GEN_UNARY(VInv)
GEN_UNARY(VSqrt)
GEN_UNARY(VRSqrt)
GEN_UNARY(VAbs)
GEN_UNARY(VFastInv)
GEN_UNARY(VFastRSqrt)

GEN_BINARY(VMax)
GEN_BINARY(VMin)

#undef GEN_UNARY
#undef GEN_BINARY

template <class base> INLINE base Length(const Vec3<base> &v) { return Sqrt(v|v); }

template <class base> INLINE Vec3<base> Condition(const typename Vec3<base>::TBool &expr,const Vec3<base> &a,const Vec3<base> &b)
	{ return Vec3<base>( Condition(expr,a.x,b.x),Condition(expr,a.y,b.y),Condition(expr,a.z,b.z) ); }
template <class base> INLINE Vec3<base> Condition(const typename Vec3<base>::TBool &expr,const Vec3<base> &v)
	{ return Vec3<base>( Condition(expr,v.x),Condition(expr,v.y,Condition(expr,v.z)) ); }

template <> INLINE Vec3<float> Condition(const bool &expr,const Vec3<float> &a,const Vec3<float> &b) { return expr?a:b; }
template <> INLINE Vec3<float> Condition(const bool &expr,const Vec3<float> &a) { return expr?a:Vec3<float>(0.0f,0.0f,0.0f); }

template <class base1,class base2> INLINE void Convert(const Vec3<base1> &vec,base2 &outX,base2 &outY,base2 &outZ)
	{ Convert(vec.x,outX); Convert(vec.y,outY); Convert(vec.z,outZ); }
template <class base1,class base2> INLINE void Convert(const base1 &x,const base1 &y,const base1 &z,Vec3<base2> &out)
	{ Convert(x,out.x); Convert(y,out.y); Convert(z,out.z); }



#endif

