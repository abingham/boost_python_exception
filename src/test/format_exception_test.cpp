#include <boost/test/unit_test.hpp>

#include <boost/python/list.hpp>

#include <boost_python_exception/format_exception.hpp>

namespace bp=boost::python;
namespace bpe=boost_python_exception;

BOOST_AUTO_TEST_SUITE(format_exception)

BOOST_AUTO_TEST_SUITE(no_args)

BOOST_AUTO_TEST_CASE(no_active_exception_is_all_nones)
{
    PyErr_Clear();
    std::string formatted = bpe::format_exception();
    BOOST_CHECK(formatted == "(None, None, None)");
}

BOOST_AUTO_TEST_CASE(an_active_exception_has_information)
{
    try {
        bp::object obj = bp::list()[1234];
        BOOST_REQUIRE(false);
    }
    catch (const bp::error_already_set&) {
        std::string formatted = bpe::format_exception();
        BOOST_CHECK(formatted != "(None, None, None)");
    }
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(explicit_exception)

BOOST_AUTO_TEST_CASE(all_nones)
{
    std::string formatted = bpe::format_exception(
        bp::make_tuple(bp::object(),
                       bp::object(),
                       bp::object()));
    BOOST_CHECK(formatted == "(None, None, None)");
}

BOOST_AUTO_TEST_CASE(not_all_nones)
{
    std::string formatted = bpe::format_exception(
        bp::make_tuple(1, 2, 3));
    BOOST_CHECK(formatted == "(1, 2, 3)");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
