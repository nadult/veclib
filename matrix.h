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

// Convertible to any matrix type as identity matrix
template <class T=void>
struct Identity: public Matrix<T> {
	Identity() :Matrix<T>(Identity<void>()) { }

	operator Matrix<T>&() { return *(Matrix<T>*)this; }
	operator const Matrix<T>&() const { return *(Matrix<T>*)this; }
};

template <> struct Identity<void> { };

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
	INLINE Matrix(Identity<void>) {
		TScalar zero=Const<TScalar,0>(),one=Const<TScalar,1>();
		x=vbase(one,zero,zero,zero);
		y=vbase(zero,one,zero,zero);
		z=vbase(zero,zero,one,zero);
		w=vbase(zero,zero,zero,one);
	}

	INLINE const Matrix &operator*=(const Matrix &m) {
		Matrix t=Transpose(m);
		vbase x_=x,y_=y,z_=z;
		x=x_|t.x,x_|t.y,x_|t.z,x_|t.w;
		y=y_|t.x,y_|t.y,y_|t.z,y_|t.w;
		z=z_|t.x,z_|t.y,z_|t.z,z_|t.w;
		w=w|t.x,w|t.y,w|t.z,w|t.w;
		return *this;
	}
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
INLINE Vec4<typename vbase::TScalar> operator*(const Matrix<vbase> &m,const Vec4<typename vbase::TScalar> &v) {
	Vec4<vbase> out;
	out.x = m.x|v;
	out.y = m.y|v;
	out.z = m.z|v;
	out.w = m.w|v;
	return out;
}
template <class vbase>
INLINE Vec3<typename vbase::TScalar> operator*(const Matrix<vbase> &m,const Vec3<typename vbase::TScalar> &v) {
	Vec3<typename vbase::TScalar> out;

	out.x = m.x.x*v.x+m.x.y*v.y+m.x.z*v.z;
	out.y = m.y.x*v.x+m.y.y*v.y+m.y.z*v.z;
	out.z = m.z.x*v.x+m.z.y*v.y+m.z.z*v.z;
	//out *= Inv( Sum(m.w) );

	return out;
}
template <class vbase>
INLINE Vec2<typename vbase::TScalar> operator*(const Matrix<vbase> &m,const Vec2<typename vbase::TScalar> &v) {
	Vec2<typename vbase::TScalar> out;

	out.x = m.x.x*v.x+m.x.y*v.y;
	out.y = m.y.x*v.x+m.y.y*v.y;
	out *= Inv( Sum(m.w) );

	return out;
}

INLINE Matrix<Vec4<float> > RotateX(float angle) {
	float c=cos(angle),s=sin(angle);
	Matrix<Vec4<float> > out=Identity<Vec4<float> >();
	
	out.y.y=c; out.y.z=s;
	out.z.y=-s; out.z.z=c;
	return out;
}

INLINE Matrix<Vec4<float> > RotateY(float angle) {
	float c=cos(angle),s=sin(angle);
	Matrix<Vec4<float> > out=Identity<Vec4<float> >();

	out.x.x=c; out.x.z=s;
	out.z.x=-s; out.z.z=c;
	return out;
}

INLINE Matrix<Vec4<float> > RotateZ(float angle) {
	float c=cos(angle),s=sin(angle);
	Matrix<Vec4<float> > out=Identity<Vec4<float> >();

	out.x.x=c; out.x.y=-s;
	out.y.x=s; out.y.y=c;
	return out;
}

INLINE Matrix<Vec4<float> > Rotate(float yaw,float pitch,float roll) {
	return RotateZ(roll)*RotateX(pitch)*RotateY(pitch);
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
