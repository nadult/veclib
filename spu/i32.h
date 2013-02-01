#ifndef VECLIB_SPU_I32_H
#define VECLIB_SPU_I32_H


#include "vecbase.h"
#include "spu/f32.h"

class i32x4b;

//TODO usunac i32x4b i wszystko robic na i32x4
class i32x4
{
public:
	i32x4() { }
	i32x4(int v) { vi = spu_splats(v); }
	i32x4(unsigned v) { vu = spu_splats(v); }
	i32x4(int a, int b, int c, int d) { vi = (vec_int4){a, b, c, d}; }
	i32x4(vec_uint4 tvu) { vu = tvu; }
	i32x4(vec_int4 tvi) { vi = tvi; }
	i32x4(const i32x4 &rhs) { vi = rhs.vi; }
	void operator=(const i32x4 &rhs) { vi = rhs.vi; }
	explicit i32x4(const i32x4b);

	explicit i32x4(const f32x4 f) { vi = spu_convts(f.vf, 0); }
	operator const f32x4() const { return f32x4(spu_convtf(vi, 0)); }

	const i32x4 operator+=(const i32x4 v) {
		vi = spu_add(vi, v.vi);
		return *this;
	}
	const i32x4 operator-=(const i32x4 v) {
		vi = spu_sub(vi, v.vi);
		return *this;
	}
	const i32x4 operator*=(const i32x4 &v) {
		i[0] *= v[0]; i[1] *= v[1]; i[2] *= v[2]; i[3] *= v[3];
		return *this;
	}
	const i32x4 operator/=(const i32x4 &v) {
		i[0] /= v[0]; i[1] /= v[1]; i[2] /= v[2]; i[3] /= v[3];
		return *this;
	}
	const i32x4 operator%=(const i32x4 &v) {
		i[0] %= v[0]; i[1] %= v[1]; i[2] %= v[2]; i[3] %= v[3];
		return *this;
	}
	const i32x4 operator&=(const i32x4 v) {
		vi = spu_and(vi, v.vi);
		return *this;
	}
	const i32x4 operator|=(const i32x4 v) {
		vi = spu_or(vi, v.vi);
		return *this;
	}
	const i32x4 operator^=(const i32x4 v) {
		vi = spu_xor(vi, v.vi);
		return *this;
	}
	const i32x4 operator<<=(const i32x4 &v) {
		i[0] <<= v[0]; i[1] <<= v[1]; i[2] <<= v[2]; i[3] <<= v[3];
		return *this;
	}
	const i32x4 operator>>=(const i32x4 &v) {
		i[0] >>= v[0]; i[1] >>= v[1]; i[2] >>= v[2]; i[3] >>= v[3];
		return *this;
	}

	const i32x4 operator-() const;
	const i32x4 operator~() const { return spu_nor(vu, vu); }
	const i32x4b operator!() const;

	operator i32*() { return i; }
	operator const i32*() const { return i; }

	union {
		i32 i[4];
		u32 u[4];
		vec_uint4 vu;
		vec_int4 vi;
	};
};

inline const i32x4 operator+(const i32x4 a, const i32x4 b)
	{ return spu_add(a.vi, b.vi); }
inline const i32x4 operator-(const i32x4 a, const i32x4 b)
	{ return spu_sub(a.vi, b.vi); }
	
inline const i32x4 i32x4::operator-() const { return i32x4(0) - i32x4(vi); }
inline const i32x4 operator*(const i32x4 &a, const i32x4 &b)
	{ return i32x4(a[0] * b[0], a[1] * b[1], a[2] * b[2], a[3] * b[3]); }
inline const i32x4 operator/(const i32x4 &a, const i32x4 &b)
	{ return i32x4(a[0] / b[0], a[1] / b[1], a[2] / b[2], a[3] / b[3]); }
inline const i32x4 operator%(const i32x4 &a, const i32x4 &b)
	{ return i32x4(a[0] % b[0], a[1] % b[1], a[2] % b[2], a[3] % b[3]); }
inline const i32x4 operator&(const i32x4 &a, const i32x4 &b)
	{ return spu_and(a.vi, b.vi); }
inline const i32x4 operator|(const i32x4 a, const i32x4 b)
	{ return spu_or(a.vi, b.vi); }
inline const i32x4 operator^(const i32x4 a, const i32x4 b)
	{ return spu_xor(a.vi, b.vi); }
inline const i32x4 operator<<(const i32x4 &a, const i32x4 &b)
	{ return i32x4(a[0] << b[0], a[1] << b[1], a[2] << b[2], a[3] << b[3]); }
inline const i32x4 operator>>(const i32x4 &a, const i32x4 &b)
	{ return i32x4(a[0] >> b[0], a[1] >> b[1], a[2] >> b[2], a[3] >> b[3]); }


template <unsigned bits>
inline const i32x4 Shl(const i32x4 in)
	{ return spu_sl(in.vi, bits); }

template <unsigned bits>
inline const i32x4 Shr(const i32x4 in)
	{ return spu_sl(in.vi, -bits); }

class i32x4b
{
public:
	i32x4b() { }
	i32x4b(bool a, bool b, bool c, bool d)
		{ vu = (vec_uint4){a? ~0u : 0u, b? ~0u : 0u, c? ~0u : 0u, d? ~0u : 0u}; }
	i32x4b(bool v)
		{ vu = spu_splats(v?0xffffffffu : 0u); }
	i32x4b(const vec_uint4 t) { vu = t; }
	i32x4b(const i32x4b &rhs) { vu = rhs.vu; }
	i32x4b(const f32x4b rhs) { vu = rhs.vu; }
	operator const f32x4b() const { return vu; }
	void operator=(const i32x4b &rhs) { vu = rhs.vu; }

	const i32x4b operator^(const i32x4b t) const { return spu_xor(vu, t.vu); }
	const i32x4b operator&(const i32x4b t) const { return spu_and(vu, t.vu); }
	const i32x4b operator|(const i32x4b t) const { return spu_or(vu, t.vu); }
	const i32x4b operator&&(const i32x4b t) const { return spu_and(vu, t.vu); }
	const i32x4b operator||(const i32x4b t) const { return spu_or(vu, t.vu); }
	const i32x4b operator!() const { return spu_nor(vu, vu); }

private:
	friend bool ForAny(const i32x4b);
	friend bool ForAll(const i32x4b);
	friend int ForWhich(const i32x4b);
	friend const i32x4 Condition(const i32x4b, const i32x4, const i32x4);
	friend const i32x4 Condition(const i32x4b, const i32x4);

	union {
		int i[4];
		unsigned u[4];
		vec_uint4 vu;
	};
};

inline bool ForAny(const i32x4b v)  { return spu_extract(spu_orx(v.vu), 0)? 1 : 0; }
inline bool ForAll(const i32x4b v)  { return !ForAny(!v); }
inline int ForWhich(const i32x4b v)
	{ return (v.i[0] & 1) | ((v.i[1] & 1) << 1) | ((v.i[2] & 1) << 2) | ((v.i[3] & 1) << 3); }

inline const i32x4b operator==(const i32x4 a, const i32x4 b)
	{ return (vec_uint4)spu_cmpeq(a.vi, b.vi); }
inline const i32x4b operator!=(const i32x4 a, const i32x4 b)
	{ return !(a == b); }
inline const i32x4b operator>(const i32x4 a, const i32x4 b)
	{ return (vec_uint4)spu_cmpgt(a.vi, b.vi); }
inline const i32x4b operator<(const i32x4 a, const i32x4 b)
	{ return (vec_uint4)spu_cmpgt(b.vi, a.vi); }
inline const i32x4b operator>=(const i32x4 a, const i32x4 b)
	{ return !(a < b); }
inline const i32x4b operator<=(const i32x4 a, const i32x4 b)
	{ return !(a > b); }

inline const i32x4 Abs(const i32x4 v)
	{ return Condition(v < i32x4(0), -v, v); }
inline int SignMask(const i32x4 v)
	{ return (v[0] < 0? 1 : 0) | (v[1] < 0? 2 : 0) | (v[2] < 0? 4 : 0) | (v[3] < 0? 8 : 0); }

inline const i32x4 Min(const i32x4 a, const i32x4 b)
	{ return spu_sel(a.vi, b.vi, spu_cmpgt(a.vi, b.vi)); }
inline const i32x4 Max(const i32x4 a, const i32x4 b)
	{ return spu_sel(b.vi, a.vi, spu_cmpgt(a.vi, b.vi)); }

inline const i32x4 Condition(const i32x4b t, const i32x4 a, const i32x4 b)
	{ return spu_sel(b.vu, a.vu, t.vu); }

inline const i32x4 Condition(const i32x4b t, const i32x4 a)
	{ return spu_sel(i32x4(0).vu, a.vu, t.vu); }

template<>
struct ScalarInfo<i32x4> {
	enum { multiplicity = 4, floatingPoint = 0 };
	typedef i32x4b TBool;

	inline static i32x4 ElementMask(int n) {
		static i32x4 elems[4]={
			i32x4(~0, 0, 0, 0),
			i32x4(0, ~0, 0, 0),
			i32x4(0, 0, ~0, 0),
			i32x4(0, 0, 0, ~0) };
		return elems[n];
    }
};

inline void Broadcast(int in, i32x4 &out)
	{ out = i32x4(in, in, in, in); }
inline void Convert(const int in[4], i32x4 &out)
	{ out = i32x4(in[0], in[1], in[2], in[3]); }
inline void Convert(i32x4 in, int out[4])
	{ out[0] = in[0]; out[1] = in[1]; out[2] = in[2]; out[3] = in[3]; }

inline void Convert(int x, int y, int z, int w, i32x4 &out)
	{ out = i32x4(x, y, z, w); }
inline void Convert(i32x4 in, int &outX, int &outY, int &outZ, int &outW)
	{ outX = in[0]; outY = in[1]; outZ = in[2]; outW = in[3]; }

//TODO testme
inline const i32x4 Round(const f32x4 &v)
	{ return i32x4(v + f32x4(0.5f)); }
inline const i32x4 Trunc(const f32x4 &v)
	{ return i32x4(v); }

inline void Cast(const i32x4 &src, f32x4 &dst) {
	dst.vf = (vec_float4)src.vi;
}

inline void Cast(const f32x4 &src, i32x4 &dst) {
	dst.vi = (vec_int4)src.vf;
}

#endif

