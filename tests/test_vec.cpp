#include <stdio.h>
#include "veclib.h"

using namespace veclib;


template <class base,class vec3a,class vec3b,class vec3c>
INLINE base IntersectRaySphere(const vec3a &rOrigin,const vec3b &rDir,const vec3c &sPos,const base &sRad)
{
	Vec3<base> dst=rOrigin-sPos;
	base b=dst|rDir,c=(dst|dst)-(sRad*sRad),d=b*b-c;

	return Condition( d > base(0.0f) , -b-Sqrt(d) , base(-1.0f) );
}

/*

const FVec4 XMHalf(0.5f),XMOne(1.0f),XMTwo(2.0f),XMThree(3.0f),XMFour(4.0f);
const FVec4 XMPi(PI),XMPi2(PI2),XMInvPi(INVPI),XMInvPi2(INVPI2);
const FVec4 XMSqrt2(1.4142135624f),XMSqrt3(1.7320508076f);
const FVec4 XMMaskMinus(VecMask(0x80000000,0x80000000,0x80000000,0x80000000));
const FVec4 XMMaskNotMinus(VecMask(0x7fffffff,0x7fffffff,0x7fffffff,0x7fffffff));
const FVec4 XMMaskX(VecMask(-1,0,0,0)),XMMaskY(VecMask(0,-1,0,0));
const FVec4 XMMaskZ(VecMask(0,0,-1,0)),XMMaskW(VecMask(0,0,0,-1));

static const FVec4 XMSin_coeff3579 (-0.166666515f,+0.008332964f,-0.000198048f,+0.000002598f);
static const FVec4 XMSin_cmpVec(0.25f);

template <class Vec>
FVec4 Sin(const Vec &x)
{
	Vec v=x;
	{
		v*=XMInvPi2;
		v-=Round(v);

		FVec4 mask2=CmpL(v,-XMSin_cmpVec);
		FVec4 mask1=Or(CmpG(v,XMSin_cmpVec),mask2);

		v=Xor(v,And(XMMaskMinus,mask1));
		v+=Or(And(mask1,XMHalf),And(XMMaskMinus,mask2));
		v*=XMPi2;
	}

	FVec4 v2=v*v,v3=v2*v,v5=v3*v2,v7=v5*v2,v9=v7*v2;
	return 	v3*XMSin_coeff3579.x+v5*XMSin_coeff3579.y+v7*XMSin_coeff3579.z+v9*XMSin_coeff3579.w+v;
}

*/

bool TestVec()
{
	printf("TestVec ------------------\n");

	typedef Vec3<float> Vec3f;
	typedef	SSEVec3 Vec3q;
	typedef SSEReal realq;

	Vec3f	rayOrig[4]={Vec3f(0,0,1),Vec3f(0,0,1),Vec3f(0,0,1),Vec3f(0,0,1)}
			,rayDir[4] ={Vec3f(0,0,1),Vec3f(0,1,0),Vec3f(1,0,0),Vec3f(0,0,1)};

	Vec3f	spherePos[16]={
			Vec3f(0,0.5f,0),Vec3f(1,0.5f,0),Vec3f(0,0.5f,1),Vec3f(0,0.5f,2),
			Vec3f(0,0.5f,0),Vec3f(1,0.5f,0),Vec3f(0,0.5f,1),Vec3f(0,0.5f,2),
			Vec3f(0,0.5f,0),Vec3f(1,0.5f,0),Vec3f(0,0.5f,1),Vec3f(0,0.5f,2),
			Vec3f(0,0.5f,0),Vec3f(1,0.5f,0),Vec3f(0,0.5f,1),Vec3f(0,0.5f,2),
	};
	float sphereRad[16]={4.0f,5.0f,6.0f,7.0f,1,2,3,4,5,6,7,5,3,2,1,4};
	float out[4];
	
	Vec3f temp(1,2,3);

	Vec3q a,b;
	Convert(rayOrig,a); Convert(rayDir,b);

	realq val1(0,0,0,0);

	for(int n=0;n<4;n++) {
		Vec3q sp; realq sr;
		Convert(spherePos+n*4,sp); Convert(sphereRad+n*4,sr);
		val1+=IntersectRaySphere(a,b,sp,sr);
	}

	Convert(val1,out);
	printf("%f %f %f %f\n",out[0],out[1],out[2],out[3]);

	for(int n=0;n<4;n++) {
		Vec3q sp; realq sr;
		Convert(spherePos+n*4,sp); Convert(sphereRad+n*4,sr);
		val1=IntersectRaySphere(a,b,sp,sr);
		Convert(val1,out);
		printf("%f %f %f %f\n",out[0],out[1],out[2],out[3]);
	}

//	SSEReal val2=IntersectRaySphere(Distribute(rayOrig[0]),Distribute(rayDir[0]),Pack(spherePos),Pack(sphereRad));
//	Unpack(val2,out);
//	printf("%f %f %f %f\n",out[0],out[1],out[2],out[3]);

//	SSEReal val3=IntersectRaySphere(Pack(rayOrig),Pack(rayDir),Pack(spherePos),Pack(sphereRad));
//	Unpack(val3,out);
//	printf("%f %f %f %f\n",out[0],out[1],out[2],out[3]);

	return 1;
}

