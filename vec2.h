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

	//TODO poprawic
	INLINE Vec2() { }
	INLINE Vec2(const base &t) :x(t),y(t) { }
	INLINE Vec2(const base arr[2]) :x(arr[0]),y(arr[1]) { }
	INLINE Vec2(const base &tx,const base &ty) :x(tx),y(ty) { }
	INLINE Vec2(const Vec2& rhs) :x(rhs.x),y(rhs.y) { }
	INLINE const Vec2 &operator=(const Vec2 &rhs) { x=rhs.x; y=rhs.y; return *this; }

	template <class VEC>
	INLINE explicit Vec2(const VEC &v) :x(v.x),y(v.y) { }

	explicit INLINE Vec2(const Vec3<base>&);
	explicit INLINE Vec2(const Vec4<base>&);

#define GEN_OP(op) \
	template <class GenericVec3> \
	INLINE const Vec2 &operator op(const GenericVec3 &v) { \
		x op v.x; y op v.y; \
		return *this; \
	}


	GEN_OP(+=)
	GEN_OP(-=)
	GEN_OP(*=)
	GEN_OP(/=)

#undef GEN_OP

	INLINE TBool operator==(const Vec2 &rhs) const { return x==rhs.x&&y==rhs.y; }
	INLINE TBool operator!=(const Vec2 &rhs) const { return x!=rhs.x||y!=rhs.y; }

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

	base x,y;
};

#include "vec3.h"

template <class base>
Vec2<base>::Vec2(const Vec3<base> &v) :x(v.x),y(v.y) { }
template <class base>
Vec2<base>::Vec2(const Vec4<base> &v) :x(v.x),y(v.y) { }


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
INLINE base operator|(const Vec2<base> &a,const GenericVec &b) { return a.x*b.x+a.y*b.y; }
template <class base>
INLINE base Sum(const Vec2<base> &v) { return v.x+v.y; }

#define GEN_UNARY(name) \
	template <class base> \
	INLINE Vec2<base> V##name(const Vec2<base> &v) { \
		Vec2<base> out; \
		out.x = name(v.x); \
		out.y = name(v.y); \
		return out; \
	}
#define GEN_BINARY(name) \
	template <class base> \
	INLINE Vec2<base> V##name(const Vec2<base> &a,const Vec2<base> &b) { \
		Vec2<base> out; \
		out.x = name(a.x,b.x); \
		out.y = name(a.y,b.y); \
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

template <class base> INLINE base Length(const Vec2<base> &v) { return Sqrt(v|v); }
template <class base> INLINE base LengthSq(const Vec2<base> &v) { return v|v; }

template <class base> INLINE Vec2<base> Condition(const typename Vec2<base>::TBool &expr,const Vec2<base> &a,const Vec2<base> &b)
	{ return Vec2<base>( Condition(expr,a.x,b.x),Condition(expr,a.y,b.y) ); }
template <class base> INLINE Vec2<base> Condition(const typename Vec2<base>::TBool &expr,const Vec2<base> &v)
	{ return Vec2<base>( Condition(expr,v.x),Condition(expr,v.y) ); }

template <> INLINE Vec2<float> Condition(const bool &expr,const Vec2<float> &a,const Vec2<float> &b) { return expr?a:b; }
template <> INLINE Vec2<float> Condition(const bool &expr,const Vec2<float> &a) { return expr?a:Vec2<float>(0.0f,0.0f); }

template <class base1,class base2> INLINE void Convert(const Vec2<base1> &vec,base2 &outX,base2 &outY)
	{ Convert(vec.x,outX); Convert(vec.y,outY); }
template <class base1,class base2> INLINE void Convert(const base1 &x,const base1 &y,Vec2<base2> &out)
	{ Convert(x,out.x); Convert(y,out.y); }



#endif

