#include <boost/test/unit_test.hpp>

#include <boost/python/list.hpp>

#include <boost_python_exception/exception_info.hpp>
#include <boost_python_exception/format_exception.hpp>

#include "helpers/fixtures/clear_python_errors.hpp"

namespace bp=boost::python;
namespace bpe=boost_python_exception;

BOOST_AUTO_TEST_SUITE(format_exception)

BOOST_AUTO_TEST_SUITE(no_args)

BOOST_FIXTURE_TEST_CASE(no_active_exception_is_all_nones,
                        test::fixtures::clear_python_errors)
{
    PyErr_Clear();
    std::string const formatted = bpe::format_exception();
    BOOST_CHECK_EQUAL(formatted, "(None, None, None)");
}

BOOST_AUTO_TEST_CASE(an_active_exception_has_information)
{
    try {
        bp::object const obj = bp::list()[1234];
        BOOST_REQUIRE(false);
    }
    catch (const bp::error_already_set&) {
        std::string const formatted = bpe::format_exception();
        BOOST_CHECK(formatted != "(None, None, None)");
    }
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(explicit_exception)

BOOST_AUTO_TEST_CASE(all_nones)
{
    std::string const formatted = bpe::format_exception(
        bpe::exception_info(bp::object(),
                            bp::object(),
                            bp::object()));
    BOOST_CHECK_EQUAL(formatted, "(None, None, None)");
}

BOOST_AUTO_TEST_CASE(not_all_nones)
{
    std::string const formatted = bpe::format_exception(
        bpe::exception_info(bp::object(1),
                            bp::object(2),
                            bp::object(3)));
    BOOST_CHECK_EQUAL(formatted, "(1, 2, 3)");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
