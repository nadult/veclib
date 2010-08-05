#ifndef VECLIB_ALTIVEC_F32_H
#define VECLIB_ALTIVEC_F32_H

class f32x4;
class f32x4b;

const f32x4 Inv(const f32x4);

class f32x4 
{
public:
	f32x4() { }
    f32x4(float a,float b,float c,float d) { vf = (vector float){a, b, c, d}; }
	f32x4(float v) {
		vector float vec = vec_ld(0, &v);
        vf = vec_splat(vec_perm(vec, vec, vec_lvsl(0, &v)), 0);
	}
	f32x4(const f32x4 &v) { vf = v.vf; }
	f32x4(vector float tvf) { vf = tvf; }
	void operator=(const f32x4 &v) { vf = v.vf; }

	const f32x4 operator+=(const f32x4 v) {
		vf = vec_add(vf, v.vf);
		return *this;
	}
	const f32x4 operator-=(const f32x4 v) {
		vf = vec_sub(vf, v.vf);
		return *this;
	}
	const f32x4 operator*=(const f32x4 v) {
		vf = vec_madd(vf, v.vf, (vector float)vec_splat_u8(0));
		return *this;
	}
	const f32x4 operator/=(const f32x4 den) {
  		vector float y0, y0numer;
		y0 = vec_re(den.vf);
		y0numer = vec_madd(vf, y0, (vector float){0.0f, 0.0f, 0.0f, 0.0f});
		vf = vec_madd(vec_nmsub(den.vf, y0, (vector float){1.0f, 1.0f, 1.0f, 1.0f}), y0numer, y0numer);
		return *this;
	}

	const f32x4 operator-() const {
		return vec_sub((vector float)vec_splat_u8(0), vf);
	}

	operator f32*() { return f; }
	operator const f32*() const { return f; }

	union {
		float f[4];
		vector float vf;
	};
};

class f32x4b
{
public:
	f32x4b() { }
	f32x4b(bool a, bool b, bool c, bool d)
		{ i[0] = a? ~0 : 0; i[1] = b? ~0 : 0; i[2] = c? ~0 : 0; i[3] = d? ~0 : 0; }
	f32x4b(bool v) {
		unsigned int mask = -(int)v;
		vector unsigned int vec = vec_ld(0, &mask);
		vi = vec_splat(vec_perm(vec, vec, vec_lvsl(0, &mask)), 0);
	}
	f32x4b(const vector unsigned int t) { vi = t; }
	f32x4b(const f32x4b &rhs) { vi = rhs.vi; }
	void operator=(const f32x4b &rhs) { vi = rhs.vi; }

	const f32x4b operator^(const f32x4b t) const {
		return vec_xor(vi, t.vi);
	}
	const f32x4b operator&&(const f32x4b t) const {
		return vec_and(vi, t.vi);
	}
	const f32x4b operator||(const f32x4b t) const {
		return vec_or(vi, t.vi);
	}
	const f32x4b operator!() const {
		return vec_nor(vi, vi);
	}

private:
	friend bool ForAny(const f32x4b);
	friend bool ForAll(const f32x4b);
	friend int ForWhich(const f32x4b);
	friend const f32x4 Condition(const f32x4b, const f32x4, const f32x4);
	friend const f32x4 Condition(const f32x4b, const f32x4);
	friend class i32x4b;

	union {
		int i[4];
		vector unsigned int vi;
	};
};

inline bool ForAny(const f32x4b v)  { return vec_any_eq(v.vi, ((vector unsigned int){~0,~0,~0,~0})); }
inline bool ForAll(const f32x4b v)  { return vec_all_eq(v.vi, ((vector unsigned int){~0,~0,~0,~0})); }
inline int ForWhich(const f32x4b v)
	{ return (v.i[0] & 1) | ((v.i[1] & 1) << 1) | ((v.i[2] & 1) << 2) | ((v.i[3] & 1) << 3); }

inline const f32x4b operator==(const f32x4 a, const f32x4 b)
	{ return (vector unsigned int)vec_cmpeq(a.vf, b.vf); }
inline const f32x4b operator!=(const f32x4 a, const f32x4 b)
	{ return !(a == b); }
inline const f32x4b operator>=(const f32x4 a, const f32x4 b)
	{ return (vector unsigned int)vec_cmpge(a.vf, b.vf); }
inline const f32x4b operator<=(const f32x4 a, const f32x4 b)
	{ return (vector unsigned int)vec_cmple(a.vf, b.vf); }
inline const f32x4b operator>(const f32x4 a, const f32x4 b)
	{ return (vector unsigned int)vec_cmpgt(a.vf, b.vf); }
inline const f32x4b operator<(const f32x4 a, const f32x4 b)
	{ return (vector unsigned int)vec_cmpgt(b.vf, a.vf); }

inline const f32x4 Inv(const f32x4 v) {
	vector float reciprocal = vec_re(v.vf);
	return vec_madd(reciprocal,
			vec_nmsub(reciprocal, v.vf, vec_ctf(vec_splat_u32(1), 0)), reciprocal);
}

inline const f32x4 operator+(const f32x4 a, const f32x4 b)
	{ return vec_add(a.vf, b.vf); }
inline const f32x4 operator-(const f32x4 a, const f32x4 b)
	{ return vec_sub(a.vf, b.vf); }
inline const f32x4 operator*(const f32x4 a, const f32x4 b)
	{ return vec_madd(a.vf, b.vf, (vector float)vec_splat_u8(0)); }
inline const f32x4 operator/(const f32x4 num, const f32x4 den) {
  vector float y0, y0numer;
  y0 = vec_re(den.vf);
  y0numer = vec_madd(num.vf, y0, (vector float){0.0f, 0.0f, 0.0f, 0.0f});
  return vec_madd(vec_nmsub(den.vf, y0, (vector float){1.0f, 1.0f, 1.0f, 1.0f}), y0numer, y0numer);
}

inline const f32x4 RSqrt(const f32x4 v) {
	const vector float kMinusZero = (vector float)vec_sl(vec_splat_u32(-1), vec_splat_u32(-1));
	const vector float kOne = vec_ctf(vec_splat_u32( 1 ), 0);
	const vector float kOneHalf = vec_ctf(vec_splat_u32( 1 ), 1);
	
	vector float sqrtReciprocalEstimate = vec_rsqrte(v.vf);
	vector float reciprocalEstimate =
		vec_madd(sqrtReciprocalEstimate, sqrtReciprocalEstimate, kMinusZero);
	vector float halfSqrtReciprocalEst =
		vec_madd(sqrtReciprocalEstimate, kOneHalf, kMinusZero);
	vector float term1 = vec_nmsub(v.vf, reciprocalEstimate, kOne);

	return vec_madd(term1, halfSqrtReciprocalEst, sqrtReciprocalEstimate);
}

inline const f32x4 Sqrt(const f32x4 v) { return RSqrt(v) * v; }

inline const f32x4 FastInv(const f32x4 v) {
	return vec_re(v.vf);
}

inline const f32x4 FastRSqrt(const f32x4 v)
	{ return vec_rsqrte(v.vf); }


inline const f32x4 Abs(const f32x4 &v)
	{ return vec_abs(v.vf); }
inline int SignMask(const f32x4 &v)
	{ return (v[0] < 0.0f? 1 : 0) | (v[1] < 0.0f? 2 : 0) | (v[2] < 0.0f? 4 : 0) | (v[3] < 0.0f? 8 : 0); }

inline const f32x4 Min(const f32x4 a, const f32x4 b)
	{ return vec_min(a.vf, b.vf); }
inline const f32x4 Max(const f32x4 a, const f32x4 b)
	{ return vec_max(a.vf, b.vf); }

inline const f32x4 Condition(const f32x4b t, const f32x4 a, const f32x4 b)
	{ return vec_sel(b.vf, a.vf, t.vi); }

inline const f32x4 Condition(const f32x4b t, const f32x4 a)
	{ return vec_sel(f32x4(0.0f).vf, a.vf, t.vi); }

template <>
struct ScalarInfo<f32x4> {
	enum { multiplicity = 4, floatingPoint = 1 };
	typedef f32x4b TBool;

	static const f32x4b ElementMask(int n) {
		static f32x4b elems[4] = {
			f32x4b(1, 0, 0, 0),
			f32x4b(0, 1, 0, 0),
			f32x4b(0, 0, 1, 0),
			f32x4b(0, 0, 0, 1),
		};

		return elems[n];
	}
};

inline void Broadcast(float in, f32x4 &out)
	{ out = f32x4(in, in, in, in); }
inline void Convert(const float in[4], f32x4 &out)
	{ out = f32x4(in[0], in[1], in[2], in[3]); }
inline void Convert(f32x4 in, float out[4])
	{ out[0] = in[0]; out[1] = in[1]; out[2] = in[2]; out[3] = in[3]; }

inline void Convert(float x, float y, float z, float w, f32x4 &out)
	{ out = f32x4(x, y, z, w); }
inline void Convert(f32x4 in, float &outX, float &outY, float &outZ, float &outW)
	{ outX = in[0]; outY = in[1]; outZ = in[2]; outW = in[3]; }

#endif

