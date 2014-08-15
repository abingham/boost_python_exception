#ifndef INCLUDE_BOOST_PYTHON_EXCEPTION_FORMAT_EXCEPTION_HPP
#define INCLUDE_BOOST_PYTHON_EXCEPTION_FORMAT_EXCEPTION_HPP

#include <string>

namespace boost_python_exception {

class exception_info;

<<<<<<< HEAD
/* Generate a nicely formatted string for the given exception_info.
 * This is well-behaved when the values are ``None``.
 */
std::string format_exception(exception_info const & ex_info);
=======
/* Generate a nicely formatted string for the (type, value, traceback)
 * tuple ``ex_info``. This is well-behaved when the values are
 * ``None``.
 */
std::string format_exception(const exception_info& ex_info);
>>>>>>> upstream/master

/* Calls ``format_exception()`` with the return value of
 * ``getExceptionInfo()``.
 */
std::string format_exception();


}

#endif /* INCLUDE_BOOST_PYTHON_EXCEPTION_FORMAT_EXCEPTION_HPP */
