#ifndef INCLUDE_BOOST_PYTHON_EXCEPTION__EXCEPTION_TRANSLATOR_HPP
#define INCLUDE_BOOST_PYTHON_EXCEPTION__EXCEPTION_TRANSLATOR_HPP

#include <Python.h>

#include <utility>
#include <vector>

#include <boost/exception/info.hpp>
#include <boost/function.hpp>
#include <boost/python/import.hpp>
#include <boost/python/object.hpp>
#include <boost/python/tuple.hpp>

#include <boost_python_exception/exception_info.hpp>

namespace boost_python_exception {

/** A registry of python-to-c++ exception translators.

    The basic concept here is a map of Python exception class
    references to callables which are invoked when that exception is
    encountered. To use this, you create an instance and add
    translation handlers via the ``add()`` method. Then when you
    detect a Python exception (e.g. via
    ``boost::python::error_already_set()``), you call ``translate()``
    with the ``exception_info`` for the exception.

    In general it looks like this::

        exception_translator translator;

        // Configure the translator to throw IndexError when a Python
        // IndexError is detected.
        translator.add(
            bp::object(
               bp::handle<>(
                   bp::borrowed(PyExc_IndexError))),
            throw_<IndexError>);

        . . .

        try {
            some_boost_python_calls();
        }
        catch (const bp::error_already_set&) {
            translator.translate(get_exception_info());
        }
 */
class exception_translator
{
public:

    void translate(const exception_info& excInfo);

    typedef boost::function<void(const exception_info&)> Thrower;

    /* Add a translator for ``excType``.

       This will replace any existing translator for ``excType``.

       @return ``true`` if an existing handler was replaced, ``false``
       otherwise.
     */
    bool add(boost::python::object excType,
             Thrower thrower);

    /* Remove the translator for ``excType``, if any.

       This does nothing if there was not mapping for ``excType``.

       @return ``true`` if a translation was removed, ``false``
       otherwise.
     */
    bool remove(boost::python::object excType);

private:
    typedef std::pair<boost::python::object, Thrower> mapping;
    typedef std::vector<mapping> throw_map;
    throw_map map_;
};

/* An ``exception_translator::Thrower`` implementation that simply
   throws a default-constructed instace of ``ExcType``.
 */
template <typename ExceptionType>
void throw_(const exception_info&)
{
    throw ExceptionType();
}

/* A boost::exception error_info for carrying Python exception
   information.
*/
typedef boost::error_info<struct tag_exc_info, exception_info> exc_info;

/* An ``exception_translator::Thrower`` implementation that throws a
   default-constructed instance of ``ExceptionType`` with an ``exc_info``
   attached containing the ``exception_info``.
 */
template <typename ExceptionType>
void throw_with_python_info(const exception_info& e)
{
    throw ExceptionType() << exc_info(e);
}

}

#endif
