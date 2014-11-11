#ifndef INCLUDE_BOOST_PYTHON_EXCEPTION_GET_EXCEPTION_INFO_H
#define INCLUDE_BOOST_PYTHON_EXCEPTION_GET_EXCEPTION_INFO_H

#include <boost_python_exception/exception_info.hpp>

namespace boost_python_exception {

/** Get the current Python exception info

    This leaves the Python exception registers unchanged (with the
    exception of inc-ref'ing the objects in the registers, if any.)

    @return An exception_info instance. If there is no current exception, all of the elements
      of the instance will be ``None``.
 */
exception_info get_exception_info();

}

#endif /* INCLUDE_BOOST_PYTHON_EXCEPTION_GET_EXCEPTION_INFO_H */
