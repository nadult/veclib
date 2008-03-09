// Generator wektorkow upakowanych (od 2 do 4)

class CLASS_NAME {
public:
	typedef float TScalar;
	typedef bool TBool;

	INLINE CLASS_NAME() {
	}
	INLINE CLASS_NAME(const __m128 &v) :m(v) {
	}
	INLINE explicit CLASS_NAME(float v) :m(_mm_set1_ps(v)) {
	}
	INLINE explicit CLASS_NAME(bool v) :m(_mm_bool2mask(v)) {
	}

	INLINE CLASS_NAME operator-() const {
		return _mm_sub_ps(_mm_setzero_ps(),m);
	}

#define GEN_OP(op,mmop) \
	INLINE const CLASS_NAME &operator op (const CLASS_NAME &v) { \
		m= mmop (m,v.m); \
		return *this; \
	}

	GEN_OP(+=,_mm_add_ps)
	GEN_OP(-=,_mm_sub_ps)
	GEN_OP(*=,_mm_mul_ps)
	GEN_OP(/=,_mm_div_ps)

#undef GEN_OP

	INLINE const CLASS_NAME &operator*=(float s) {
		m=_mm_mul_ps(m,_mm_set1_ps(s));
		return *this;
	}
	INLINE const CLASS_NAME &operator/=(float s) {
		m=_mm_div_ps(m,_mm_set1_ps(s));
		return *this;
	}

	ADDITIONAL_CLASS_CODE

	__m128 m;
};


#define GEN_OP(op,sop) \
	INLINE CLASS_NAME operator op(const CLASS_NAME &a,const CLASS_NAME &b) { \
		CLASS_NAME out(a); \
		out sop b; \
		return out; \
	}
#define GEN_SCL_OP(op,sop) \
	INLINE CLASS_NAME operator op(const CLASS_NAME &a,float s) { \
		CLASS_NAME out(a); \
		out sop s; \
		return out; \
	}
#define GEN_FUNC(name,mmname) \
	INLINE CLASS_NAME name(const CLASS_NAME &v) { \
		return mmname(v.m); \
	}
#define GEN_BIN_FUNC(name,mmname) \
	INLINE CLASS_NAME name(const CLASS_NAME &a,const CLASS_NAME &b) { \
		return mmname(a.m,b.m); \
	}

GEN_FUNC(Sqrt,_mm_sqrt_ps)
GEN_FUNC(Inv,_mm_nrrcp_ps)
GEN_FUNC(RSqrt,_mm_nrrsqrt_ps)
GEN_FUNC(FastInv,_mm_rcp_ps)
GEN_FUNC(FastRSqrt,_mm_rsqrt_ps)

GEN_BIN_FUNC(Min,_mm_min_ps)
GEN_BIN_FUNC(Max,_mm_max_ps)

GEN_OP(+,+=)
GEN_OP(-,-=)
GEN_OP(*,*=)
GEN_OP(/,/=)

GEN_SCL_OP(*,*=)
GEN_SCL_OP(/,/=)

#undef GEN_OP
#undef GEN_SCL_OP
#undef GEN_FUNC
#undef GEN_BIN_FUNC

INLINE CLASS_NAME Condition(bool test_,const CLASS_NAME &v1,const CLASS_NAME &v2) {
	__m128 test=_mm_bool2mask(test_);
	return _mm_or_ps(_mm_and_ps(test,v1.m),_mm_andnot_ps(test,v2.m));
}
INLINE CLASS_NAME Condition(bool test_,const CLASS_NAME &v1) {
	__m128 test=_mm_bool2mask(test_);
	return _mm_and_ps(test,v1.m);
}

INLINE CLASS_NAME Abs(const CLASS_NAME &v) {
	return _mm_and_ps(SSEMaskConst<0x7fffffff>::value,v.m);
}

