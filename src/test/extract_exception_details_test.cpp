#include <boost_python_exception/extract_exception_details.hpp>

#include <boost/test/unit_test.hpp>

#include <sstream>

#include <boost_python_exception/get_exception_info.hpp>

#include "helpers/execute_python_code.hpp"
#include "helpers/fixtures/clear_python_errors.hpp"

namespace bp = boost::python;
namespace bpe = boost_python_exception;

namespace {

void verify_traceback(std::string const & expected_traceback, bp::object py_traceback)
{
    bpe::traceback tb = bpe::extract_traceback(py_traceback);

    std::ostringstream actual;
    for (bpe::traceback::const_iterator it = tb.begin(); it != tb.end(); ++it) {
        actual << *it << "\n";
    }

    BOOST_CHECK_EQUAL(expected_traceback, actual.str());
}

void test_traceback(std::string const & python_code, std::string const & expected_traceback)
{
    test::execute_python_code_in_main_module(python_code, true);
    bpe::exception_info const info = bpe::get_exception_info();
    verify_traceback(expected_traceback, info.traceback);
}

}

BOOST_FIXTURE_TEST_SUITE(extract_traceback, test::fixtures::clear_python_errors)

BOOST_AUTO_TEST_CASE(no_error)
{
    std::string const python_code("1 + 2");
    std::string const expected_traceback("");

    test_traceback(python_code, expected_traceback);
}

BOOST_AUTO_TEST_CASE(single_line_with_error)
{
    std::string const python_code("1 + \"2\"");
    std::string const expected_traceback("File \"<string>\", line 1, in <module>\n");

    test_traceback(python_code, expected_traceback);
}

BOOST_AUTO_TEST_CASE(function_call_with_error)
{
    std::string const python_code(
        "def main():\n"
        "\t 1 + \"2\"\n"
        "if __name__ == \"__main__\":\n"
        "\t main()\n"
        );

    std::string const expected_traceback(
        "File \"<string>\", line 4, in <module>\n"
        "File \"<string>\", line 2, in main\n"
        );

    test_traceback(python_code, expected_traceback);
}

BOOST_AUTO_TEST_SUITE_END()



BOOST_FIXTURE_TEST_SUITE(extract_exception_type, test::fixtures::clear_python_errors)

BOOST_AUTO_TEST_CASE(exception_returns_type_name)
{
    std::string const python_code("raise ValueError()");
    test::execute_python_code_in_main_module(python_code, true);

    std::ostringstream expected;
#if PY_MAJOR_VERSION == 2
    expected << "exceptions.";
#endif
    expected << "ValueError";
    BOOST_CHECK_EQUAL(expected.str(),
                      bpe::extract_exception_type(bpe::get_exception_info().type));
}

BOOST_AUTO_TEST_CASE(integer_as_type_throws)
{
 boost::python::object const not_an_exception_type(42);
 BOOST_CHECK_THROW(bpe::extract_exception_type(not_an_exception_type), std::logic_error);
}

BOOST_AUTO_TEST_CASE(none_as_type_throws)
{
 boost::python::object const none;
 BOOST_CHECK_THROW(bpe::extract_exception_type(none), std::logic_error);
}

BOOST_AUTO_TEST_SUITE_END()




BOOST_FIXTURE_TEST_SUITE(extract_message, test::fixtures::clear_python_errors)

BOOST_AUTO_TEST_CASE(exception_returns_message)
{
    std::string const expected = "message";
    std::string const python_code("raise ValueError('" + expected + "')");
    test::execute_python_code_in_main_module(python_code, true);

    BOOST_CHECK_EQUAL(expected, bpe::extract_message(bpe::get_exception_info().value));
}

BOOST_AUTO_TEST_CASE(none_returns_string_representation)
{
 boost::python::object const none;

 std::string const expected = "None";
 BOOST_CHECK_EQUAL(expected, bpe::extract_message(none));
}

BOOST_AUTO_TEST_SUITE_END()
