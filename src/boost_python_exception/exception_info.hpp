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
    const boost::python::object type;
    /**
     * @brief Exception value
     */
    const boost::python::object value;
    /**
     * @brief Exception traceback
     */
    const boost::python::object traceback;

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
