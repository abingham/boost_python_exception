#ifndef INCLUDE_BOOST_PYTHON_EXCEPTION_UTIL_HPP
#define INCLUDE_BOOST_PYTHON_EXCEPTION_UTIL_HPP

#include <Python.h>

#include <boost/python/object.hpp>

namespace boost_python_exception {

/** Get the "builtins" module.

    @return The "builtins" module object.
 */
boost::python::object builtins();

}

#endif /* INCLUDE_BOOST_PYTHON_EXCEPTION_UTIL_HPP */
