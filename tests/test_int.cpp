#include <stdio.h>
#include <math.h>
#include "veclib.h"

using namespace veclib;

class IntSet
{
public:
	IntSet(int s,bool skipZero=0) :size(s),skip0(skipZero) { }

	int Num() const { return size*5; }
	int Generate(int n) const {
		int mul=1,sh=0;

		while(n>size) { mul*=size/2; n-=size; }
		int out=(n&1?-1:1)*(n/2)*mul+sh;
		if(skip0&&out==0) return 1;
		return out;
	}
	void Print() {
		for(int n=0;n<Num();n++)
			printf("%11d\n",Generate(n));
	}

	bool skip0;
	int size;
};

class IntTest
{
private:
	void EvalX4(int v1[4],int v2[4],int a[4],i32x4 (*func)(const i32x4&,const i32x4&)) {
		i32x4 t1,t2,t;
		Convert(v1,t1);
		Convert(v2,t2);
		t=func(t1,t2);
		Convert(t,a);
	}
	void EvalX4(int v[4],int a[4],i32x4 (*func)(const i32x4&)) {
		i32x4 t1,t2;
		Convert(v,t1);
		t2=func(t1);
		Convert(t2,a);
	}

	template <class Generator>
	bool DoTest(const Generator &gen,const char *name,
			i32x4 (*testedFunc)(const i32x4&),int(*correctFunc)(int)) {	

		for(int n=0;n<gen.Num();n++) {
			int v[4],a[4],b[4];
			for(int k=0;k<4;k++) {
				v[k]=gen.Generate(n+k);
				b[k]=correctFunc(v[k]);
			}
			EvalX4(v,a,testedFunc);

			if(a[0]!=b[0]||a[1]!=b[1]||a[2]!=b[2]||a[3]!=b[3]) {
				printf("%s ERROR:\n"
						"func( %11d %11d %11d %11d ) =\n"
						"      %11d %11d %11d %11d should be:\n"
						"      %11d %11d %11d %11d\n",
						name,
						v[0],v[1],v[2],v[3],a[0],a[1],a[2],a[3],b[0],b[1],b[2],b[3]);
				return 0;
			}
		}
		printf("%s; ",name); fflush(stdout);
		return 1;
	}
	template <class Generator>
	bool DoTest(const Generator &gen,const char *name,
			i32x4 (*testedFunc)(const i32x4&,const i32x4&),int(*correctFunc)(int,int)) {	

		for(int x=0;x<gen.Num();x++) for(int y=0;y<gen.Num();y++) {
			int v1[4],v2[4],a[4],b[4];
			for(int k=0;k<4;k++) {
				v1[k]=gen.Generate(x+k);
				v2[k]=gen.Generate(y+k);
				v2[k]=-2;
				b[k]=correctFunc(v1[k],v2[k]);
			}
			EvalX4(v1,v2,a,testedFunc);

			if(a[0]!=b[0]||a[1]!=b[1]||a[2]!=b[2]||a[3]!=b[3]) {
				printf( "%s ERROR:\n"
						"func( %11d %11d %11d %11d ,\n"
						"      %11d %11d %11d %11d ) =\n"
						"      %11d %11d %11d %11d should be:\n"
						"      %11d %11d %11d %11d\n",
						name,
						v1[0],v1[1],v1[2],v1[3],v2[0],v2[1],v2[2],v2[3],
						a[0],a[1],a[2],a[3],b[0],b[1],b[2],b[3]);
				return 0;
			}
		}
		printf("%s; ",name); fflush(stdout);
		return 1;
	}

	static int TAdd(int a,int b) { return a+b; }
	static int TSub(int a,int b) { return a-b; }
	static int TMul(int a,int b) { return a*b; }
	static int TDiv(int a,int b) { return a/b; }
	static int TMod(int a,int b) { return a%b; }
	static int TAnd(int a,int b) { return a&b; }
	static int TOr (int a,int b) { return a|b; }
	static int TXor(int a,int b) { return a^b; }
	static int TShl(int a,int b) { return a<<b; }
	static int TShr(int a,int b) { return a>>b; }
	static int TMax(int a,int b) { return a>b?a:b; }
	static int TMin(int a,int b) { return a<b?a:b; }
	static int TCmpEq(int a,int b) { return a==b?0xffffffff:0; }
	static int TCmpNe(int a,int b) { return a!=b?0xffffffff:0; }
	static int TCmpLe(int a,int b) { return a<=b?0xffffffff:0; }
	static int TCmpGe(int a,int b) { return a>=b?0xffffffff:0; }
	static int TCmpLt(int a,int b) { return a< b?0xffffffff:0; }
	static int TCmpGt(int a,int b) { return a> b?0xffffffff:0; }

	static int TCond1(int a,int b) { return (a<b)||(b<a)?a:b; }
	static int TCond2(int a,int b) { return a>=b&&b>=a?a:b; }
	static int TCond3(int a,int b) { return !(a>b)||!(a<b)?a:b; }
	static int TCond4(int a,int b) { return !(!(a<b)&&!(a>b))?a:b; }
	static int TCond5(int a,int b) { return !(a==b)||(a==b)?a:b; }
	static int TCond6(int a,int b) { bool t=!(a<b); return t?a:b; }

	static int TCond7 (int a,int b) { return (a<=b)^(a>=b)?a:b; }
	static int TCond8 (int a,int b) { return !(a<b)^(a<=b)?a:b; }
	static int TCond9 (int a,int b) { return (a<=b)^!(a<b)?a:b; }
	static int TCond10(int a,int b) { return (!(a<b))^(!(a>b))?a:b; }


	static i32x4 Add(const i32x4 &a,const i32x4 &b) { return a+b; }
	static i32x4 Sub(const i32x4 &a,const i32x4 &b) { return a-b; }
	static i32x4 Mul(const i32x4 &a,const i32x4 &b) { return a*b; }
	static i32x4 Div(const i32x4 &a,const i32x4 &b) { return a/b; }
	static i32x4 Mod(const i32x4 &a,const i32x4 &b) { return a%b; }
	static i32x4 And(const i32x4 &a,const i32x4 &b) { return a&b; }
	static i32x4 Or (const i32x4 &a,const i32x4 &b) { return a|b; }
	static i32x4 Xor(const i32x4 &a,const i32x4 &b) { return a^b; }
	static i32x4 Shl(const i32x4 &a,const i32x4 &b) { return a<<b; }
	static i32x4 Shr(const i32x4 &a,const i32x4 &b) { return a>>b; }
	static i32x4 CmpEq(const i32x4 &a,const i32x4 &b) { return i32x4(a==b); }
	static i32x4 CmpNe(const i32x4 &a,const i32x4 &b) { return i32x4(a!=b); }
	static i32x4 CmpLe(const i32x4 &a,const i32x4 &b) { return i32x4(a<=b); }
	static i32x4 CmpGe(const i32x4 &a,const i32x4 &b) { return i32x4(a>=b); }
	static i32x4 CmpLt(const i32x4 &a,const i32x4 &b) { return i32x4(a< b); }
	static i32x4 CmpGt(const i32x4 &a,const i32x4 &b) { return i32x4(a> b); }

	static i32x4 Cond1(const i32x4 &a,const i32x4 &b) { return Condition((a<b)||(a>b),a,b); }
	static i32x4 Cond2(const i32x4 &a,const i32x4 &b) { return Condition(a>=b&&b>=a,a,b); }
	static i32x4 Cond3(const i32x4 &a,const i32x4 &b) { return Condition(!(a>b)||!(a<b),a,b); }
	static i32x4 Cond4(const i32x4 &a,const i32x4 &b) { return Condition(!(!(a<b)&&!(a>b)),a,b); }
	static i32x4 Cond5(const i32x4 &a,const i32x4 &b) { return Condition(!(a==b)||(a==b),a,b); }
	static i32x4 Cond6(const i32x4 &a,const i32x4 &b) { i32x4b t=!(a<b); return Condition(t,a,b); }

	static i32x4 Cond7 (const i32x4 &a,const i32x4 &b) { return Condition((a<=b)^(a>=b),a,b); }
	static i32x4 Cond8 (const i32x4 &a,const i32x4 &b) { return Condition(!(a<b)^(a<=b),a,b); }
	static i32x4 Cond9 (const i32x4 &a,const i32x4 &b) { return Condition((a<=b)^!(a<b),a,b); }
	static i32x4 Cond10(const i32x4 &a,const i32x4 &b) { return Condition((!(a<b))^(!(a>b)),a,b); }

	static int TNeg(int v) { return -v; }
	static int TNot(int v) { return ~v; }
	static int TAbs(int v) { return v < 0? -v : v; }

	static i32x4 Neg(const i32x4 &v) { return -v; }
	static i32x4 Not(const i32x4 &v) { return ~v; }

public:
	bool Test() {
		bool out=1;

		IntSet set(500),setnz(500,1);

#define TEST(set,func) { out&=DoTest(set,#func,func,T##func); }
		TEST(set,Add)
		TEST(set,Sub)
		TEST(set,Mul)
		TEST(setnz,Div)
		TEST(setnz,Mod)
		TEST(set,And)
		TEST(set,Or)
		TEST(set,Xor)
		TEST(set,Shl)
		TEST(set,Shr)

		TEST(set,Neg)
		TEST(set,Not)
//		TEST(set,Abs)

//		TEST(set,Max)
//		TEST(set,Min)

		TEST(set,CmpEq)
		TEST(set,CmpNe)
		TEST(set,CmpLe)
		TEST(set,CmpGe)
		TEST(set,CmpLt)
		TEST(set,CmpGt)

		TEST(set,Cond1)
		TEST(set,Cond2)
		TEST(set,Cond3)
		TEST(set,Cond4)
		TEST(set,Cond5)
		TEST(set,Cond6)
		TEST(set,Cond7)
		TEST(set,Cond8)
		TEST(set,Cond9)
		TEST(set,Cond10)
#undef TEST

		return out;
	}
};

int main()
{
	bool out=1;
	IntTest test1;

	out&=test1.Test();
	if(out) printf("\nAll OK\n");
	else printf("\n");

	return 0;
}
