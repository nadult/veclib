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

	INLINE vbase& X() { return x; }
	INLINE vbase& Y() { return y; }
	INLINE vbase& Z() { return z; }
	INLINE vbase& W() { return w; }
	INLINE const vbase& X() const { return x; }
	INLINE const vbase& Y() const { return y; }
	INLINE const vbase& Z() const { return z; }
	INLINE const vbase& W() const { return w; }

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
INLINE Matrix<vbase> Identity() {
	Matrix<vbase> out;
	typename vbase::TScalar zero=Const<typename vbase::TScalar,0>::Value(),one=Const<typename vbase::TScalar,1>::Value();
	out.x=vbase(one,zero,zero,zero);
	out.y=vbase(zero,one,zero,zero);
	out.z=vbase(zero,zero,one,zero);
	out.w=vbase(zero,zero,zero,one);
	return out;
}

template <class vbase>
INLINE Matrix<vbase> Transpose(const Matrix<vbase> &m) {
	Matrix<vbase> out;
	out.x=vbase(m.x.X(),m.y.X(),m.z.X(),m.w.X());
	out.y=vbase(m.x.Y(),m.y.Y(),m.z.Y(),m.w.Y());
	out.z=vbase(m.x.Z(),m.y.Z(),m.z.Z(),m.w.Z());
	out.w=vbase(m.x.W(),m.y.W(),m.z.W(),m.w.W());
	return out;
}

template <class vbase>
INLINE Vec4<typename vbase::TScalar> operator*(const Matrix<vbase> &m,const Vec4<typename vbase::TScalar> &v) {
	Vec4<base> out;
	out.X() = m.X()|v;
	out.Y() = m.Y()|v;
	out.Z() = m.Z()|v;
	out.W() = m.W()|v;
	return out;
}
template <class vbase>
INLINE Vec3<typename vbase::TScalar> operator*(const Matrix<vbase> &m,const Vec3<typename vbase::TScalar> &v) {
	Vec3<typename vbase::TScalar> out;

	out.X() = m.X().X()*v.X()+m.X().Y()*v.Y()+m.X().Z()*v.Z();
	out.Y() = m.Y().X()*v.X()+m.Y().Y()*v.Y()+m.Y().Z()*v.Z();
	out.Z() = m.Z().X()*v.X()+m.Z().Y()*v.Y()+m.Z().Z()*v.Z();
	//out *= Inv( Sum(m.W()) );

	return out;
}
template <class vbase>
INLINE Vec2<typename vbase::TScalar> operator*(const Matrix<vbase> &m,const Vec2<typename vbase::TScalar> &v) {
	Vec2<typename vbase::TScalar> out;

	out.X() = m.X().X()*v.X()+m.X().Y()*v.Y();
	out.Y() = m.Y().X()*v.X()+m.Y().Y()*v.Y();
	out *= Inv( Sum(m.W()) );

	return out;
}

INLINE Matrix<Vec4<float> > RotateX(float angle) {
	float c=cos(angle),s=sin(angle);
	Matrix<Vec4<float> > out=Identity<Vec4<float> >();
	
	out.y.Y()=c; out.y.Z()=s;
	out.z.Y()=-s; out.z.Z()=c;
	return out;
}

INLINE Matrix<Vec4<float> > RotateY(float angle) {
	float c=cos(angle),s=sin(angle);
	Matrix<Vec4<float> > out=Identity<Vec4<float> >();

	out.x.X()=c; out.x.Z()=s;
	out.z.X()=-s; out.z.Z()=c;
	return out;
}

INLINE Matrix<Vec4<float> > RotateZ(float angle) {
	float c=cos(angle),s=sin(angle);
	Matrix<Vec4<float> > out=Identity<Vec4<float> >();

	out.x.X()=c; out.x.Y()=-s;
	out.y.X()=s; out.y.Y()=c;
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
