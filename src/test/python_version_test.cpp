#include <boost_python_exception/python_version.hpp>

#include <boost/test/unit_test.hpp>
#include <patchlevel.h>

BOOST_AUTO_TEST_SUITE(python_version)

using boost_python_exception::version;


BOOST_AUTO_TEST_CASE(version_constructor)
{
	unsigned int const expected_major = 1;
	unsigned int const expected_minor = 2;
	unsigned int const expected_micro = 3;
	version const v(expected_major, expected_minor, expected_micro);
	BOOST_CHECK_EQUAL(expected_major, v.major);
	BOOST_CHECK_EQUAL(expected_minor, v.minor);
	BOOST_CHECK_EQUAL(expected_micro, v.micro);
}

BOOST_AUTO_TEST_CASE(stream_inserter)
{
	version const v(1, 2, 3);
	std::string const expected = "1.2.3";
	std::ostringstream actual;
	actual << v;
	BOOST_CHECK_EQUAL(expected, actual.str());
}


namespace {
	version const reference(1,1,1);

	version const different_major(2,1,1);
	version const different_minor(1,2,1);
	version const different_micro(1,1,2);
}

BOOST_AUTO_TEST_CASE(equality)
{
	BOOST_CHECK( reference == reference );
	BOOST_CHECK( not (reference == different_major) );
	BOOST_CHECK( not (reference == different_minor) );
	BOOST_CHECK( not (reference == different_micro) );
}

BOOST_AUTO_TEST_CASE(inequality)
{
	BOOST_CHECK( not(reference != reference) );
	BOOST_CHECK( reference != different_major );
	BOOST_CHECK( reference != different_minor );
	BOOST_CHECK( reference != different_micro );
}

BOOST_AUTO_TEST_CASE(python_version)
{
	version const expected(PY_MAJOR_VERSION, PY_MINOR_VERSION, PY_MICRO_VERSION);
	version const actual = boost_python_exception::python_version();
	BOOST_CHECK_EQUAL(expected, actual);
}

BOOST_AUTO_TEST_SUITE_END()

