#ifndef VECLIB_SCALAR_I32_H
#define VECLIB_SCALAR_I32_H


#include "vecbase.h"
#include "scalar/f32.h"

class i32x4b;

//TODO usunac i32x4b i wszystko robic na i32x4
class i32x4
{
public:
	i32x4() { }
	i32x4(int v) { i[0] = i[1] = i[2] = i[3] = v; }
	i32x4(unsigned v) { u[0] = u[1] = u[2] = u[3] = v; }
	i32x4(int a, int b, int c, int d) { i[0] = a; i[1] = b; i[2] = c; i[3] = d; }
	explicit i32x4(const i32x4b);

	explicit i32x4(const f32x4 &f) { i[0] = f[0]; i[1] = f[1]; i[2] = f[2]; i[3] = f[3]; }
	operator const f32x4() const { return f32x4(i[0], i[1], i[2], i[3]); }

	const i32x4 operator+=(const i32x4 &v) {
		i[0] += v[0]; i[1] += v[1]; i[2] += v[2]; i[3] += v[3];
		return *this;
	}
	const i32x4 operator-=(const i32x4 &v) {
		i[0] -= v[0]; i[1] -= v[1]; i[2] -= v[2]; i[3] -= v[3];
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
		i[0] &= v[0]; i[1] &= v[1]; i[2] &= v[2]; i[3] &= v[3];
		return *this;
	}
	const i32x4 operator|=(const i32x4 &v) {
		i[0] |= v[0]; i[1] |= v[1]; i[2] |= v[2]; i[3] |= v[3];
		return *this;
	}
	const i32x4 operator^=(const i32x4 &v) {
		i[0] ^= v[0]; i[1] ^= v[1]; i[2] ^= v[2]; i[3] ^= v[3];
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

	const i32x4 operator-() const { return i32x4(-i[0], -i[1], -i[2], -i[3]); }
	const i32x4 operator~() const { return i32x4(~i[0], ~i[1], ~i[2], ~i[3]); }
	const i32x4b operator!() const;

	operator i32*() { return i; }
	operator const i32*() const { return i; }

	union {
		i32 i[4];
		u32 u[4];
	};
};

inline const i32x4 operator+(const i32x4 &a, const i32x4 &b)
	{ return i32x4(a[0] + b[0], a[1] + b[1], a[2] + b[2], a[3] + b[3]); }
inline const i32x4 operator-(const i32x4 &a, const i32x4 &b)
	{ return i32x4(a[0] - b[0], a[1] - b[1], a[2] - b[2], a[3] - b[3]); }
inline const i32x4 operator*(const i32x4 &a, const i32x4 &b)
	{ return i32x4(a[0] * b[0], a[1] * b[1], a[2] * b[2], a[3] * b[3]); }
inline const i32x4 operator/(const i32x4 &a, const i32x4 &b)
	{ return i32x4(a[0] / b[0], a[1] / b[1], a[2] / b[2], a[3] / b[3]); }
inline const i32x4 operator%(const i32x4 &a, const i32x4 &b)
	{ return i32x4(a[0] % b[0], a[1] % b[1], a[2] % b[2], a[3] % b[3]); }
inline const i32x4 operator&(const i32x4 &a, const i32x4 &b)
	{ return i32x4(a[0] & b[0], a[1] & b[1], a[2] & b[2], a[3] & b[3]); }
inline const i32x4 operator|(const i32x4 &a, const i32x4 &b)
	{ return i32x4(a[0] | b[0], a[1] | b[1], a[2] | b[2], a[3] | b[3]); }
inline const i32x4 operator^(const i32x4 &a, const i32x4 &b)
	{ return i32x4(a[0] ^ b[0], a[1] ^ b[1], a[2] ^ b[2], a[3] ^ b[3]); }
inline const i32x4 operator<<(const i32x4 &a, const i32x4 &b)
	{ return i32x4(a[0] << b[0], a[1] << b[1], a[2] << b[2], a[3] << b[3]); }
inline const i32x4 operator>>(const i32x4 &a, const i32x4 &b)
	{ return i32x4(a[0] >> b[0], a[1] >> b[1], a[2] >> b[2], a[3] >> b[3]); }


template <unsigned bits>
inline const i32x4 Shl(const i32x4 &in)
	{ return i32x4(in[0] << bits, in[1] << bits, in[2] << bits, in[3] << bits); }

template <unsigned bits>
inline const i32x4 Shr(const i32x4 &in)
	{ return i32x4(in[0] >> bits, in[1] >> bits, in[2] >> bits, in[3] >> bits); }

inline const i32x4 Sqrt(const i32x4 &v)
	{ return i32x4(Sqrt(v[0]), Sqrt(v[1]), Sqrt(v[2]), Sqrt(v[3])); }

class i32x4b
{
public:
	i32x4b() { }
	i32x4b(bool a, bool b, bool c, bool d) { v[0] = a; v[1] = b; v[2] = c; v[3] = d; }
	i32x4b(bool a) { v[0] = v[1] = v[2] = v[3] = a; }
	i32x4b(const f32x4b v) { v4 = v.v4; }

	const i32x4b operator^(const i32x4b t) const {
		return MakeV4(v4 ^ t.v4);
	}
	const i32x4b operator&&(const i32x4b t) const {
		return MakeV4(v4 & t.v4);
	}
	const i32x4b operator||(const i32x4b t) const {
		return MakeV4(v4 | t.v4);
	}
	const i32x4b operator!() const {
		return i32x4b(!v[0], !v[1], !v[2], !v[3]);
	}

private:
	static const i32x4b MakeV4(int tv4) {
		i32x4b out;
		out.v4 = tv4;
		return out;
	}
	friend bool ForAny(const i32x4b);
	friend bool ForAll(const i32x4b);
	friend int ForWhich(const i32x4b);
	friend const i32x4 Condition(const i32x4b, const i32x4&, const i32x4&);
	friend const i32x4 Condition(const i32x4b, const i32x4&);
	friend i32x4::i32x4(const i32x4b);

	union {
		bool v[4];
		int v4;
	};
};

inline const i32x4b i32x4::operator!() const
	{ return i32x4b(!i[0], !i[1], !i[2], !i[3]); }

inline i32x4::i32x4(const i32x4b v) {
	i[0] = v.v[0]? 0xffffffff : 0;
	i[1] = v.v[1]? 0xffffffff : 0;
	i[2] = v.v[2]? 0xffffffff : 0;
	i[3] = v.v[3]? 0xffffffff : 0;
}

inline bool ForAny(const i32x4b v)  { return v.v4? 1 : 0; }
inline bool ForAll(const i32x4b v)  { return v.v4 == 0x01010101; }
inline int ForWhich(const i32x4b v) { return v.v[0] | (v.v[1] << 1) | (v.v[2] << 2) | (v.v[3] << 3); }

inline const i32x4b operator==(const i32x4 &a, const i32x4 &b)
	{ return i32x4b(a[0] == b[0], a[1] == b[1], a[2] == b[2], a[3] == b[3]); }
inline const i32x4b operator!=(const i32x4 &a, const i32x4 &b)
	{ return i32x4b(a[0] != b[0], a[1] != b[1], a[2] != b[2], a[3] != b[3]); }
inline const i32x4b operator>=(const i32x4 &a, const i32x4 &b)
	{ return i32x4b(a[0] >= b[0], a[1] >= b[1], a[2] >= b[2], a[3] >= b[3]); }
inline const i32x4b operator<=(const i32x4 &a, const i32x4 &b)
	{ return i32x4b(a[0] <= b[0], a[1] <= b[1], a[2] <= b[2], a[3] <= b[3]); }
inline const i32x4b operator>(const i32x4 &a, const i32x4 &b)
	{ return i32x4b(a[0] > b[0], a[1] > b[1], a[2] > b[2], a[3] > b[3]); }
inline const i32x4b operator<(const i32x4 &a, const i32x4 &b)
	{ return i32x4b(a[0] < b[0], a[1] < b[1], a[2] < b[2], a[3] < b[3]); }

inline const i32x4 Abs(const i32x4 &v)
	{ return i32x4(Abs(v[0]), Abs(v[1]), Abs(v[2]), Abs(v[3])); }
inline int SignMask(const i32x4 &v)
	{ return (v[0] < 0? 1 : 0) | (v[1] < 0? 2 : 0) | (v[2] < 0? 4 : 0) | (v[3] < 0? 8 : 0); }

inline const i32x4 Min(const i32x4 &a,const i32x4 &b)
	{ return i32x4(Min(a[0], b[0]), Min(a[1], b[1]), Min(a[2], b[2]), Min(a[3], b[3])); }
inline const i32x4 Max(const i32x4 &a,const i32x4 &b)
	{ return i32x4(Max(a[0], b[0]), Max(a[1], b[1]), Max(a[2], b[2]), Max(a[3], b[3])); }

inline const i32x4 Condition(const i32x4b t, const i32x4 &a, const i32x4 &b)
	{ return i32x4(t.v[0]? a[0] : b[0], t.v[1]? a[1] : b[1], t.v[2]? a[2] : b[2], t.v[3]? a[3] : b[3]); }

inline const i32x4 Condition(const i32x4b t, const i32x4 &a)
	{ return i32x4(t.v[0]? a[0] : 0, t.v[1]? a[1] : 0, t.v[2]? a[2] : 0, t.v[3]? a[3] : 0); }

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
	{ return i32x4(v[0] + 0.5f, v[1] + 0.5f, v[2] + 0.5f, v[3] + 0.5f); }
inline const i32x4 Trunc(const f32x4 &v)
	{ return i32x4(v[0], v[1], v[2], v[3]); }

inline void Cast(const i32x4 &src, f32x4 &dst) {
   dst = f32x4(	BitCast<float>(src[0]),
				BitCast<float>(src[1]),
				BitCast<float>(src[2]),
				BitCast<float>(src[3]));
}

inline void Cast(const f32x4 &src, i32x4 &dst) {
   dst = i32x4(	BitCast<int>(src[0]),
				BitCast<int>(src[1]),
				BitCast<int>(src[2]),
				BitCast<int>(src[3]));
}

#endif

