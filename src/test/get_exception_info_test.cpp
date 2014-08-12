#include <boost/test/unit_test.hpp>

#include <boost/python/import.hpp>

#include <boost_python_exception/get_exception_info.hpp>

#include "clear_python_errors.hpp"

namespace bp=boost::python;
namespace bpe=boost_python_exception;

BOOST_FIXTURE_TEST_SUITE(get_exception_info,
                         bpe::test::clear_python_errors)

BOOST_AUTO_TEST_CASE(no_extant_exception)
{
    bpe::exception_info ex_info = bpe::get_exception_info();
    for (int i = 0; i < 3; ++i)
        BOOST_CHECK(ex_info.type == bp::object());
}

BOOST_AUTO_TEST_CASE(import_error)
{
    try {
        bp::import("no_such_module_exists_i_hope");
        BOOST_REQUIRE(false);
    }
    catch (const bp::error_already_set&) {
        bpe::exception_info ex_info = bpe::get_exception_info();
        bp::object ex_type = ex_info.type;
        BOOST_CHECK(
            PyErr_GivenExceptionMatches(
                PyExc_ImportError,
                ex_type.ptr()));
    }

}

BOOST_AUTO_TEST_CASE(index_error)
{
    try {
        bp::list l;
        bp::object item = l[1234];
        BOOST_REQUIRE(false);
    }
    catch (const bp::error_already_set&) {
        bpe::exception_info ex_info = bpe::get_exception_info();
        bp::object ex_type = ex_info.type;
        BOOST_CHECK(
            PyErr_GivenExceptionMatches(
                PyExc_IndexError,
                ex_type.ptr()));
    }

}

BOOST_AUTO_TEST_SUITE_END()
