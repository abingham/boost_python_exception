#include <boost/python/exec.hpp>
#include <boost/test/unit_test.hpp>

#include <boost_python_exception/exceptions.hpp>
#include <boost_python_exception/get_exception_info.hpp>
#include <boost_python_exception/standard_exception_translator.hpp>

#include "helpers/execute_python_code.hpp"

namespace bp=boost::python;
namespace bpe=boost_python_exception;

namespace {

	void translate_exception_from_python_code(std::string const & python_code)
	{
		bpe::exception_translator const translator(bpe::create_standard_exception_translator());
		try {
			test::execute_python_code_in_main_module(python_code);
		} catch (boost::python::error_already_set const &) {
			translator.translate(bpe::get_exception_info());
		}
	}

	template <class CPPExceptionType>
	void exception_translation_default_test(std::string const & python_exception)
	{
		std::string const python_code("raise " + python_exception + "('Error message')");
		BOOST_CHECK_THROW(translate_exception_from_python_code(python_code), CPPExceptionType);
	}

}

BOOST_AUTO_TEST_SUITE(standard_exception_translator)

BOOST_AUTO_TEST_CASE( attribute_error )
{
	exception_translation_default_test<bpe::attribute_error>("AttributeError");
}

BOOST_AUTO_TEST_CASE( import_error )
{
	exception_translation_default_test<bpe::import_error>("ImportError");
}

BOOST_AUTO_TEST_CASE( index_error )
{
	exception_translation_default_test<bpe::index_error>("IndexError");
}

BOOST_AUTO_TEST_CASE( io_error )
{
	exception_translation_default_test<bpe::io_error>("IOError");
}

BOOST_AUTO_TEST_CASE( key_error )
{
	exception_translation_default_test<bpe::key_error>("KeyError");
}

BOOST_AUTO_TEST_CASE( type_error )
{
	exception_translation_default_test<bpe::type_error>("TypeError");
}

BOOST_AUTO_TEST_CASE( reference_error )
{
	exception_translation_default_test<bpe::reference_error>("ReferenceError");
}

BOOST_AUTO_TEST_CASE( value_error )
{
	exception_translation_default_test<bpe::value_error>("ValueError");
}

BOOST_AUTO_TEST_CASE( stop_iteration )
{
	exception_translation_default_test<bpe::stop_iteration>("StopIteration");
}

BOOST_AUTO_TEST_CASE( syntax_error )
{
	std::string const python_code(
			"def function():\n"
			"    obvious syntax error"
		);

	bpe::exception_translator translator(bpe::create_standard_exception_translator());

    try {
    	translate_exception_from_python_code(python_code);
    	BOOST_FAIL("No exception thrown");
	} catch (bpe::syntax_error const & error) {
		std::string const expected_message(
			"exceptions.SyntaxError: In module \"<string>\", line 2, position 18:\n"
			"Offending code:     obvious syntax error\n"
			"                                 ^"
		);
		BOOST_CHECK_EQUAL(expected_message.c_str(), error.what());
	}

}

BOOST_AUTO_TEST_SUITE_END()
