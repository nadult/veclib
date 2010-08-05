#include <stdio.h>
#include <math.h>
#include "../veclib.h"

using namespace veclib;

struct DataFloat {
	void Print(int indent) const { while(indent-->0) printf(" "); printf("%10.6f",v); }
	float v;
};

class FloatGenerator
{
public:
	typedef DataFloat TData;

	FloatGenerator(float mi,float ma,int seed_,int num_) :min(mi),max(ma),seed(seed_),num(num_) { }

	void Init() const { srand(seed); }
	int Num() const { return num; }
	DataFloat Generate(int n) const {
		float p=float(rand())/float(RAND_MAX)*0.01f+float(rand())/float(RAND_MAX)*0.99f;
		DataFloat out; out.v=Clamp(p*(max-min)+min,min,max);
		return out;
	}

	float min,max;
	int seed,num;
};

struct DataFloat4 {
	void Print(int indent) const { while(indent-->0) printf(" "); printf("%10.6f %10.6f %10.6f %10.6f",v[0],v[1],v[2],v[3]); }
	float v[4];
};
struct DataFloat4x2 {
	void Print(int indent) const { int i=indent;
		while(i-->0) 	  printf(" "); printf("%10.6f %10.6f %10.6f %10.6f\n",v1[0],v1[1],v1[2],v1[3]);
		while(indent-->0) printf(" "); printf("%10.6f %10.6f %10.6f %10.6f"  ,v2[0],v2[1],v2[2],v2[3]);
	}
	float v1[4]; float v2[4];
};

class Float4Generator: public FloatGenerator
{
public:
	typedef DataFloat4 TData;
	Float4Generator(float mi,float ma,int seed_,int num_) :FloatGenerator(mi,ma,seed_,num_) { }
	DataFloat4 Generate(int n) const
		{ DataFloat4 out; for(int i=0;i<4;i++) out.v[i]=FloatGenerator::Generate(n+i).v; return out; }
};
class Float4x2Generator: public FloatGenerator
{
public:
	typedef DataFloat4x2 TData;
	Float4x2Generator(float mi,float ma,int seed_,int num_) :FloatGenerator(mi,ma,seed_,num_) { }
	DataFloat4x2 Generate(int n) const {
		DataFloat4x2 out;
		for(int i=0;i<4;i++) {
			out.v1[i]=FloatGenerator::Generate(n+i).v;
			out.v2[i]=n<1000?out.v1[i]:FloatGenerator::Generate(n+i).v;
		}
		return out;
	}
};


double Error(double a,double b)
{
	if(b<0) { b=-b; a=-a; }
	double err=(a-b<b-a?a-b:b-a)/(b==0.0?1.0:b);
	return err<0?-err:err;
}

template <class Data,class Input,class Output>
void Eval(const Data &in,Data &out,Output (*func)(const Input&)) {
	Input input; Output output;
	Convert(in,input); output=func(input); Convert(output,out);
}
template <class Data,class Input,class Output>
void Eval(const Data &in1,const Data &in2,Data &out,Output (*func)(const Input&,const Input&)) {
	Input input1,input2; Output output;
	Convert(in1,input1); Convert(in2,input2); output=func(input1,input2); Convert(output,out);
}

template <class TestedFunc,class CorrectFunc>
double Compare(DataFloat4 data,TestedFunc tFunc,CorrectFunc cFunc) {
	float out1[4]; double out2[4];
	Eval(data.v,out1,tFunc);
	for(int n=0;n<4;n++) out2[n]=cFunc(data.v[n]);

	double err=Error(out1[0],out2[0]);
	for(int n=1;n<4;n++) { double e=Error(out1[n],out2[n]); err=e<err?e:err; }
	return err;
}

template <class TestedFunc,class CorrectFunc>
double Compare(DataFloat4x2 data,TestedFunc tFunc,CorrectFunc cFunc) {
	float out1[4]; double out2[4];
	Eval(data.v1,data.v2,out1,tFunc);
	for(int n=0;n<4;n++) out2[n]=cFunc(data.v1[n],data.v2[n]);

	double err=Error(out1[0],out2[0]);
	for(int n=1;n<4;n++) { double e=Error(out1[n],out2[n]); err=e<err?e:err; }
	return err;
}


class FloatTest
{
private:
template <class Generator,class TestedFunc,class CorrectFunc>
	bool DoTest(const Generator &gen,const char *name,TestedFunc tFunc,CorrectFunc cFunc,double maxError) {	
		printf("%10s: ",name);
		double error=0;
		typedef typename Generator::TData Data;

		gen.Init();
		for(int n=0;n<gen.Num();n++) {
			Data data=gen.Generate(n);
			double err=Compare(data,tFunc,cFunc);

			if(err>maxError) {
				printf("ERROR:  func (\n");
				data.Print(11);
				printf(" )\n      is too far from correct solution by: %.20f (max=%.20f)\n",err,maxError);
				return 0;
			}
			if(err>error) error=err;
		}

		printf("OK\tmaxError: %.20f\n",error);
		return 1;
	}

	static double CSqrt		(double v) { return sqrt(v); }
	static double CInv		(double v) { return 1.0/v; }
	static double CRSqrt	(double v) { return 1.0/sqrt(v); }
	static double CAbs		(double v) { return v<0.0?-v:v; }
	static double CFastInv	(double v) { return 1.0/v; }
	static double CFastRSqrt(double v) { return 1.0/sqrt(v); }

	static double CMax(double a,double b) { return a>b?a:b; }
	static double CMin(double a,double b) { return a<b?a:b; }

	static double CCmpEq(double a,double b) { return a==b?1.0:-1.0; }
	static double CCmpNe(double a,double b) { return a!=b?1.0:-1.0; }
	static double CCmpLe(double a,double b) { return a<=b?1.0:-1.0; }
	static double CCmpGe(double a,double b) { return a>=b?1.0:-1.0; }
	static double CCmpLt(double a,double b) { return a< b?1.0:-1.0; }
	static double CCmpGt(double a,double b) { return a> b?1.0:-1.0; }

	static double CCond1(double a,double b) { return (a<b)||(b<a)?a:b; }
	static double CCond2(double a,double b) { return a>=b&&b>=a?a:b; }
	static double CCond3(double a,double b) { return !(a>b)||!(a<b)?a:b; }
	static double CCond4(double a,double b) { return !(!(a<b)&&!(a>b))?a:b; }
	static double CCond5(double a,double b) { return !(a==b)||(a==b)?a:b; }
	static double CCond6(double a,double b) { bool t=!(a<b); return t?a:b; }

	static double CCond7 (double a,double b) { return (a<=b)^(a>=b)?a:b; }
	static double CCond8 (double a,double b) { return !(a<b)^(a<=b)?a:b; }
	static double CCond9 (double a,double b) { return (a<=b)^!(a<b)?a:b; }
	static double CCond10(double a,double b) { return (!(a<b))^(!(a>b))?a:b; }


	static f32x4 TSqrt		(const f32x4 &in) { return Sqrt (in); }
	static f32x4 TInv		(const f32x4 &in) { return Inv  (in); }
	static f32x4 TRSqrt		(const f32x4 &in) { return RSqrt(in); }
	static f32x4 TAbs		(const f32x4 &in) { return Abs  (in); }
	static f32x4 TFastInv	(const f32x4 &in) { return FastInv  (in); }
	static f32x4 TFastRSqrt	(const f32x4 &in) { return FastRSqrt(in); }

	static f32x4 TMax  (const f32x4 &a,const f32x4 &b) { return Max  (a,b); }
	static f32x4 TMin  (const f32x4 &a,const f32x4 &b) { return Min  (a,b); }

	static f32x4 TCmpEq(const f32x4 &a,const f32x4 &b) { return Condition(a == b, 1.0f, -1.0f); }
	static f32x4 TCmpNe(const f32x4 &a,const f32x4 &b) { return Condition(a != b, 1.0f, -1.0f); }
	static f32x4 TCmpLe(const f32x4 &a,const f32x4 &b) { return Condition(a <= b, 1.0f, -1.0f); }
	static f32x4 TCmpGe(const f32x4 &a,const f32x4 &b) { return Condition(a >= b, 1.0f, -1.0f); }
	static f32x4 TCmpLt(const f32x4 &a,const f32x4 &b) { return Condition(a <  b, 1.0f, -1.0f); }
	static f32x4 TCmpGt(const f32x4 &a,const f32x4 &b) { return Condition(a >  b, 1.0f, -1.0f); }

	static f32x4 TCond1(const f32x4 &a,const f32x4 &b) { return Condition((a < b) || (a > b), a, b); }
	static f32x4 TCond2(const f32x4 &a,const f32x4 &b) { return Condition(a >= b && b >= a, a, b); }
	static f32x4 TCond3(const f32x4 &a,const f32x4 &b) { return Condition(!(a > b) || !(a < b), a, b); }
	static f32x4 TCond4(const f32x4 &a,const f32x4 &b) { return Condition(!(!(a < b) && !(a > b)), a, b); }
	static f32x4 TCond5(const f32x4 &a,const f32x4 &b) { return Condition(!(a == b) || (a == b), a, b); }
	static f32x4 TCond6(const f32x4 &a,const f32x4 &b) { f32x4b t=!(a<b); return Condition(t, a, b); }

	static f32x4 TCond7 (const f32x4 &a,const f32x4 &b) { return Condition((a<=b)^(a>=b),a,b); }
	static f32x4 TCond8 (const f32x4 &a,const f32x4 &b) { return Condition(!(a<b)^(a<=b),a,b); }
	static f32x4 TCond9 (const f32x4 &a,const f32x4 &b) { return Condition((a<=b)^!(a<b),a,b); }
	static f32x4 TCond10(const f32x4 &a,const f32x4 &b) { return Condition((!(a<b))^(!(a>b)),a,b); }

public:
	bool Test() {
		bool out=1;
		Float4Generator		setp(0.01		,100000.0f	,12345	,10203);
		Float4Generator		seta(-99999.0f	,100000.0f	,12345	,20101);
		Float4x2Generator	setab(-99999.0f	,100000.0f	,12345	,20101);

		double err=0.000001,fastErr=0.001;

#define TEST(set,func,err) { out&=DoTest(set,#func,T##func,C##func,err); }

		TEST(setp,Sqrt		,err);
		TEST(setp,Inv		,err);
		TEST(setp,RSqrt		,err);
		TEST(seta,FastInv	,fastErr);
		TEST(setp,FastRSqrt	,fastErr);
		TEST(seta,Abs		,err);

		TEST(setab,Max		,err);
		TEST(setab,Min		,err);

		TEST(setab,CmpEq	,0.0f);
		TEST(setab,CmpNe	,0.0f);
		TEST(setab,CmpLe	,0.0f);
		TEST(setab,CmpGe	,0.0f);
		TEST(setab,CmpLt	,0.0f);
		TEST(setab,CmpGt	,0.0f);

		TEST(setab,Cond1	,0.0f);
		TEST(setab,Cond2	,0.0f);
		TEST(setab,Cond3	,0.0f);
		TEST(setab,Cond4	,0.0f);
		TEST(setab,Cond5	,0.0f);
		TEST(setab,Cond6	,0.0f);
		TEST(setab,Cond7	,0.0f);
		TEST(setab,Cond8	,0.0f);
		TEST(setab,Cond9	,0.0f);
		TEST(setab,Cond10	,0.0f);

#undef TEST

		return out;
	}
};

int main()
{
	bool out=1;
	FloatTest test1;

	out&=test1.Test();

	printf(out?"All OK\n":"Errors Encountered\n");

	f32x4 a(1.0f, 2.0f, 3.0f, 4.0f), b(1.5f, 1.7, 3.1, 3.9);
	f32x4b t = a < b;
	f32x4 c = Condition(t, a, b);
	f32x4 d = Condition(a > b, a, b);

	for(int k = 0; k < 4;k++)
		printf("%f %f\n", c[k], d[k]);

	return 0;
}

