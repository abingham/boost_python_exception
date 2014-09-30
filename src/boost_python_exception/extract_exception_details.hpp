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
 *
 * Example:
 * @code
 * try {
 *     some_boost_python_code();
 * } catch (const bp::error_already_set&) {
 *     using boost_python_exception;
 *     exception_info const info = get_exception_info();
 *     traceback const stack = extract_traceback(info.traceback);
 *     // ...
 * }
 * @endcode
 */
traceback extract_traceback(boost::python::object py_traceback);

/**
 * @brief Extracts the type name of a python standard exception
 * @param type A python object which should represent a standard exception type
 * @return The type as a C++ string
 * @throw std::logic_error in case type is not a standard exception type
 *
 * Example:
 * @code
 * try {
 *     some_boost_python_code();
 * } catch (const bp::error_already_set&) {
 *     using boost_python_exception;
 *     exception_info const info = get_exception_info();
 *     std::string const type = extract_exception_type(info.type);
 *     // ...
 * }
 * @endcode
 */
std::string extract_exception_type(boost::python::object type);

/**
 * @brief Extract the string representation of the given value object as a string.
 *        In python, this would correspond to str(value).
 * @param value The value whose string representation should be determined
 * @return The string representation of value
 *
 * Please note that not all Python standard exceptions have a meaningful
 * string representation for value (SyntaxError, for example).
 *
 * Example:
 * @code
 * try {
 *     some_boost_python_code();
 * } catch (const bp::error_already_set&) {
 *     using boost_python_exception;
 *     exception_info const info = get_exception_info();
 *     std::string const message = extract_message(info.value);
 *     // ...
 * }
 * @endcode
 */
std::string extract_message(boost::python::object value);

}

#endif /* INCLUDE_BOOST_PYTHON_EXCEPTION_EXTRACT_EXCEPTION_DETAILS_H */
