#ifndef INCLUDE_BOOST_PYTHON_EXCEPTION_EXTRACT_TRACEBACK_H
#define INCLUDE_BOOST_PYTHON_EXCEPTION_EXTRACT_TRACEBACK_H

#include <vector>

#include <boost/python/object.hpp>

#include <boost_python_exception/traceback_step.hpp>

namespace boost_python_exception {


/**
 * @brief Represents a python traceback
 */
typedef std::vector<traceback_step> traceback;

/*
 * @brief Extract a C++ representation of a python traceback stored in the given boost::python::object
 * @param py_traceback A python object which contains a representation of the traceback
 * @return The python traceback stored in the object. The vector is sorted from outer to inner, i.e.,
 *         vector[0] yields the outermost level of the traceback. Returns empty vector if
 *         py_traceback is None.
 */
traceback extract_traceback(boost::python::object py_traceback);

}

#endif /* INCLUDE_BOOST_PYTHON_EXCEPTION_EXTRACT_TRACEBACK_H */

