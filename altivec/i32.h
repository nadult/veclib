#ifndef VECLIB_ALTIVEC_I32_H
#define VECLIB_ALTIVEC_I32_H


#include "vecbase.h"
#include "altivec/f32.h"

class i32x4b;

//TODO usunac i32x4b i wszystko robic na i32x4
class i32x4
{
public:
	i32x4() { }
	i32x4(int v) { vi = (vector int){v, v, v, v}; }
	i32x4(unsigned v) { vu = (vector unsigned int){v, v, v, v}; }
	i32x4(int a, int b, int c, int d) { vi = (vector int){a, b, c, d}; }
	explicit i32x4(const i32x4b);

	explicit i32x4(const f32x4 &f) { i[0] = f[0]; i[1] = f[1]; i[2] = f[2]; i[3] = f[3]; }
	operator const f32x4() const { return f32x4(i[0], i[1], i[2], i[3]); }
	i32x4(const i32x4 &rhs) { vi = rhs.vi; }
	void operator=(const i32x4 &rhs) { vi = rhs.vi; }
	i32x4(const vector int rhs) { vi = rhs; }
	i32x4(const vector unsigned int rhs) { vu = rhs; }

	const i32x4 operator+=(const i32x4 &v) {
		vi = vec_add(vi, v.vi);
		return *this;
	}
	const i32x4 operator-=(const i32x4 &v) {
		vi = vec_sub(vi, v.vi);
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
	const i32x4 operator&=(const i32x4 &v) {
		vi = vec_and(vi, v.vi);	
		return *this;
	}
	const i32x4 operator|=(const i32x4 &v) {
		vi = vec_or(vi, v.vi);
		return *this;
	}
	const i32x4 operator^=(const i32x4 &v) {
		vi = vec_xor(vi, v.vi);
		return *this;
	}
	const i32x4 operator<<=(const i32x4 &v) {
		vu = vec_sl(vu, v.vu); //TODO: check
		return *this;
	}
	const i32x4 operator>>=(const i32x4 &v) {
		vu = vec_sr(vu, v.vu);
		return *this;
	}

	const i32x4 operator-() const { return vec_sub(i32x4(0).vi, vi); }
	const i32x4 operator~() const { return vec_nor(vi, vi); }
	const i32x4b operator!() const;

	operator i32*() { return i; }
	operator const i32*() const { return i; }

	union {
		i32 i[4];
		u32 u[4];
		vector int vi;
		vector unsigned int vu;
	};
};

inline const i32x4 operator+(const i32x4 a, const i32x4 b)
	{ return vec_add(a.vi, b.vi); }
inline const i32x4 operator-(const i32x4 a, const i32x4 b)
	{ return vec_sub(a.vi, b.vi); }
inline const i32x4 operator*(const i32x4 a, const i32x4 b)
	{ return i32x4(a[0] * b[0], a[1] * b[1], a[2] * b[2], a[3] * b[3]); }
inline const i32x4 operator/(const i32x4 a, const i32x4 b)
	{ return i32x4(a[0] / b[0], a[1] / b[1], a[2] / b[2], a[3] / b[3]); }
inline const i32x4 operator%(const i32x4 a, const i32x4 b)
	{ return i32x4(a[0] % b[0], a[1] % b[1], a[2] % b[2], a[3] % b[3]); }
inline const i32x4 operator&(const i32x4 a, const i32x4 b)
	{ return vec_and(a.vi, b.vi); }
inline const i32x4 operator|(const i32x4 a, const i32x4 b)
	{ return vec_or(a.vi, b.vi); }
inline const i32x4 operator^(const i32x4 a, const i32x4 b)
	{ return vec_xor(a.vi, b.vi); }
inline const i32x4 operator<<(const i32x4 a, const i32x4 b)
	{ return vec_sl(a.vu, b.vu); }
inline const i32x4 operator>>(const i32x4 a, const i32x4 b)
	{ return vec_sr(a.vu, b.vu); }


template <unsigned bits>
inline const i32x4 Shl(const i32x4 &in)
	{ return in << i32x4(bits); }

template <unsigned bits>
inline const i32x4 Shr(const i32x4 &in)
	{ return in >> i32x4(bits); }

class i32x4b
{
public:
	i32x4b() { }
	i32x4b(bool a, bool b, bool c, bool d)
		{ i[0] = a? ~0 : 0; i[1] = b? ~0 : 0; i[2] = c? ~0 : 0; i[3] = d? ~0 : 0; }
	i32x4b(bool v) {
		unsigned int mask = -(int)v;
		vector unsigned int vec = vec_ld(0, &mask);
		vi = vec_splat(vec_perm(vec, vec, vec_lvsl(0, &mask)), 0);
	}
	i32x4b(const vector unsigned int t) { vi = t; }
	i32x4b(const i32x4b &rhs) { vi = rhs.vi; }
	void operator=(const i32x4b &rhs) { vi = rhs.vi; }
	i32x4b(const f32x4b tv) { vi = tv.vi; }

	const i32x4b operator^(const i32x4b t) const {
		return vec_xor(vi, t.vi);
	}
	const i32x4b operator&&(const i32x4b t) const {
		return vec_and(vi, t.vi);
	}
	const i32x4b operator||(const i32x4b t) const {
		return vec_or(vi, t.vi);
	}
	const i32x4b operator!() const {
		return vec_nor(vi, vi);
	}

private:
	friend bool ForAny(const i32x4b);
	friend bool ForAll(const i32x4b);
	friend int ForWhich(const i32x4b);
	friend const i32x4 Condition(const i32x4b, const i32x4, const i32x4);
	friend const i32x4 Condition(const i32x4b, const i32x4);
	friend i32x4::i32x4(const i32x4b);

	union {
		int i[4];
		vector unsigned int vi;
	};
};

inline const i32x4b i32x4::operator!() const
	{ return i32x4b(!i[0], !i[1], !i[2], !i[3]); }

inline i32x4::i32x4(const i32x4b v) { vu = v.vi; }

inline bool ForAny(const i32x4b v)  { return vec_any_eq(v.vi, ((vector unsigned int){~0,~0,~0,~0})); }
inline bool ForAll(const i32x4b v)  { return vec_all_eq(v.vi, ((vector unsigned int){~0,~0,~0,~0})); }
inline int ForWhich(const i32x4b v)
	{ return (v.i[0] & 1) | ((v.i[1] & 1) << 1) | ((v.i[2] & 1) << 2) | ((v.i[3] & 1) << 3); }

inline const i32x4b operator>(const i32x4 a, const i32x4 b)
	{ return (vector unsigned int)vec_cmpgt(a.vi, b.vi); }
inline const i32x4b operator<(const i32x4 a, const i32x4 b)
	{ return (vector unsigned int)vec_cmpgt(b.vi, a.vi); }
inline const i32x4b operator==(const i32x4 a, const i32x4 b)
	{ return (vector unsigned int)vec_cmpeq(a.vi, b.vi); }
inline const i32x4b operator!=(const i32x4 a, const i32x4 b)
	{ return !(a == b); }
inline const i32x4b operator>=(const i32x4 a, const i32x4 b)
	{ return !(a < b); }
inline const i32x4b operator<=(const i32x4 a, const i32x4 b)
	{ return !(a > b); }

inline const i32x4 Abs(const i32x4 &v)
	{ return vec_abs(v.vi); }
inline int SignMask(const i32x4 &v)
	{ return (v[0] < 0? 1 : 0) | (v[1] < 0? 2 : 0) | (v[2] < 0? 4 : 0) | (v[3] < 0? 8 : 0); }

inline const i32x4 Min(const i32x4 a, const i32x4 b)
	{ return vec_min(a.vi, b.vi); }
inline const i32x4 Max(const i32x4 a, const i32x4 b)
	{ return vec_max(a.vi, b.vi); }

inline const i32x4 Condition(const i32x4b t, const i32x4 a, const i32x4 b)
	{ return vec_sel(b.vi, a.vi, t.vi); }

inline const i32x4 Condition(const i32x4b t, const i32x4 a)
	{ return vec_sel(i32x4(0).vi, a.vi, t.vi); }

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
	{ return i32x4(v + 0.5f); }
inline const i32x4 Trunc(const f32x4 &v)
	{ return i32x4(v[0], v[1], v[2], v[3]); }

inline void Cast(const i32x4 &src, f32x4 &dst) {
   dst = f32x4((vector float)src.vi);
}

inline void Cast(const f32x4 &src, i32x4 &dst) {
   dst = i32x4((vector int)src.vf);
}

#endif

