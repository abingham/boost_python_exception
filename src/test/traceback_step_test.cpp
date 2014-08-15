#include <boost_python_exception/traceback_step.hpp>

#include <boost/test/unit_test.hpp>

#include <sstream>


BOOST_AUTO_TEST_SUITE(traceback_step)

BOOST_AUTO_TEST_CASE(output_to_stream)
{
	boost_python_exception::traceback_step const info = {7, "test.py", "test()"};

	std::ostringstream actual;
	actual << info;
	std::string const expected("File \"test.py\", line 7, in test()");
	BOOST_CHECK_EQUAL(expected, actual.str());
}

BOOST_AUTO_TEST_SUITE_END()

