#ifndef VECLIB_SCALAR_F32_H
#define VECLIB_SCALAR_F32_H

class f32x4b;

class f32x4 
{
public:
	f32x4() { }
    f32x4(float a,float b,float c,float d) { f[0] = a; f[1] = b; f[2] = c; f[3] = d; }
	f32x4(float v) { f[0] = f[1] = f[2] = f[3] = v; }

	const f32x4 operator+=(const f32x4 &v) {
		f[0] += v[0]; f[1] += v[1]; f[2] += v[2]; f[3] += v[3];
		return *this;
	}
	const f32x4 operator-=(const f32x4 &v) {
		f[0] -= v[0]; f[1] -= v[1]; f[2] -= v[2]; f[3] -= v[3];
		return *this;
	}
	const f32x4 operator*=(const f32x4 &v) {
		f[0] *= v[0]; f[1] *= v[1]; f[2] *= v[2]; f[3] *= v[3];
		return *this;
	}
	const f32x4 operator/=(const f32x4 &v) {
		f[0] /= v[0]; f[1] /= v[1]; f[2] /= v[2]; f[3] /= v[3];
		return *this;
	}

	const f32x4 operator-() const { return f32x4(-f[0], -f[1], -f[2], -f[3]); }
	operator f32*() { return f; }
	operator const f32*() const { return f; }

	float f[4];
};

class f32x4b
{
public:
	f32x4b() { }
	f32x4b(bool a, bool b, bool c, bool d) { v[0] = a; v[1] = b; v[2] = c; v[3] = d; }
	f32x4b(bool a) { v[0] = v[1] = v[2] = v[3] = a; }

	const f32x4b operator^(const f32x4b t) const {
		return MakeV4(v4 ^ t.v4);
	}
	const f32x4b operator&&(const f32x4b t) const {
		return MakeV4(v4 & t.v4);
	}
	const f32x4b operator||(const f32x4b t) const {
		return MakeV4(v4 | t.v4);
	}
	const f32x4b operator!() const {
		return f32x4b(!v[0], !v[1], !v[2], !v[3]);
	}

private:
	static const f32x4b MakeV4(int tv4) {
		f32x4b out;
		out.v4 = tv4;
		return out;
	}
	friend bool ForAny(const f32x4b);
	friend bool ForAll(const f32x4b);
	friend int ForWhich(const f32x4b);
	friend const f32x4 Condition(const f32x4b, const f32x4&, const f32x4&);
	friend const f32x4 Condition(const f32x4b, const f32x4&);
	friend class i32x4b;

	union {
		bool v[4];
		int v4;
	};
};

inline bool ForAny(const f32x4b v)  { return v.v4? 1 : 0; }
inline bool ForAll(const f32x4b v)  { return v.v4 == 0x01010101; }
inline int ForWhich(const f32x4b v) { return v.v[0] | (v.v[1] << 1) | (v.v[2] << 2) | (v.v[3] << 3); }

inline const f32x4b operator==(const f32x4 &a, const f32x4 &b)
	{ return f32x4b(a[0] == b[0], a[1] == b[1], a[2] == b[2], a[3] == b[3]); }
inline const f32x4b operator!=(const f32x4 &a, const f32x4 &b)
	{ return f32x4b(a[0] != b[0], a[1] != b[1], a[2] != b[2], a[3] != b[3]); }
inline const f32x4b operator>=(const f32x4 &a, const f32x4 &b)
	{ return f32x4b(a[0] >= b[0], a[1] >= b[1], a[2] >= b[2], a[3] >= b[3]); }
inline const f32x4b operator<=(const f32x4 &a, const f32x4 &b)
	{ return f32x4b(a[0] <= b[0], a[1] <= b[1], a[2] <= b[2], a[3] <= b[3]); }
inline const f32x4b operator>(const f32x4 &a, const f32x4 &b)
	{ return f32x4b(a[0] > b[0], a[1] > b[1], a[2] > b[2], a[3] > b[3]); }
inline const f32x4b operator<(const f32x4 &a, const f32x4 &b)
	{ return f32x4b(a[0] < b[0], a[1] < b[1], a[2] < b[2], a[3] < b[3]); }

inline const f32x4 operator+(const f32x4 &a, const f32x4 &b)
	{ return f32x4(a[0] + b[0], a[1] + b[1], a[2] + b[2], a[3] + b[3]); }
inline const f32x4 operator-(const f32x4 &a, const f32x4 &b)
	{ return f32x4(a[0] - b[0], a[1] - b[1], a[2] - b[2], a[3] - b[3]); }
inline const f32x4 operator*(const f32x4 &a, const f32x4 &b)
	{ return f32x4(a[0] * b[0], a[1] * b[1], a[2] * b[2], a[3] * b[3]); }
inline const f32x4 operator/(const f32x4 &a, const f32x4 &b)
	{ return f32x4(a[0] / b[0], a[1] / b[1], a[2] / b[2], a[3] / b[3]); }

inline const f32x4 Sqrt(const f32x4 &v)
	{ return f32x4(Sqrt(v[0]), Sqrt(v[1]), Sqrt(v[2]), Sqrt(v[3])); }
inline const f32x4 Inv(const f32x4 &v)
	{ return f32x4(1.0f / (v[0]), 1.0f / (v[1]), 1.0f / (v[2]), 1.0f / (v[3])); }
inline const f32x4 RSqrt(const f32x4 &v)
	{ return f32x4(RSqrt(v[0]), RSqrt(v[1]), RSqrt(v[2]), RSqrt(v[3])); }
inline const f32x4 FastInv(const f32x4 &v)	
	{ return f32x4(FastInv(v[0]), FastInv(v[1]), FastInv(v[2]), FastInv(v[3])); }
inline const f32x4 FastRSqrt(const f32x4 &v)
	{ return f32x4(FastRSqrt(v[0]), FastRSqrt(v[1]), FastRSqrt(v[2]), FastRSqrt(v[3])); }


inline const f32x4 Abs(const f32x4 &v)
	{ return f32x4(Abs(v[0]), Abs(v[1]), Abs(v[2]), Abs(v[3])); }
inline int SignMask(const f32x4 &v)
	{ return (v[0] < 0.0f? 1 : 0) | (v[1] < 0.0f? 2 : 0) | (v[2] < 0.0f? 4 : 0) | (v[3] < 0.0f? 8 : 0); }

inline const f32x4 Min(const f32x4 &a,const f32x4 &b)
	{ return f32x4(Min(a[0], b[0]), Min(a[1], b[1]), Min(a[2], b[2]), Min(a[3], b[3])); }
inline const f32x4 Max(const f32x4 &a,const f32x4 &b)
	{ return f32x4(Max(a[0], b[0]), Max(a[1], b[1]), Max(a[2], b[2]), Max(a[3], b[3])); }

inline const f32x4 Condition(const f32x4b t, const f32x4 &a, const f32x4 &b)
	{ return f32x4(t.v[0]? a[0] : b[0], t.v[1]? a[1] : b[1], t.v[2]? a[2] : b[2], t.v[3]? a[3] : b[3]); }

inline const f32x4 Condition(const f32x4b t, const f32x4 &a)
	{ return f32x4(t.v[0]? a[0] : 0.0f, t.v[1]? a[1] : 0.0f, t.v[2]? a[2] : 0.0f, t.v[3]? a[3] : 0.0f); }

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

