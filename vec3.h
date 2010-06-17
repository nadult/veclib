#ifndef VECLIB_VEC3_H
#define VECLIB_VEC3_H

#include "vec2.h"

template <class base> class Vec4;

template <class base>
class Vec3 {
public:
	typedef base TScalar;
	typedef typename ScalarInfo<base>::TBool TBool;

	Vec3() { }
	Vec3(const base &t) :x(t),y(t),z(t) { }
	Vec3(const base arr[3]) :x(arr[0]),y(arr[1]),z(arr[2]) { }
	Vec3(const base &tx,const base &ty,const base &tz) :x(tx),y(ty),z(tz) { }
	Vec3(const Vec3 &rhs) :x(rhs.x),y(rhs.y),z(rhs.z) { }
	Vec3 operator=(const Vec3 &rhs) { x=rhs.x; y=rhs.y; z=rhs.z; return *this; }

	explicit Vec3(const Vec2<base>&v) :x(v.x),y(v.y),z(base(0.0f)) { }
	explicit Vec3(const Vec4<base>&);

	template <class VEC>
	explicit Vec3(const VEC &v) :x(v.x),y(v.y),z(v.z) { }

#define GEN_OP(op) \
	template <class GenericVec3> \
	const Vec3 operator op(GenericVec3 v) { \
		x op v.x; y op v.y; z op v.z; \
		return *this; \
	}

	GEN_OP(+=)
	GEN_OP(-=)
	GEN_OP(*=)
	GEN_OP(/=)

#undef GEN_OP
	
	TBool operator==(Vec3 rhs) const { return x==rhs.x&&y==rhs.y&&z==rhs.z; }
	TBool operator!=(Vec3 rhs) const { return x!=rhs.x||y!=rhs.y||z!=rhs.z; }

	const Vec3 operator*=(base s) {
		x*=s; y*=s; z*=s;
		return *this;
	}
	const Vec3 operator/=(base s) {
		base inv=Inv(s);
		x*=inv; y*=inv; z*=inv;
		return *this;
	}
	Vec3 operator-() const {
		Vec3 out;
		out.x=-x;
		out.y=-y;
		out.z=-z;
		return out;
	}
	base& operator[](int i) { return i==0?x:i==1?y:z; }
	const base& operator[](int i) const { return i==0?x:i==1?y:z; }

	base x,y,z;
};

#include "vec4.h"

template <class base>
Vec3<base>::Vec3(const Vec4<base> &v) :x(v.x),y(v.y),z(v.z) { }

#define GEN_OP(op,sop) \
	template <class base,class GenericVec> \
	inline Vec3<base> operator op(Vec3<base> a, GenericVec b) { \
		Vec3<base> out(a); \
		out sop b; \
		return out; \
	}
#define GEN_SCL_OP(op,sop) \
	template <class base> \
	inline Vec3<base> operator op(Vec3<base> a, base s) { \
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
inline const base operator|(Vec3<base> a, GenericVec b) {
	base out = a.x * b.x + a.y * b.y + a.z * b.z;
	return out;
}
template <class base>
inline const base Sum(const Vec3<base> &v) {
	base out = v.x + v.y + v.z;
	return out;
}

template <class base,class GenericVec>
inline const Vec3<base> operator^(Vec3<base> b, GenericVec c) {
	Vec3<base> out;
	out.x = b.y * c.z - b.z * c.y;
	out.y = b.z * c.x - b.x * c.z;
	out.z = b.x * c.y - b.y * c.x;
	return out;
}

#define GEN_UNARY(name) \
	template <class base> \
	inline const Vec3<base> V##name(Vec3<base> v) { \
		Vec3<base> out; \
		out.x = name(v.x); \
		out.y = name(v.y); \
		out.z = name(v.z); \
		return out; \
	}
#define GEN_BINARY(name) \
	template <class base> \
	inline const Vec3<base> V##name(Vec3<base> a, Vec3<base> b) { \
		Vec3<base> out; \
		out.x = name(a.x,b.x); \
		out.y = name(a.y,b.y); \
		out.z = name(a.z,b.z); \
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

template <class base> inline const base Length(Vec3<base> v) { return Sqrt(v|v); }
template <class base> inline const base LengthSq(Vec3<base> v) { return v|v; }

template <class base> inline const Vec3<base> Condition(typename Vec3<base>::TBool expr, Vec3<base> a, Vec3<base> b)
	{ return Vec3<base>( Condition(expr,a.x,b.x),Condition(expr,a.y,b.y),Condition(expr,a.z,b.z) ); }
template <class base> inline const Vec3<base> Condition(typename Vec3<base>::TBool expr, Vec3<base> v)
	{ return Vec3<base>( Condition(expr,v.x),Condition(expr,v.y),Condition(expr,v.z) ); }

template <> inline const Vec3<float> Condition(bool expr, Vec3<float> a, Vec3<float> b) { return expr?a:b; }
template <> inline const Vec3<float> Condition(bool expr, Vec3<float> a) { return expr?a:Vec3<float>(0.0f,0.0f,0.0f); }

template <class base1,class base2>
inline void Convert(Vec3<base1> vec,base2 &outX,base2 &outY,base2 &outZ) {
	Convert(vec.x,outX);
	Convert(vec.y,outY);
	Convert(vec.z,outZ);
}

template <class base1,class base2>
inline void Convert(base1 x, base1 y, base1 z, Vec3<base2> &out) {
	Convert(x,out.x);
	Convert(y,out.y);
	Convert(z,out.z);
}



#endif

