#include <boost_python_exception/auto_translation/exception_translator.hpp>

#include <boost/python/list.hpp>
#include <boost/test/unit_test.hpp>

#include <boost_python_exception/clear_exception.hpp>
#include <boost_python_exception/get_exception_info.hpp>
#include <boost_python_exception/exception_translator.hpp>
#include <boost_python_exception/exceptions.hpp>
#include <boost_python_exception/util.hpp>

#include <test/helpers/fixtures/clear_global_translator.hpp>

namespace bpe=boost_python_exception;;
namespace bp=boost::python;

namespace auto_translation = bpe::auto_translation;
using auto_translation::exception_translator::translate;

namespace {
	struct custom_error {};

	void throw_custom_error(bpe::exception_info const &)
	{
		throw custom_error();
	}

	bpe::exception_info make_index_error_info()
	{
		bp::object const none;
		return bpe::exception_info(bpe::builtins().attr("IndexError"), none, none);
	}

	void set_custom_translator()
	{
		bpe::exception_translator translator;
		translator.add(bpe::builtins().attr("IndexError"), throw_custom_error);

		auto_translation::exception_translator::set(translator);
	}
}

BOOST_FIXTURE_TEST_SUITE( auto_translation_exception_translator, test::fixtures::clear_global_translator )

BOOST_AUTO_TEST_CASE( logic_error_if_no_translator_set )
{
	BOOST_CHECK_THROW(translate(make_index_error_info()), std::logic_error);
}

BOOST_AUTO_TEST_CASE( translation_with_custom_translator )
{
	set_custom_translator();

	BOOST_CHECK_THROW(translate(make_index_error_info()), custom_error);
}

BOOST_AUTO_TEST_CASE( logic_error_if_cleared_after_set )
{
	set_custom_translator();
	auto_translation::exception_translator::clear();

	BOOST_CHECK_THROW(translate(make_index_error_info()), std::logic_error);
}

BOOST_AUTO_TEST_CASE( translation_with_default_translator )
{
	auto_translation::exception_translator::set_default();
	BOOST_CHECK_THROW(translate(make_index_error_info()), bpe::index_error)
}

BOOST_AUTO_TEST_CASE( custom_translator_after_default_translator )
{
	auto_translation::exception_translator::set_default();
	set_custom_translator();

	BOOST_CHECK_THROW(translate(make_index_error_info()), custom_error);
}

BOOST_AUTO_TEST_CASE( default_translator_after_custom_translator )
{
	set_custom_translator();
	auto_translation::exception_translator::set_default();

	BOOST_CHECK_THROW(translate(make_index_error_info()), bpe::index_error);
}

BOOST_AUTO_TEST_SUITE_END()
