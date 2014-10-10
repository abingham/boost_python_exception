#include <boost_python_exception/auto_translation/import.hpp>

#include <boost/python/import.hpp>
#include <boost/test/unit_test.hpp>

#include <boost_python_exception/exceptions.hpp>
#include <boost_python_exception/auto_translation/exception_translator.hpp>

#include <test/helpers/fixtures/clear_global_translator.hpp>

namespace bpe=boost_python_exception;;
namespace bp=boost::python;

namespace auto_translation = bpe::auto_translation;


BOOST_FIXTURE_TEST_SUITE( import, test::fixtures::clear_global_translator )

BOOST_AUTO_TEST_CASE( wraps_boost_python_import )
{
	std::string const module("math");
	bp::object const expected = bp::import(module.c_str());
	bp::object const actual = auto_translation::import(module);
	BOOST_CHECK(expected == actual);
}

BOOST_AUTO_TEST_CASE( throws_cpp_exception_on_error )
{
	std::string const invalid_module("this_module_does_not_exist");

	auto_translation::exception_translator::set_default();
	BOOST_CHECK_THROW(auto_translation::import(invalid_module), bpe::import_error);
}

BOOST_AUTO_TEST_SUITE_END()

