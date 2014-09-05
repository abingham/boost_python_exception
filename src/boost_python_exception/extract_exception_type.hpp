#ifndef INCLUDE_BOOST_PYTHON_EXTRACT_EXCEPTION_TYPE_HPP
#define INCLUDE_BOOST_PYTHON_EXTRACT_EXCEPTION_TYPE_HPP

#include <string>

#include <boost/python/object.hpp>

namespace boost_python_exception {

/**
 * @brief Extracts the type name of a python standard exception
 * @param type A python object which should represent a standard exception type
 * @return The type as a C++ string
 * @throw std::logic_error in case type is not a standard exception type
 */
std::string extract_exception_type(boost::python::object type);

}

#endif
