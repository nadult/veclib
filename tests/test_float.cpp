#include <stdio.h>
#include <math.h>
#include "veclib.h"

using namespace veclib;

// Generates float from range ( -size/40 ; size/40 ) with step 0.05f
class LinearFloatSet
{
public:
	LinearFloatSet(int s,float st,float dis,float sb)
		:size(s),step(st),disort(dis),sub(sb) { }

	int Num() const { return size; }
	float Generate(int n) const {
		return float(n)*step+disort-sub;
	}

	int size;
	float step,disort,sub;
};

double Error(double a,double b)
{
	if(b<0) { b=-b; a=-a; }
	double err=(a-b<b-a?a-b:b-a)/(b==0.0?1.0:b);
	return err<0?-err:err;
}

class SimpleFloatFunctionsTest
{
private:
	template <class Generator>
	bool DoTest(const Generator &gen,const char *name,
			float (*testedFunc)(float),double (*correctFunc)(float),double maxError) {	
		printf("\t%s: ",name);
		double error=0;

		for(int n=0;n<gen.Num();n++) {
			float v=gen.Generate(n);
			double a=testedFunc(v),b=correctFunc(v);
			double err=Error(a,b);

			if(err>maxError) {
				printf("ERROR\tf(%f)=%f instead of %f; err=%.20f\n",v,a,b,err);
				return 0;
			}
			if(err>error) error=err;
		}

		printf("OK\tmaxError: %.20f\n",error);
		return 1;
	}

	template <class Generator>
	bool DoTest(const Generator &gen,const char *name,
			float (*testedFunc)(float,float),double (*correctFunc)(float,float),double maxError) {	
		printf("\t%s: ",name);
		double error=0;

		for(int x=0;x<gen.Num();x++) for(int y=0;y<gen.Num();y++) {
			float vx=gen.Generate(x),vy=gen.Generate(y);
			double a=testedFunc(vx,vy),b=correctFunc(vx,vy);
			double err=Error(a,b);

			if(err>maxError) {
				printf("ERROR\tf(%f,%f)=%f instead of %f (error=%f)\n",vx,vy,a,b,err);
				return 0;
			}
			if(err>error) error=err;
		}

		printf("OK\tmaxError: %.20f\n",error);
		return 1;
	}

	static double TSqrt(float v) { return sqrt(v); }
	static double TInv(float v) { return 1.0/v; }
	static double TRSqrt(float v) { return 1.0/sqrt(v); }
	static double TAbs(float v) { return v<0.0?-v:v; }
	static double TMax(float a,float b) { return a>b?a:b; }
	static double TMin(float a,float b) { return a<b?a:b; }

public:
	bool Test() {
		bool out=1;
		printf("Testing simple float functions:\n");

		LinearFloatSet set1(2000,0.00333333333333,0.00012346756,0);
		LinearFloatSet set2(2000,0.00333333333333,0.00012346756,1000);

		double err=0.000001,fastErr=0.001;

		out&=DoTest(set1,"    Sqrt"	,Sqrt		,TSqrt		,err);
		out&=DoTest(set1,"     Inv"	,Inv		,TInv		,err);
		out&=DoTest(set1,"   RSqrt"	,RSqrt		,TRSqrt		,err);
		out&=DoTest(set1," FastInv"	,FastInv	,TInv		,fastErr);
		out&=DoTest(set1,"FastSqrt"	,FastRSqrt	,TRSqrt		,fastErr);
		out&=DoTest(set2,"     Abs"	,Abs		,TAbs		,err);

		out&=DoTest(set1,"     Max"	,Max		,TMax		,err);
		out&=DoTest(set1,"     Min"	,Min		,TMin		,err);

		return out;
	}
};

int main()
{
	bool out=1;
	SimpleFloatFunctionsTest test1;

	out&=test1.Test();

	printf(out?"All OK\n":"Errors Encountered\n");

	/*
	Matrix<Vec4<float> > blah;
	blah=Identity<Vec4<float> >()*RotateX(20)*RotateY(30);
	printf("%f %f %f\n",blah.X().X(),blah.Y().Z(),blah.Z().X());

	SSEPVec3 vec1(1,2,3),vec2(4,5,6);
	printf("%f\n",vec1|vec2); */

	/*
	SSEI32 v1,v2;
	int t[4]={-10,-2,300000,400000},v[4]={-1,1,20000,1000000};
	Convert(t,v1); Convert(v,v2);

	SSEI32 tv;
	tv=v1>=v2; Convert(Condition(tv,v1,v2),t); printf("%d %d %d %d %04x\n",t[0],t[1],t[2],t[3],ForWhich(tv));
	tv=v1<=v2; Convert(Condition(tv,v1,v2),t); printf("%d %d %d %d %04x\n",t[0],t[1],t[2],t[3],ForWhich(tv));
	*/

	return 0;
}
