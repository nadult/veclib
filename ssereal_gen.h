// Generator SSEReal i SSEPReal

class MASK_NAME;

class CLASS_NAME
{
public:
	INLINE CLASS_NAME() {
	}
	INLINE CLASS_NAME(const __m128 &v) :m(v) {
	}
	INLINE CLASS_NAME(float v) :m(_mm_set1_ps(v)) {
	}

#define GEN_SOP(sop,mmname) \
	INLINE const CLASS_NAME &operator sop(const CLASS_NAME &v) { \
		m=mmname(m,v.m); \
		return *this; \
	}

	GEN_SOP(+=,_mm_add_ps)
	GEN_SOP(-=,_mm_sub_ps)
	GEN_SOP(*=,_mm_mul_ps)
	GEN_SOP(/=,_mm_div_ps)

#undef GEN_SOP

	INLINE CLASS_NAME operator-() const {
		return _mm_sub_ps(_mm_setzero_ps(),m);
	}
	INLINE operator float() const {
		float out;
		_mm_store_ss(&out,m);
		return out;
	}
	ADDITIONAL_CLASS_CODE

	__m128 m;
};

#define GEN_CMP_OP(op,mmname) \
	INLINE MASK_NAME operator op(const CLASS_NAME &a,const CLASS_NAME &b) { \
		return mmname(a.m,b.m); \
	}
#define GEN_OP(op,sop) \
	INLINE CLASS_NAME operator op(const CLASS_NAME &a,const CLASS_NAME &b) { \
		CLASS_NAME out(a); \
		out sop b; \
		return out; \
	}
#define GEN_FUNC(name,mmname) \
	INLINE CLASS_NAME name(const CLASS_NAME &v) { \
		return mmname(v.m); \
	}

GEN_CMP_OP(==,_mm_cmpeq_ps)
GEN_CMP_OP(!=,_mm_cmpneq_ps)
GEN_CMP_OP(<=,_mm_cmple_ps)
GEN_CMP_OP(>=,_mm_cmpge_ps)
GEN_CMP_OP(<,_mm_cmplt_ps)
GEN_CMP_OP(>,_mm_cmpgt_ps)

GEN_OP(+,+=)
GEN_OP(-,-=)
GEN_OP(*,*=)
GEN_OP(/,/=)

GEN_FUNC(Sqrt,_mm_sqrt_ps)
GEN_FUNC(Inv,_mm_nrrcp_ps)
GEN_FUNC(RSqrt,_mm_nrrsqrt_ps)
GEN_FUNC(FastInv,_mm_rcp_ps)
GEN_FUNC(FastRSqrt,_mm_rsqrt_ps)

#undef GEN_OP
#undef GEN_CMP_OP
#undef GEN_FUNC


template <int m,int n> class Const<CLASS_NAME,m,n> {
public:
	INLINE static CLASS_NAME Value() { return CLASS_NAME(Const<__m128,m,n>::Value()); }
	INLINE operator CLASS_NAME() const { return Value(); }
};

INLINE CLASS_NAME Abs(const CLASS_NAME &v) {
	return _mm_and_ps(Const<MASK_NAME,0x7fffffff>::Value().m,v.m);
}
INLINE CLASS_NAME Min(const CLASS_NAME &a,const CLASS_NAME &b) {
	return _mm_min_ps(a.m,b.m);
}
INLINE CLASS_NAME Max(const CLASS_NAME &a,const CLASS_NAME &b) {
	return _mm_max_ps(a.m,b.m);
}

INLINE int SignMask(const CLASS_NAME &v) {
	return _mm_movemask_ps(v.m);
}

INLINE CLASS_NAME Condition(const MASK_NAME &test,const CLASS_NAME &v1,const CLASS_NAME &v2) {
	return _mm_or_ps(_mm_and_ps(test.m,v1.m),_mm_andnot_ps(test.m,v2.m));
}
INLINE CLASS_NAME Condition(const MASK_NAME_NEG &test,const CLASS_NAME &v1,const CLASS_NAME &v2) {
	return _mm_or_ps(_mm_andnot_ps(test.m,v1.m),_mm_and_ps(test.m,v2.m));
}
INLINE CLASS_NAME Condition(const MASK_NAME &test,const CLASS_NAME &v1) {
	return _mm_and_ps(test.m,v1.m);
}
INLINE CLASS_NAME Condition(const MASK_NAME_NEG &test,const CLASS_NAME &v1) {
	return _mm_andnot_ps(test.m,v1.m);
}
