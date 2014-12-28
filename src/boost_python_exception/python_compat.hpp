#ifndef INCLUDE_BOOST_PYTHON_EXCEPTION_PYTHON_COMPAT_HPP
#define INCLUDE_BOOST_PYTHON_EXCEPTION_PYTHON_COMPAT_HPP

/* Python 2/3 compatibility layer. */

#include <Python.h>
#include <string>

namespace boost_python_exception {

std::string python_string_as_std_string(PyObject*);
long python_integral_as_long(PyObject*);

}

#endif /* INCLUDE_BOOST_PYTHON_EXCEPTION_PYTHON_COMPAT_HPP */
