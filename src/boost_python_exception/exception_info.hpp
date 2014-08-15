#ifndef INCLUDE_BOOST_PYTHON_EXCEPTION_EXCEPTION_INFO_H
#define INCLUDE_BOOST_PYTHON_EXCEPTION_EXCEPTION_INFO_H

#include <boost/python/object.hpp>

namespace boost_python_exception {

/**
 * @brief Collects python objects which contain exception details
 */
struct exception_info {
	/**
	 * @brief Exception type
	 */
	boost::python::object const type;
	/**
	 * @brief Exception value
	 */
	boost::python::object const value;
	/**
	 * @brief Exception traceback
	 */
	boost::python::object const traceback;

    /**
     * @brief Construct a new exception_info instance
     * @param type Type of the exception
     * @param value Value of the exception
     * @param traceback Traceback of the exception
     */
    exception_info(boost::python::object type,
                   boost::python::object value,
                   boost::python::object traceback);
};

}

#endif /* INCLUDE_BOOST_PYTHON_EXCEPTION_EXCEPTION_INFO_H */
