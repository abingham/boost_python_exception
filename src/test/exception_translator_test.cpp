#include <boost_python_exception/exception_translator.hpp>

#include <boost/python/list.hpp>
#include <boost/test/unit_test.hpp>

#include <boost_python_exception/exceptions.hpp>
#include <boost_python_exception/get_exception_info.hpp>
#include <boost_python_exception/util.hpp>

namespace bpe=boost_python_exception;;
namespace bp=boost::python;

BOOST_AUTO_TEST_SUITE( exception_translator )

BOOST_AUTO_TEST_CASE( add )
{
    bpe::exception_translator e;
    e.add( bpe::builtins().attr("IndexError"),
           bpe::throw_with_python_info<bpe::IndexError> );

    bp::list l;

    try {
        l[5];
    } catch (const bp::error_already_set&) {
        BOOST_CHECK_THROW(
            e.translate(bpe::get_exception_info()),
            bpe::IndexError);
    }
}

BOOST_AUTO_TEST_CASE( remove )
{
    bpe::exception_translator e;
    e.add( bpe::builtins().attr("IndexError"),
           bpe::throw_with_python_info<bpe::IndexError> );

    bp::list l;

    try {
        l[5];
    } catch (const bp::error_already_set&) {
        BOOST_CHECK_THROW(
            e.translate(bpe::get_exception_info()),
            bpe::IndexError);
    }

    e.remove(bpe::builtins().attr("IndexError"));

    try {
        l[5];
    } catch (const bp::error_already_set&) {
        e.translate(bpe::get_exception_info());
        BOOST_ASSERT(true);
    }
}

BOOST_AUTO_TEST_SUITE_END()
