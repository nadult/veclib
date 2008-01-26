class SSEMASK_NEG_CLASS;

class SSEMASK_CLASS
{
public:
	INLINE SSEMASK_CLASS() {
	}
	INLINE SSEMASK_CLASS(const __m128 &v) :m(v) {
	}

	INLINE SSEMASK_CLASS operator^(const SSEMASK_CLASS &v) const {
		return _mm_xor_ps(m,v.m);
	}
	INLINE SSEMASK_CLASS operator&&(const SSEMASK_CLASS &v) const {
		return _mm_and_ps(m,v.m);
	}

	INLINE SSEMASK_CLASS operator||(const SSEMASK_CLASS &v) const {
		return _mm_or_ps(m,v.m);
	}

	SSEMASK_ADDITIONAL_CODE

	__m128 m;
};

template <int mask> class Const<SSEMASK_CLASS,mask,1> {
	static const SSEMASK_CLASS value;
public:
	INLINE static SSEMASK_CLASS Value() { return value; }
};
template <int mask> const SSEMASK_CLASS Const<SSEMASK_CLASS,mask,1>::value=_mm_set1_ps(UValue(mask).f);


class SSEMASK_NEG_CLASS
{
public:
	INLINE SSEMASK_NEG_CLASS(const __m128 &v) :m(v) {
	}

	INLINE SSEMASK_NEG_CLASS operator^(const SSEMASK_CLASS &v) const {
		return _mm_xor_ps(m,v.m);
	}
	INLINE SSEMASK_CLASS operator^(const SSEMASK_NEG_CLASS &v) const {
		return _mm_xor_ps(m,v.m);
	}
	INLINE SSEMASK_CLASS operator!() const {
		return SSEMASK_CLASS(m);
	}

	INLINE SSEMASK_CLASS operator&&(const SSEMASK_CLASS &v) const {
		return _mm_andnot_ps(m,v.m);
	}
	INLINE SSEMASK_NEG_CLASS operator&&(const SSEMASK_NEG_CLASS &v) const {
		return _mm_or_ps(m,v.m);
	}

	INLINE SSEMASK_NEG_CLASS operator||(const SSEMASK_NEG_CLASS &v) const {
		return _mm_and_ps(m,v.m);
	}
	INLINE SSEMASK_CLASS operator||(const SSEMASK_CLASS &v) const {
		return _mm_or_ps(_mm_andnot_ps(m,Const<SSEMASK_CLASS,0xffffffff>::Value().m),v.m);
	}
	operator SSEMASK_CLASS() const {
		return _mm_andnot_ps(m,Const<SSEMASK_CLASS,0xffffffff>::Value().m);
	}

	SSEMASK_NEG_ADDITIONAL_CODE

	__m128 m;
};

INLINE SSEMASK_NEG_CLASS operator!(const SSEMASK_CLASS &v) {
	return SSEMASK_NEG_CLASS(v.m);
}
INLINE SSEMASK_NEG_CLASS operator^(const SSEMASK_CLASS &a,const SSEMASK_NEG_CLASS &b) {
	return _mm_xor_ps(a.m,b.m);
}
INLINE SSEMASK_CLASS operator&&(const SSEMASK_CLASS &a,const SSEMASK_NEG_CLASS &b) {
	return _mm_andnot_ps(b.m,a.m);
}
INLINE SSEMASK_CLASS operator||(const SSEMASK_CLASS &a,const SSEMASK_NEG_CLASS &b) {
	return _mm_or_ps(a.m,_mm_andnot_ps(b.m,Const<SSEMASK_CLASS,0xffffffff>::Value().m));
}

