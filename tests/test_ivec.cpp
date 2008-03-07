#include <boost/test/unit_test.hpp>
using boost::unit_test_framework::test_suite;
using boost::unit_test_framework::test_case;


class SSEIntTest
{
public:
	SSEIntTest() {
	}

	void TestConversions() {
/*		int u[4]={123,456,789,345};
		SSEInt vec; Convert(u,vec);

		int v[4];
		Convert(vec,v);

		BOOST_REQUIRE(v[0]==u[0]&&v[1]==u[1]&&v[2]==u[2]&&v[3]==u[3]);*/
	}

	void TestOperators() {

	}

	void TestFunctions() {

	}

	void ComplexTest() {
/*		int u[4]={1,2,3,4};
		SSEInt vec; Convert(u,vec);

		SSEInt vec2=vec*vec+vec*vec*vec;
		int v[4]; Convert(vec2,v);

		for(int n=0;n<4;n++) u[n]=u[n]*u[n]+u[n]*u[n]*u[n];
		BOOST_REQUIRE(v[0]==u[0]&&v[1]==u[1]&&v[2]==u[2]&&v[3]==u[3]);*/
	}
};


class SSEIntTestSuite: public test_suite
{
public:
	SSEIntTestSuite(): test_suite("SSEIntTestSuite") {
		boost::shared_ptr<SSEIntTest> inst(new SSEIntTest());

		add(	BOOST_CLASS_TEST_CASE(&SSEIntTest::TestConversions,inst)	);
		add(	BOOST_CLASS_TEST_CASE(&SSEIntTest::TestOperators,inst)		);
		add(	BOOST_CLASS_TEST_CASE(&SSEIntTest::TestFunctions,inst)		);
		add(	BOOST_CLASS_TEST_CASE(&SSEIntTest::ComplexTest,inst)		);
	}
};

