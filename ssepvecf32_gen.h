// Generator wektorkow upakowanych (od 2 do 4)

class CLASS_NAME {
public:
	typedef float TScalar;
	typedef bool TBool;

	INLINE CLASS_NAME() { }
	INLINE CLASS_NAME(const __m128 &v) :m(v) { }
	INLINE CLASS_NAME(const CLASS_NAME &rhs) :m(rhs.m) { }
	INLINE explicit CLASS_NAME(float v) :m(_mm_set1_ps(v)) { }

	INLINE const CLASS_NAME &operator=(const CLASS_NAME &rhs) { m=rhs.m; return *this; }
	INLINE CLASS_NAME operator-() const { return _mm_sub_ps(_mm_setzero_ps(),m); }

	INLINE const CLASS_NAME &operator+=(const CLASS_NAME &v) { m=_mm_add_ps(m,v.m); return *this; }
	INLINE const CLASS_NAME &operator-=(const CLASS_NAME &v) { m=_mm_sub_ps(m,v.m); return *this; }
	INLINE const CLASS_NAME &operator*=(const CLASS_NAME &v) { m=_mm_mul_ps(m,v.m); return *this; }
	INLINE const CLASS_NAME &operator/=(const CLASS_NAME &v) { m=_mm_div_ps(m,v.m); return *this; }

	INLINE const CLASS_NAME &operator*=(float s) { m=_mm_mul_ps(m,_mm_set1_ps(s)); return *this; }
	INLINE const CLASS_NAME &operator/=(float s) { m=_mm_div_ps(m,_mm_set1_ps(s)); return *this; }

	ADDITIONAL_CLASS_CODE
};


INLINE CLASS_NAME VSqrt(const CLASS_NAME &v)		{ return _mm_sqrt_ps(v.m); }
INLINE CLASS_NAME VInv(const CLASS_NAME &v)			{ return _mm_nrrcp_ps(v.m); }
INLINE CLASS_NAME VRSqrt(const CLASS_NAME &v)		{ return _mm_nrrsqrt_ps(v.m); }
INLINE CLASS_NAME VAbs(const CLASS_NAME &v)			{ return _mm_and_ps(_mm_set1_ps(BitCast<float,u32>(0x7fffffff)),v.m); }
INLINE CLASS_NAME VFastInv(const CLASS_NAME &v)		{ return _mm_rcp_ps(v.m); }
INLINE CLASS_NAME VFastRSqrt(const CLASS_NAME &v)	{ return _mm_rsqrt_ps(v.m); }


INLINE CLASS_NAME VMin(const CLASS_NAME &a,const CLASS_NAME &b) { return _mm_min_ps(a.m,b.m); }
INLINE CLASS_NAME VMax(const CLASS_NAME &a,const CLASS_NAME &b) { return _mm_max_ps(a.m,b.m); }

INLINE CLASS_NAME operator+(const CLASS_NAME &a,const CLASS_NAME &b) { CLASS_NAME out(a); out+=b; return out; }
INLINE CLASS_NAME operator-(const CLASS_NAME &a,const CLASS_NAME &b) { CLASS_NAME out(a); out-=b; return out; }
INLINE CLASS_NAME operator*(const CLASS_NAME &a,const CLASS_NAME &b) { CLASS_NAME out(a); out*=b; return out; }
INLINE CLASS_NAME operator/(const CLASS_NAME &a,const CLASS_NAME &b) { CLASS_NAME out(a); out/=b; return out; }

INLINE CLASS_NAME operator*(const CLASS_NAME &a,float v) { CLASS_NAME out(a); out*=v; return out; }
INLINE CLASS_NAME operator/(const CLASS_NAME &a,float v) { CLASS_NAME out(a); out/=v; return out; }


INLINE CLASS_NAME Condition(bool test_,const CLASS_NAME &v1,const CLASS_NAME &v2) {
	__m128 test=_mm_bool2mask(test_);
	return _mm_or_ps(_mm_and_ps(test,v1.m),_mm_andnot_ps(test,v2.m));
}
INLINE CLASS_NAME Condition(bool test_,const CLASS_NAME &v1) {
	__m128 test=_mm_bool2mask(test_);
	return _mm_and_ps(test,v1.m);
}

