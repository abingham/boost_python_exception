#include <boost_python_exception/exception.hpp>

#include <boost/python/list.hpp>
#include <boost/test/unit_test.hpp>

#include <boost_python_exception/standard_exception_translator.hpp>
#include <boost_python_exception/get_exception_info.hpp>
#include <test/helpers/fixtures/clear_python_errors.hpp>
#include <test/helpers/execute_python_code.hpp>

namespace bpe=boost_python_exception;;
namespace bp=boost::python;


BOOST_FIXTURE_TEST_SUITE( exception, test::fixtures::clear_python_errors )

BOOST_AUTO_TEST_CASE( empty_message )
{
	std::string const type("ExceptionType");
	std::string const empty_message;
	bpe::traceback empty_traceback;

	bpe::exception error(type, empty_message, empty_traceback);
	BOOST_CHECK_EQUAL(type, error.what());
}

BOOST_AUTO_TEST_CASE( empty_traceback )
{
	std::string const type("ExceptionType");
	std::string const message("Error message");
	bpe::traceback empty_traceback;

	bpe::exception error(type, message, empty_traceback);
	std::string const expected("ExceptionType: Error message");
	BOOST_CHECK_EQUAL(expected, error.what());
}

BOOST_AUTO_TEST_CASE( all_fields_contain_data )
{
	std::string const type("ExceptionType");
	std::string const message("Error message");
	bpe::traceback traceback;
	bpe::traceback_step const step = {7, "test.py", "test()"};
	traceback.push_back(step);

	bpe::exception error(type, message, traceback);
	std::string const expected(
			"Python traceback (most recent calls last):\n"
			"File \"test.py\", line 7, in test()\n"
			"ExceptionType: Error message"
		);
	BOOST_CHECK_EQUAL(expected, error.what());
}


BOOST_AUTO_TEST_SUITE_END()
