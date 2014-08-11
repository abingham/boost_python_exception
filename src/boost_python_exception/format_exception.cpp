#include <boost_python_exception/format_exception.hpp>

#include <boost/python/extract.hpp>
#include <boost/python/str.hpp>
#include <boost/python/tuple.hpp>

#include <boost_python_exception/get_exception_info.hpp>

namespace bp=boost::python;

namespace boost_python_exception {

/* Generate a nicely formatted string for the (type, value, traceback)
 * tuple ``ex_info``. This is well-behaved when the values are
 * ``None``.
 */
std::string format_exception(const exception_info& ex_info)
{
    bp::str formatted(
        bp::make_tuple(
            ex_info.type,
            ex_info.value,
            ex_info.traceback));

    return bp::extract<std::string>(formatted);
}

/* Calls ``format_exception()`` with the return value of
 * ``getExceptionInfo()``.
 */
std::string format_exception()
{
    return format_exception(
        get_exception_info());
}


}
