#include <boost_python_exception/python_version.hpp>

#include <boost/test/unit_test.hpp>
#include <patchlevel.h>

BOOST_AUTO_TEST_SUITE(python_version)

BOOST_AUTO_TEST_CASE(version_constructor)
{
    unsigned int const expected_major = PY_MAJOR_VERSION;
    unsigned int const expected_minor = PY_MINOR_VERSION;
    unsigned int const expected_micro = PY_MICRO_VERSION;

    boost_python_exception::python_version const v;
    BOOST_CHECK_EQUAL(expected_major, v.major);
    BOOST_CHECK_EQUAL(expected_minor, v.minor);
    BOOST_CHECK_EQUAL(expected_micro, v.micro);
}

BOOST_AUTO_TEST_SUITE_END()
