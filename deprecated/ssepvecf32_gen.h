// Generator wektorkow upakowanych (od 2 do 4)

class CLASS_NAME {
public:
	typedef float TScalar;
	typedef bool TBool;

	CLASS_NAME() { }
	CLASS_NAME(__m128 m) :m(m) { }
	CLASS_NAME(const CLASS_NAME &rhs) :m(rhs.m) { }
	explicit CLASS_NAME(float v) :m(_mm_set1_ps(v)) { }

	const CLASS_NAME operator=(const CLASS_NAME &rhs) { m=rhs.m; return *this; }
	const CLASS_NAME operator-() const { return _mm_sub_ps(_mm_setzero_ps(), m); }

	const CLASS_NAME operator+=(CLASS_NAME v) { m = _mm_add_ps(m, v.m); return *this; }
	const CLASS_NAME operator-=(CLASS_NAME v) { m = _mm_sub_ps(m, v.m); return *this; }
	const CLASS_NAME operator*=(CLASS_NAME v) { m = _mm_mul_ps(m, v.m); return *this; }
	const CLASS_NAME operator/=(CLASS_NAME v) { m = _mm_div_ps(m, v.m); return *this; }

	const CLASS_NAME operator*=(float s) { m = _mm_mul_ps(m, _mm_set1_ps(s)); return *this; }
	const CLASS_NAME operator/=(float s) { m = _mm_div_ps(m, _mm_set1_ps(s)); return *this; }

	ADDITIONAL_CLASS_CODE
};


inline const CLASS_NAME VSqrt(CLASS_NAME v)			{ return _mm_sqrt_ps(v.m); }
inline const CLASS_NAME VInv(CLASS_NAME v)			{ return _mm_nrrcp_ps(v.m); }
inline const CLASS_NAME VRSqrt(CLASS_NAME v)		{ return _mm_nrrsqrt_ps(v.m); }
inline const CLASS_NAME VAbs(CLASS_NAME v)			{ return _mm_and_ps(_mm_set1_ps(BitCast<float,u32>(0x7fffffff)),v.m); }
inline const CLASS_NAME VFastInv(CLASS_NAME v)		{ return _mm_rcp_ps(v.m); }
inline const CLASS_NAME VFastRSqrt(CLASS_NAME v)	{ return _mm_rsqrt_ps(v.m); }


inline const CLASS_NAME VMin(CLASS_NAME a, CLASS_NAME b) { return _mm_min_ps(a.m,b.m); }
inline const CLASS_NAME VMax(CLASS_NAME a, CLASS_NAME b) { return _mm_max_ps(a.m,b.m); }

inline const CLASS_NAME operator+(CLASS_NAME a, CLASS_NAME b) { return _mm_add_ps(a.m, b.m); }
inline const CLASS_NAME operator-(CLASS_NAME a, CLASS_NAME b) { return _mm_sub_ps(a.m, b.m); }
inline const CLASS_NAME operator*(CLASS_NAME a, CLASS_NAME b) { return _mm_mul_ps(a.m, b.m); }
inline const CLASS_NAME operator/(CLASS_NAME a, CLASS_NAME b) { return _mm_div_ps(a.m, b.m); }

inline const CLASS_NAME operator*(CLASS_NAME a, float v) { return _mm_mul_ps(a.m, _mm_set1_ps(v)); }
inline const CLASS_NAME operator/(CLASS_NAME a, float v) { return _mm_div_ps(a.m, _mm_set1_ps(v)); }


inline CLASS_NAME Condition(bool test_, CLASS_NAME v1, CLASS_NAME v2) {
	__m128 test = _mm_bool2mask(test_);
	return _mm_or_ps(_mm_and_ps(test,v1.m), _mm_andnot_ps(test,v2.m));
}
inline CLASS_NAME Condition(bool test_, CLASS_NAME v1) {
	__m128 test = _mm_bool2mask(test_);
	return _mm_and_ps(test, v1.m);
}

