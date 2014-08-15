#include <boost_python_exception/format_exception.hpp>

#include <boost/python/extract.hpp>
#include <boost/python/str.hpp>
#include <boost/python/tuple.hpp>

#include <boost_python_exception/get_exception_info.hpp>

namespace bp=boost::python;

namespace boost_python_exception {

<<<<<<< HEAD
std::string format_exception(exception_info const & ex_info)
=======
/* Generate a nicely formatted string for the (type, value, traceback)
 * tuple ``ex_info``. This is well-behaved when the values are
 * ``None``.
 */
std::string format_exception(const exception_info& ex_info)
>>>>>>> upstream/master
{
    bp::str formatted(
        bp::make_tuple(
            ex_info.type,
            ex_info.value,
            ex_info.traceback));

    return bp::extract<std::string>(formatted);
}

std::string format_exception()
{
    return format_exception(
        get_exception_info());
}


}
