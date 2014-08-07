#include <boost_python_exception/exception_info.hpp>

#include <boost/test/unit_test.hpp>

#include <boost/python/long.hpp>

namespace bp=boost::python;
namespace bpe=boost_python_exception;

BOOST_AUTO_TEST_SUITE(exception_info)

BOOST_AUTO_TEST_CASE(construction)
{
	bp::long_ const expected_type(1);
	bp::long_ const expected_value(2);
	bp::long_ const expected_traceback(3);

	bpe::exception_info const info(expected_type, expected_value, expected_traceback);

	BOOST_CHECK(expected_type == info.type);
	BOOST_CHECK(expected_value == info.value);
	BOOST_CHECK(expected_traceback == info.traceback);
}

BOOST_AUTO_TEST_SUITE_END()
