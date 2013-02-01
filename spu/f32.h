#ifndef VECLIB_SPU_F32_H
#define VECLIB_SPU_F32_H

class f32x4b;

class f32x4 
{
public:
	f32x4() { }
    f32x4(float a,float b,float c,float d) { vf =(vec_float4){a, b, c, d}; }
	f32x4(float v) { vf = spu_splats(v); }
	f32x4(const f32x4 &v) { vf = v.vf; }
	f32x4(vector float tvf) { vf = tvf; }
	void operator=(const f32x4 &v) { vf = v.vf; }

	const f32x4 operator+=(const f32x4 v) {
		vf = spu_add(vf, v.vf);
		return *this;
	}
	const f32x4 operator-=(const f32x4 v) {
		vf = spu_sub(vf, v.vf);
		return *this;
	}
	const f32x4 operator*=(const f32x4 v) {
		vf = spu_mul(vf, v.vf);
		return *this;
	}
	const f32x4 operator/=(const f32x4 v) {
		vector float oneish = (vec_float4)spu_splats(0x3f800001);
		vector float y0 = spu_re(v.vf);
		vector float y0numer = spu_mul(vf, y0);
		vf = spu_madd(spu_nmsub(v.vf, y0, oneish ), y0numer, y0numer);
		return *this;
	}

	const f32x4 operator-() const
		{ return (vec_float4)spu_xor((vec_uint4)vf, spu_splats(0x80000000)); }

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
		{ vu = (vec_uint4){a? ~0u : 0u, b? ~0u : 0u, c? ~0u : 0u, d? ~0u : 0u}; }
	f32x4b(bool v)
		{ vu = spu_splats(v?0xffffffffu : 0u); }
	f32x4b(const vector unsigned int t) { vu = t; }
	f32x4b(const f32x4b &rhs) { vu = rhs.vu; }
	void operator=(const f32x4b &rhs) { vu = rhs.vu; }

	const f32x4b operator^(const f32x4b t) const { return spu_xor(vu, t.vu); }
	const f32x4b operator&(const f32x4b t) const { return spu_and(vu, t.vu); }
	const f32x4b operator|(const f32x4b t) const { return spu_or(vu, t.vu); }
	const f32x4b operator&&(const f32x4b t) const { return spu_and(vu, t.vu); }
	const f32x4b operator||(const f32x4b t) const { return spu_or(vu, t.vu); }
	const f32x4b operator!() const { return spu_nor(vu, vu); }

private:
	friend bool ForAny(const f32x4b);
	friend bool ForAll(const f32x4b);
	friend int ForWhich(const f32x4b);
	friend const f32x4 Condition(const f32x4b, const f32x4, const f32x4);
	friend const f32x4 Condition(const f32x4b, const f32x4);
	friend class i32x4b;

	union {
		int i[4];
		unsigned u[4];
		vector unsigned int vu;
	};
};

inline bool ForAny(const f32x4b v)  { return spu_extract(spu_orx(v.vu), 0)? 1 : 0; }
inline bool ForAll(const f32x4b v)  { return !ForAny(!v); }
inline int ForWhich(const f32x4b v)
	{ return (v.i[0] & 1) | ((v.i[1] & 1) << 1) | ((v.i[2] & 1) << 2) | ((v.i[3] & 1) << 3); }


	//TODO: tu sa bledy (widac w test_float)
inline const f32x4b operator==(const f32x4 a, const f32x4 b)
	{ return (vec_uint4)spu_cmpeq(a.vf, b.vf); }
inline const f32x4b operator!=(const f32x4 a, const f32x4 b)
	{ return !(a == b); }
inline const f32x4b operator>(const f32x4 a, const f32x4 b)
	{ return (vec_uint4)spu_cmpgt(a.vf, b.vf); }
inline const f32x4b operator<(const f32x4 a, const f32x4 b)
	{ return (vec_uint4)spu_cmpgt(b.vf, a.vf); }
inline const f32x4b operator>=(const f32x4 a, const f32x4 b)
	{ return !(a < b); }
inline const f32x4b operator<=(const f32x4 a, const f32x4 b)
	{ return !(a > b); }

inline f32x4 MulAdd(const f32x4 a, const f32x4 b, const f32x4 c)
	{ return spu_madd(a.vf, b.vf, c.vf); }
inline f32x4 MulSub(const f32x4 a, const f32x4 b, const f32x4 c)
	{ return spu_msub(a.vf, b.vf, c.vf); }

inline const f32x4 operator+(const f32x4 a, const f32x4 b)
	{ return spu_add(a.vf, b.vf); }
inline const f32x4 operator-(const f32x4 a, const f32x4 b)
	{ return spu_sub(a.vf, b.vf); }
inline const f32x4 operator*(const f32x4 a, const f32x4 b)
	{ return spu_mul(a.vf, b.vf); }
inline const f32x4 operator/(const f32x4 a, const f32x4 b) {
	vector float oneish = (vec_float4)spu_splats(0x3f800001);
	vector float y0 = spu_re(b.vf);
	vector float y0numer = spu_mul(a.vf, y0);
	return spu_madd(spu_nmsub( b.vf, y0, oneish ), y0numer, y0numer);
}

inline const f32x4 Sqrt(const f32x4 v) {
	vector float oneish = (vec_float4)spu_splats(0x3f800001);
	vector float y0 = spu_rsqrte(v.vf);
	vector float y0x = spu_mul(y0, v.vf);
	vector float y0xhalf = spu_mul(y0x, spu_splats(0.5f));
	return spu_madd(spu_nmsub(y0, y0x, oneish), y0xhalf, y0x);
}
	
inline const f32x4 Inv(const f32x4 v) {
	vector float oneish = (vec_float4)spu_splats(0x3f800001);
	vector float y0 = spu_re(v.vf);
	return spu_madd( spu_nmsub(v.vf, y0, oneish), y0, y0);
}

inline const f32x4 RSqrt(const f32x4 &v) {
	vector float oneish = (vec_float4)spu_splats(0x3f800001);
	vector float y0 = spu_rsqrte(v.vf);
	vector float y0x = spu_mul(y0, v.vf);
	vector float y0half = spu_mul(y0, spu_splats(0.5f));
	return spu_madd(spu_nmsub(y0, y0x, oneish ), y0half, y0);
}

inline const f32x4 FastInv(const f32x4 v)	
	{ return spu_re(v.vf); }
inline const f32x4 FastRSqrt(const f32x4 v)
	{ return spu_rsqrte(v.vf); }


inline const f32x4 Abs(const f32x4 v)
	{ return (vec_float4)spu_andc((vec_uint4)v.vf, spu_splats(0x80000000)); }
inline int SignMask(const f32x4 &v)
	{ return (v[0] < 0.0f? 1 : 0) | (v[1] < 0.0f? 2 : 0) | (v[2] < 0.0f? 4 : 0) | (v[3] < 0.0f? 8 : 0); }

inline const f32x4 Min(const f32x4 a,const f32x4 b)
	{ return spu_sel(a.vf, b.vf, spu_cmpgt(a.vf, b.vf)); }
inline const f32x4 Max(const f32x4 a,const f32x4 b)
	{ return spu_sel(b.vf, a.vf, spu_cmpgt(a.vf, b.vf)); }

inline const f32x4 Condition(const f32x4b t, const f32x4 a, const f32x4 b)
	{ return spu_sel(b.vf, a.vf, t.vu); }

inline const f32x4 Condition(const f32x4b t, const f32x4 a)
	{ return spu_sel(f32x4(0.0f).vf, a.vf, t.vu); }

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
	{ out = f32x4(in); }
inline void Convert(const float in[4], f32x4 &out)
	{ out = f32x4(in[0], in[1], in[2], in[3]); }
inline void Convert(f32x4 in, float out[4])
	{ out[0] = in[0]; out[1] = in[1]; out[2] = in[2]; out[3] = in[3]; }

inline void Convert(float x, float y, float z, float w, f32x4 &out)
	{ out = f32x4(x, y, z, w); }
inline void Convert(f32x4 in, float &outX, float &outY, float &outZ, float &outW)
	{ outX = in[0]; outY = in[1]; outZ = in[2]; outW = in[3]; }

#endif

