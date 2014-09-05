#ifndef INCLUDE_BOOST_PYTHON_EXCEPTION_EXTRACT_EXCEPTION_DETAILS_H
#define INCLUDE_BOOST_PYTHON_EXCEPTION_EXTRACT_EXCEPTION_DETAILS_H

#include <Python.h>

#include <boost/python/object.hpp>

#include <boost_python_exception/traceback.hpp>

namespace boost_python_exception {

/*
 * @brief Extract a C++ representation of a python traceback stored in the given boost::python::object
 * @param py_traceback A python object which contains a representation of the traceback
 * @return The python traceback stored in the object. The vector is sorted from outer to inner, i.e.,
 *         vector[0] yields the outermost level of the traceback. Returns empty vector if
 *         py_traceback is None.
 */
traceback extract_traceback(boost::python::object py_traceback);

/**
 * @brief Extracts the type name of a python standard exception
 * @param type A python object which should represent a standard exception type
 * @return The type as a C++ string
 * @throw std::logic_error in case type is not a standard exception type
 */
std::string extract_exception_type(boost::python::object type);

}

#endif /* INCLUDE_BOOST_PYTHON_EXCEPTION_EXTRACT_EXCEPTION_DETAILS_H */
