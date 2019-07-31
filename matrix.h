#ifndef VECLIB_MATRIX_H
#define VECLIB_MATRIX_H

#include "vec4.h"


/*
	Translation matrix:

	x = 1 0 0 x
	y = 0 1 0 y
	z = 0 0 1 z
	w = 0 0 0 1
*/

template <class vbase> class Matrix;

struct Identity { };
static constexpr Identity identity;

template <class vbase>
class Matrix
{
public:
	typedef typename vbase::TScalar TScalar;
	typedef vbase TVector;

	INLINE Matrix() {
	}
	INLINE Matrix(const vbase &a,const vbase &b,const vbase &c,const vbase &d) :x(a),y(b),z(c),w(d) {
	}
	INLINE Matrix(Identity) {
		TScalar zero(0.0f), one(1.0f);
		x=vbase(one,zero,zero,zero);
		y=vbase(zero,one,zero,zero);
		z=vbase(zero,zero,one,zero);
		w=vbase(zero,zero,zero,one);
	}
	template <class tbase>
	INLINE Matrix(const Matrix<tbase> &other) :x(other.x),y(other.y),z(other.z),w(other.w) { }

	INLINE const Matrix &operator*=(const Matrix&);
	INLINE const Matrix &operator+=(const Matrix &m) {
		x+=m.x;
		y+=m.y;
		z+=m.z;
		w+=m.w;
		return *this;
	}
	INLINE const Matrix &operator-=(const Matrix &m) {
		x-=m.x;
		y-=m.y;
		z-=m.z;
		w-=m.w;
		return *this;
	}
	INLINE Matrix operator-() const {
		Matrix out;
		out.x=-x;
		out.y=-y;
		out.z=-z;
		out.w=-w;
		return out;
	}
	
	vbase x,y,z,w;
};

template <class vbase>
INLINE Matrix<vbase> operator*(const Matrix<vbase> &a,const Matrix<vbase> &b) {
	Matrix<vbase> out;
	out=a;
	out*=b;
	return out;
}


template <class vbase>
INLINE Matrix<vbase> Transpose(const Matrix<vbase> &m) {
	Matrix<vbase> out;
	out.x=vbase(m.x.x,m.y.x,m.z.x,m.w.x);
	out.y=vbase(m.x.y,m.y.y,m.z.y,m.w.y);
	out.z=vbase(m.x.z,m.y.z,m.z.z,m.w.z);
	out.w=vbase(m.x.w,m.y.w,m.z.w,m.w.w);
	return out;
}

template <class vbase>
INLINE const Matrix<vbase> &Matrix<vbase>::operator*=(const Matrix<vbase> &m) {
	Matrix<vbase> t=Transpose(m);
	vbase x_=x,y_=y,z_=z;
	x=vbase(x_|t.x,x_|t.y,x_|t.z,x_|t.w);
	y=vbase(y_|t.x,y_|t.y,y_|t.z,y_|t.w);
	z=vbase(z_|t.x,z_|t.y,z_|t.z,z_|t.w);
	w=vbase(w |t.x,w |t.y,w |t.z,w |t.w);
	return *this;
}

template <class mbase,class vbase>
INLINE Vec4<vbase> operator*(const Matrix<mbase> &m,Vec4<vbase> v) {
	Vec4<vbase> out;
	out.x = v|m.x;
	out.y = v|m.y;
	out.z = v|m.z;
	out.w = v|m.w;
	return out;
}

template <class mbase,class vbase>
INLINE Vec3<vbase> operator*(const Matrix<mbase> &m,Vec3<vbase> v) __attribute__((always_inline));
template <class mbase,class vbase>
INLINE Vec3<vbase> operator*(const Matrix<mbase> &m,Vec3<vbase> v) {
	Vec3<vbase> out;

	out.x = v.x*m.x.x+v.y*m.y.x+v.z*m.z.x+m.w.x;
	out.y = v.x*m.x.y+v.y*m.y.y+v.z*m.z.y+m.w.y;
	out.z = v.x*m.x.z+v.y*m.y.z+v.z*m.z.z+m.w.z;

	return out;
}

template <class mbase,class vbase>
INLINE Vec3<vbase> operator&(const Matrix<mbase> &m,Vec3<vbase> v) {
	Vec3<vbase> out;

	out.x = v.x*m.x.x+v.y*m.y.x+v.z*m.z.x;
	out.y = v.x*m.x.y+v.y*m.y.y+v.z*m.z.y;
	out.z = v.x*m.x.z+v.y*m.y.z+v.z*m.z.z;

	return out;
}

template <class mbase,class vbase>
INLINE Vec2<vbase> operator*(const Matrix<mbase> &m,Vec2<vbase> v) {
	Vec2<vbase> out;

	out.x = v.x*m.x.x+v.y*m.x.y+m.w.x;
	out.y = v.x*m.y.x+v.y*m.y.y+m.w.y;

	return out;
}

INLINE Matrix<Vec4<float> > RotateX(float angle) {
	float c=cos(angle),s=sin(angle);
	Matrix<Vec4<float> > out=identity;
	
	out.y.y=c; out.y.z=s;
	out.z.y=-s; out.z.z=c;
	return out;
}

INLINE Matrix<Vec4<float> > RotateY(float angle) {
	float c=cos(angle),s=sin(angle);
	Matrix<Vec4<float> > out=identity;

	out.x.x=c; out.x.z=s;
	out.z.x=-s; out.z.z=c;
	return out;
}

INLINE Matrix<Vec4<float> > RotateZ(float angle) {
	float c=cos(angle),s=sin(angle);
	Matrix<Vec4<float> > out=identity;

	out.x.x=c; out.x.y=-s;
	out.y.x=s; out.y.y=c;
	return out;
}

INLINE Matrix<Vec4<float> > Rotate(float yaw, float pitch, float roll) {
	return RotateZ(roll) * RotateX(pitch) * RotateY(yaw); //TODO: testme
}

INLINE Matrix<Vec4<float> > Translate(const Vec3<float> &vec) {
	Matrix<Vec4<float> > out = identity;
	out.w.x = vec.x;
	out.w.y = vec.y;
	out.w.z = vec.z;
	return out;
}

/*
INLINE void Transpose(const SSEReal &x,const SSEReal &y,const SSEReal &z,const SSEReal &w,
			   SSEReal &ox,SSEReal &oy,SSEReal &oz,SSEReal &ow)
{
	__m128 tmp3, tmp2, tmp1, tmp0;
	tmp0=_mm_shuffle_ps(x.m, y.m, 0x44);
	tmp2=_mm_shuffle_ps(x.m, y.m, 0xEE);
	tmp1=_mm_shuffle_ps(z.m, w.m, 0x44);
	tmp3=_mm_shuffle_ps(z.m, w.m, 0xEE);

	ox.m=_mm_shuffle_ps(tmp0, tmp1, 0x88);
	oy.m=_mm_shuffle_ps(tmp0, tmp1, 0xDD);
	oz.m=_mm_shuffle_ps(tmp2, tmp3, 0x88);
	ow.m=_mm_shuffle_ps(tmp2, tmp3, 0xDD);
}

void Transpose(SSEReal &x,SSEReal &y,SSEReal &z,SSEReal &w)
{
	Transpose(x,y,z,w,x,y,z,w);
} */


#endif
