#include <boost_python_exception/exception_translator.hpp>

#include <boost/python/list.hpp>
#include <boost/test/unit_test.hpp>

#include <boost_python_exception/exceptions.hpp>
#include <boost_python_exception/get_exception_info.hpp>
#include <boost_python_exception/util.hpp>

#include <test/helpers/fixtures/clear_python_errors.hpp>

namespace bpe=boost_python_exception;;
namespace bp=boost::python;

namespace {

void generate_index_error()
{
    bp::list l;
    bp::object obj = l[5];
    BOOST_CHECK(false);
}

}

BOOST_FIXTURE_TEST_SUITE( exception_translator, test::fixtures::clear_python_errors )

BOOST_AUTO_TEST_CASE( add )
{
    bpe::exception_translator e;
    BOOST_CHECK(
        not e.add(bpe::builtins().attr("IndexError"),
               bpe::throw_with_python_info<bpe::index_error>));

    try {
        generate_index_error();
    } catch (bp::error_already_set const &) {
        BOOST_CHECK_THROW(
            e.translate(bpe::get_exception_info()),
            bpe::index_error);
    }
}

BOOST_AUTO_TEST_CASE( multiple_adds )
{
    bpe::exception_translator e;
    e.add(bpe::builtins().attr("IndexError"),
          bpe::throw_with_python_info<bpe::index_error>);

    BOOST_CHECK(
        e.add(bpe::builtins().attr("IndexError"),
              bpe::throw_with_python_info<bpe::key_error>));

    try {
        generate_index_error();
    } catch (bp::error_already_set const &) {
        BOOST_CHECK_THROW(
            e.translate(bpe::get_exception_info()),
            bpe::key_error);
    }
}

BOOST_AUTO_TEST_CASE( remove )
{
    bpe::exception_translator e;
    e.add( bpe::builtins().attr("IndexError"),
           bpe::throw_with_python_info<bpe::index_error> );

    try {
        generate_index_error();
    } catch (const bp::error_already_set&) {
        BOOST_CHECK_THROW(
            e.translate(bpe::get_exception_info()),
            bpe::index_error);
    }

    BOOST_CHECK(
        e.remove(bpe::builtins().attr("IndexError")));

    try {
        generate_index_error();
    } catch (const bp::error_already_set&) {
        try {
            e.translate(bpe::get_exception_info());
        }
        catch (bpe::index_error const&) {
            BOOST_CHECK(false);
        }
        catch (bpe::exception const &) {
        	// okay because default throws standard exception
        }
    }
}

BOOST_AUTO_TEST_CASE( remove_multiple_times )
{
    bpe::exception_translator e;
    e.add( bpe::builtins().attr("IndexError"),
           bpe::throw_with_python_info<bpe::index_error> );

    BOOST_CHECK(
        e.remove(bpe::builtins().attr("IndexError")));

    BOOST_CHECK(
        not e.remove(bpe::builtins().attr("IndexError")));
}

BOOST_AUTO_TEST_CASE( remove_unknown )
{
    bpe::exception_translator e;
    BOOST_CHECK(
        not e.remove(bpe::builtins().attr("divmod")));
}

BOOST_AUTO_TEST_CASE( empty_translator_translates_standard_exception )
{
    bpe::exception_translator translator;

    try {
        generate_index_error();
    } catch (bp::error_already_set const &) {
        try {
        	translator.translate(bpe::get_exception_info());
        } catch (bpe::exception const & error) {
            std::string const expected_message("exceptions.IndexError: list index out of range");
            BOOST_CHECK_EQUAL(expected_message, error.what());
        }
    }
}

BOOST_AUTO_TEST_SUITE_END()
