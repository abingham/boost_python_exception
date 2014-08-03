#define BOOST_TEST_MODULE boost_python_exception

#include <boost/test/unit_test.hpp>

#include <boost/python/import.hpp>
#include <boost/python/list.hpp>

#include <boost_python_exception/format_exception.hpp>
#include <boost_python_exception/get_exception_info.hpp>

namespace bp=boost::python;
namespace bpe=boost_python_exception;

struct GlobalFixture {
    GlobalFixture()   { Py_Initialize(); }
    ~GlobalFixture()  { /* Py_Finalize(); */ }
};

BOOST_GLOBAL_FIXTURE(GlobalFixture);

BOOST_AUTO_TEST_SUITE(get_exception_info)

BOOST_AUTO_TEST_CASE(no_extant_exception)
{
    bp::tuple ex_info = bpe::getExceptionInfo();
    for (int i = 0; i < 3; ++i)
        BOOST_CHECK(ex_info[i] == bp::object());
}

BOOST_AUTO_TEST_CASE(import_error)
{
    try {
        bp::import("no_such_module_exists_i_hope");
        BOOST_REQUIRE(false);
    }
    catch (const bp::error_already_set&) {
        bp::tuple ex_info = bpe::getExceptionInfo();
        bp::object ex_type = ex_info[0];
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
        bp::tuple ex_info = bpe::getExceptionInfo();
        bp::object ex_type = ex_info[0];
        BOOST_CHECK(
            PyErr_GivenExceptionMatches(
                PyExc_IndexError,
                ex_type.ptr()));
    }

}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(format_exception)

BOOST_AUTO_TEST_SUITE(no_args)

BOOST_AUTO_TEST_CASE(no_active_exception_is_all_nones)
{
    PyErr_Clear();
    std::string formatted = bpe::formatException();
    BOOST_CHECK(formatted == "(None, None, None)");
}

BOOST_AUTO_TEST_CASE(an_active_exception_has_information)
{
    try {
        bp::object obj = bp::list()[1234];
        BOOST_REQUIRE(false);
    }
    catch (const bp::error_already_set&) {
        std::string formatted = bpe::formatException();
        BOOST_CHECK(formatted != "(None, None, None)");
    }
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(explicit_exception)

BOOST_AUTO_TEST_CASE(all_nones)
{
    std::string formatted = bpe::formatException(
        bp::make_tuple(bp::object(),
                       bp::object(),
                       bp::object()));
    BOOST_CHECK(formatted == "(None, None, None)");
}

BOOST_AUTO_TEST_CASE(not_all_nones)
{
    std::string formatted = bpe::formatException(
        bp::make_tuple(1, 2, 3));
    BOOST_CHECK(formatted == "(1, 2, 3)");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
