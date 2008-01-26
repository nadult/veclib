// Generator wektorków upakowanych (od 2 do 4)

class CLASS_NAME {
public:
	typedef SSEPReal TScalar;
	typedef SSEPMask TBool;

	INLINE CLASS_NAME() {
	}
	INLINE CLASS_NAME(const __m128 &v) :m(v) {
	}
	INLINE CLASS_NAME(const SSEPReal &v) :m(v.m) {
	}
	INLINE explicit CLASS_NAME(const SSEPMask &v) :m(v.m) {
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

	INLINE const CLASS_NAME &operator*=(const SSEPReal &s) {
		m=_mm_mul_ps(m,s.m);
		return *this;
	}
	INLINE const CLASS_NAME &operator/=(const SSEPReal &s) {
		m=_mm_div_ps(m,s.m);
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
	template <class base> \
	INLINE CLASS_NAME operator op(const CLASS_NAME &a,const SSEPReal &s) { \
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

INLINE CLASS_NAME Condition(const SSEPMask &test,const CLASS_NAME &v1,const CLASS_NAME &v2) {
	return _mm_or_ps(_mm_and_ps(test.m,v1.m),_mm_andnot_ps(test.m,v2.m));
}
INLINE CLASS_NAME Condition(const SSEPMaskNeg &test,const CLASS_NAME &v1,const CLASS_NAME &v2) {
	return _mm_or_ps(_mm_andnot_ps(test.m,v1.m),_mm_and_ps(test.m,v2.m));
}
INLINE CLASS_NAME Condition(const SSEPMask &test,const CLASS_NAME &v1) {
	return _mm_and_ps(test.m,v1.m);
}
INLINE CLASS_NAME Condition(const SSEPMaskNeg &test,const CLASS_NAME &v1) {
	return _mm_andnot_ps(test.m,v1.m);
}

INLINE CLASS_NAME Abs(const CLASS_NAME &v) {
	return _mm_and_ps(Const<SSEPMask,0x7fffffff>::Value().m,v.m);
}

