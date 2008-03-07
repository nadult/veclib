#ifndef VECLIB_VECBASE_H
#define VECLIB_VECBASE_H

//#include <boost/static_assert.hpp>


typedef unsigned char u8;
typedef char i8;
typedef short i16;
typedef unsigned short u16;
typedef int i32;
typedef unsigned int u32;
typedef long long i64;
typedef unsigned long long u64;
	
union UValue
{
	UValue(uint v) :u(v) { }
	UValue(int v) :i(v) { }
	UValue(float v) :f(v) { }

	float f;
	int i;
	uint u;
};

/*!
	Const< Typ, m, n > :: Value()    = Typ(m) / Typ(n)
*/
template <class base,int m,int n=1>
class Const {
	static const base value;
public:
	INLINE static base Value() { return value; }
};

/*!

*/
template <class T>
struct ScalarInfo {
	enum { Multiplicity=1 };
	typedef bool TBool;

	// n must be < Multiplicity
	INLINE static bool ElementMask(int n) {
		return 1;
	}
};

template <class base,int m,int n>
const base Const<base,m,n>::value=base(m)/base(n);

template <class base> struct ConstPI: public Const<base,75948,24175> { };
template <class base> struct Const2PI: public Const<base,2*75948,24175> { };
template <class base> struct ConstInvPI: public Const<base,24175,75948> { };
template <class base> struct ConstInv2PI: public Const<base,24175,2*75948> { };
template <class base> struct ConstEpsilon: public Const<base,1,100000> { };

INLINE float Sqrt(const float &v) {
	return sqrt(v);
}
INLINE float Inv(const float &v) {
	return Const<float,1>::Value() / v;
}
INLINE float RSqrt(const float &v) {
	return Const<float,1>::Value() / Sqrt(v);
}
INLINE float FastInv(const float &v) {
	return Const<float,1>::Value() / v;
}
INLINE float FastRSqrt(const float &v) {
	return Const<float,1>::Value() / Sqrt(v);
}
INLINE float Abs(const float &v) {
	return v < Const<float,0>::Value() ? -v : v;
}
INLINE float Min(const float &a,const float &b) {
	return a < b ? a : b;
}
INLINE float Max(const float &a,const float &b) {
	return a > b ? a : b;
}
INLINE float Condition(bool expr,float a,float b) {
	return expr?a:b;
}
INLINE float Condition(bool expr,float v) {
	return expr?v:0.0f;
}
INLINE int SignMask(const float &v) {
	return v<0?1:0;
}
INLINE float Sin(const float rad) {
	return sin(rad);
}
INLINE float Cos(const float rad) {
	return cos(rad);
}

INLINE float FRand() {
	return float(rand())/float(RAND_MAX);
}

INLINE bool ForAny(bool expr) {
	return expr;
}
INLINE bool ForAll(bool expr) {
	return expr;
}
/// Returns bit mask, bit n is set if expression is true for element n
INLINE int ForWhich(bool expr) {
	return expr;
}

template <class T>
T Clamp(const T &obj,const T &min,const T &max) {
	return Min(Max(obj,min),max);
}

template <class Obj,class Scl>
Obj Lerp(const Obj &a,const Obj &b,const Scl &x) {
	return a+(a-b)*x;
}

template <class T>
void Swap(T &a,T &b) {
	T temp(a);
	a=b;
	b=temp;
}

#endif
