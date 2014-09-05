#ifndef INCLUDE_BOOST_PYTHON_EXCEPTION__EXCEPTION_TRANSLATOR_HPP
#define INCLUDE_BOOST_PYTHON_EXCEPTION__EXCEPTION_TRANSLATOR_HPP

#include <Python.h>

#include <utility>
#include <vector>

#include <boost/exception/info.hpp>
#include <boost/function.hpp>
#include <boost/python/object.hpp>
#include <boost/python/str.hpp>
#include <boost/python/extract.hpp>

#include <boost_python_exception/exceptions.hpp>
#include <boost_python_exception/exception_info.hpp>
#include <boost_python_exception/extract_exception_details.hpp>

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

    void translate(exception_info const & excInfo) const;

    typedef boost::function<void(exception_info const &)> thrower;

    /* Add a translator for ``excType``.

       This will replace any existing translator for ``excType``.

       @return ``true`` if an existing handler was replaced, ``false``
       otherwise.
     */
    bool add(boost::python::object excType,
             thrower thrower);

    /* Remove the translator for ``excType``, if any.

       This does nothing if there was not mapping for ``excType``.

       @return ``true`` if a translation was removed, ``false``
       otherwise.
     */
    bool remove(boost::python::object excType);

private:
    typedef std::pair<boost::python::object, thrower> mapping;
    typedef std::vector<mapping> exception_translators;
    exception_translators exception_translators_;
};

/* An ``exception_translator::thrower`` implementation that throws an
   instance of ``ExceptionType`` instantiated with an
   ``exception_info`` argument.
 */
template <typename ExceptionType>
void throw_with_python_info(exception_info const & exc_info)
{
	std::string const type = extract_exception_type(exc_info.type);

	std::string const message = boost::python::extract<std::string>(boost::python::str(exc_info.value));
	traceback const traceback = extract_traceback(exc_info.traceback);

    throw ExceptionType(type, message, traceback);
}

}

#endif
