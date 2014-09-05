#include <boost_python_exception/extract_exception_type.hpp>

#include <boost/test/unit_test.hpp>

#include <sstream>

#include <boost_python_exception/get_exception_info.hpp>

#include "helpers/execute_python_code.hpp"
#include "helpers/fixtures/clear_python_errors.hpp"

namespace bp = boost::python;
namespace bpe = boost_python_exception;


BOOST_FIXTURE_TEST_SUITE(extract_exception_type, test::fixtures::clear_python_errors)

BOOST_AUTO_TEST_CASE(exception_returns_type_name)
{
    std::string const python_code("raise ValueError()");
    test::execute_python_code_in_main_module(python_code, true);

    std::string const expected = "exceptions.ValueError";
    std::string const actual = bpe::extract_exception_type(bpe::get_exception_info().type);

    BOOST_CHECK_EQUAL(expected, actual);
}

BOOST_AUTO_TEST_CASE(integer_as_type_throws)
{
	boost::python::object not_an_exception_type(42);

	BOOST_CHECK_THROW(bpe::extract_exception_type(not_an_exception_type), std::logic_error);
}

BOOST_AUTO_TEST_CASE(none_as_type_throws)
{
	boost::python::object none;

	BOOST_CHECK_THROW(bpe::extract_exception_type(none), std::logic_error);
}

BOOST_AUTO_TEST_SUITE_END()
