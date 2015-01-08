#include <boost_python_exception/exception_translator.hpp>

#include <boost/python/list.hpp>
#include <boost/test/unit_test.hpp>

#include <boost_python_exception/exceptions.hpp>
#include <boost_python_exception/get_exception_info.hpp>
#include <boost_python_exception/util.hpp>

#include <test/helpers/fixtures/clear_python_errors.hpp>
#include <test/helpers/execute_python_code.hpp>

namespace bpe=boost_python_exception;;
namespace bp=boost::python;

namespace {

 bool add_index_error_handler(bpe::exception_translator & translator)
 {
  return translator.add(bpe::builtins().attr("IndexError"),
                 bpe::throw_with_python_info<bpe::index_error>);
 }

 void generate_index_error()
 {
  bp::list l;
  bp::object obj = l[5];
  BOOST_CHECK(false);
 }

 void translate_index_error(bpe::exception_translator const & translator)
 {
     try {
         generate_index_error();
     } catch (bp::error_already_set const &) {
            translator.translate(bpe::get_exception_info());
     }
 }

 void check_translator_translates_index_error(bpe::exception_translator const & translator)
 {
  BOOST_CHECK_THROW(translate_index_error(translator), bpe::index_error);
 }

}

BOOST_FIXTURE_TEST_SUITE( exception_translator, test::fixtures::clear_python_errors )

BOOST_AUTO_TEST_CASE( add )
{
    bpe::exception_translator translator;
    BOOST_CHECK(not add_index_error_handler(translator));

    check_translator_translates_index_error(translator);
}

namespace {
 void suppress_exception(bpe::exception_info const &)
 {
 }
}

BOOST_AUTO_TEST_CASE( multiple_adds )
{
    bpe::exception_translator translator;
    translator.add(bpe::builtins().attr("IndexError"),
          suppress_exception);

    BOOST_CHECK(add_index_error_handler(translator));

    check_translator_translates_index_error(translator);
}

BOOST_AUTO_TEST_CASE( remove )
{
    bpe::exception_translator translator;
    add_index_error_handler(translator);

    check_translator_translates_index_error(translator);

    BOOST_CHECK(
     translator.remove(bpe::builtins().attr("IndexError")));

    try {
     translate_index_error(translator);
     BOOST_FAIL("No exception thrown");
    } catch (bpe::index_error const&) {
        BOOST_FAIL("After deletion of specialized handler, specialized exception must not be thrown");
 } catch (bpe::exception const &) {
  // okay because default throws standard exception
 }
}

BOOST_AUTO_TEST_CASE( remove_multiple_times )
{
    bpe::exception_translator translator;
    add_index_error_handler(translator);

    BOOST_CHECK(
        translator.remove(bpe::builtins().attr("IndexError")));

    BOOST_CHECK(
        not translator.remove(bpe::builtins().attr("IndexError")));
}

BOOST_AUTO_TEST_CASE( remove_unknown )
{
    bpe::exception_translator translator;
    BOOST_CHECK(
        not translator.remove(bpe::builtins().attr("divmod")));
}

BOOST_AUTO_TEST_CASE( empty_translator_translates_standard_exception )
{
    bpe::exception_translator translator;

    try {
        translate_index_error(translator);
        BOOST_FAIL("No exception thrown");
    } catch (bpe::exception const & error) {
        std::ostringstream expected_message;
#if PY_MAJOR_VERSION == 2
        expected_message << "exceptions.";
#endif
        expected_message << "IndexError: list index out of range";
        BOOST_CHECK_EQUAL(expected_message.str(), error.what());
    }
}

#if PY_MAJOR_VERSION == 2

BOOST_AUTO_TEST_CASE( empty_translator_translates_non_standard_exception )
{
    std::string const raise_non_standard_exception(
   "class old_style_class:\n"
   "    pass\n"
   "raise old_style_class()"
     );

    std::string const expected_message(
      "Python traceback (most recent calls last):\n"
      "File \"<string>\", line 3, in <module>\n"
      "<unknown non-standard exception>"
     );

    bpe::exception_translator translator;

    try {
     test::execute_python_code_in_main_module(raise_non_standard_exception);
     BOOST_FAIL("No exception thrown");
    } catch (bp::error_already_set const &) {
        try {
         translator.translate(bpe::get_exception_info());
         BOOST_FAIL("No exception thrown");
        } catch (bpe::exception const & error) {
            BOOST_CHECK_EQUAL(expected_message, error.what());
        }
    }
}

#endif

BOOST_AUTO_TEST_SUITE_END()
