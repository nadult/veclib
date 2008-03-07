
#include <boost/test/unit_test.hpp>
#include <boost/test/results_reporter.hpp>
#include <boost/test/output_test_stream.hpp>
#include <boost/test/unit_test_log.hpp>
#include <boost/test/unit_test_suite.hpp>
#include <boost/test/framework.hpp>
#include <boost/test/detail/unit_test_parameters.hpp>
#include <boost/test/unit_test.hpp>
using namespace boost::unit_test;

#include "test_ivec.cpp"

test_suite* init_unit_test_suite(int argc,char** argv)
{
	framework::master_test_suite().p_name.value="Veclib test suite";
	framework::master_test_suite().add(new SSEIntTestSuite());
	return 0;
}

