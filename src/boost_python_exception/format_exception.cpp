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
std::string formatException(const bp::tuple& ex_info)
{
    bp::str formatted(ex_info);
    return bp::extract<std::string>(formatted);
}

/* Calls ``format_exception()`` with the return value of
 * ``getExceptionInfo()``.
 */
std::string formatException()
{

    return formatException(
        getExceptionInfo());
}


}
