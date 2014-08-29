#include <boost/python/exec.hpp>
#include <boost/test/unit_test.hpp>

#include <boost_python_exception/exceptions.hpp>
#include <boost_python_exception/get_exception_info.hpp>
#include <boost_python_exception/standard_exception_translator.hpp>

#include "helpers/execute_python_code.hpp"

namespace bp=boost::python;
namespace bpe=boost_python_exception;

namespace {

struct initialize_exception_translator
{
    initialize_exception_translator() :
        translator (bpe::create_standard_exception_translator())
        {}

    template <class CPPExceptionType>
    void exception_test(std::string const & python_exception)
        {
            try {
                test::execute_python_code_in_main_module(
                    "raise " + python_exception + "()");
                BOOST_CHECK(false);
            }
            catch (bp::error_already_set const &) {
                BOOST_CHECK_THROW(
                    translator.translate(bpe::get_exception_info()),
                    CPPExceptionType);
            }
        }

    bpe::exception_translator translator;
};

}

BOOST_FIXTURE_TEST_SUITE(standard_exception_translator,
                         initialize_exception_translator)

BOOST_AUTO_TEST_CASE( attribute_error )
{
    exception_test<bpe::attribute_error>("AttributeError");
}

BOOST_AUTO_TEST_CASE( import_error )
{
    exception_test<bpe::import_error>("ImportError");
}

BOOST_AUTO_TEST_CASE( index_error )
{
    exception_test<bpe::index_error>("IndexError");
}

BOOST_AUTO_TEST_CASE( io_error )
{
    exception_test<bpe::io_error>("IOError");
}

BOOST_AUTO_TEST_CASE( key_error )
{
    exception_test<bpe::key_error>("KeyError");
}

BOOST_AUTO_TEST_CASE( type_error )
{
    exception_test<bpe::type_error>("TypeError");
}

BOOST_AUTO_TEST_CASE( reference_error )
{
    exception_test<bpe::reference_error>("ReferenceError");
}

BOOST_AUTO_TEST_CASE( value_error )
{
    exception_test<bpe::value_error>("ValueError");
}

BOOST_AUTO_TEST_CASE( stop_iteration )
{
    exception_test<bpe::stop_iteration>("StopIteration");
}

BOOST_AUTO_TEST_CASE( syntax_error )
{
    exception_test<bpe::syntax_error>("SyntaxError");
}

BOOST_AUTO_TEST_SUITE_END()
