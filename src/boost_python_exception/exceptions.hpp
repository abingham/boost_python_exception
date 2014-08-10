#ifndef INCLUDE_BOOST_PYTHON_EXCEPTION_EXCEPTIONS_HPP
#define INCLUDE_BOOST_PYTHON_EXCEPTION_EXCEPTIONS_HPP

/** C++ counterparts to the standard Python exceptions.
 */

#include <Python.h>

#include <exception>

#include <boost/exception/exception.hpp>

namespace boost_python_exception {

/** The base for all boost_python_exception exceptions. */
class Exception : public virtual boost::exception,
                  public virtual std::exception
{};

/* A collection of C++ analogues for the standard Python exceptions.
 */

class AttributeError : public Exception {};
class ImportError : public Exception {};
class IndexError : public Exception {};
class IOError : public Exception {};
class KeyError : public Exception {};
class TypeError : public Exception {};
class ReferenceError : public Exception {};
class ValueError : public Exception {};
class StopIteration : public Exception {};

}

#endif
